# Directories
SRCDIR   := src
INCDIR   := include
BUILDDIR := build
TESTDIR  := tests

CC      := gcc
AR      := ar
RANLIB  := ranlib

CPPFLAGS := -I$(INCDIR)
CFLAGS   := -std=c90 -Wall -Wextra -Werror -Wpedantic -Wshadow 
LDFLAGS  :=
LDLIBS   := -lm
TFLAGS    = $(CFLAGS) -I$(TESTDIR) -g -O0

# Coverage toggle, make COVERAGE=1, will only take effect if BUILD=debug is set
COVERAGE ?= 0

# Debug / Release toggle:  make BUILD=debug  or  make BUILD=release (default)
BUILD ?= release
ifeq ($(BUILD),debug)
    ifeq ($(COVERAGE),1)
	CFLAGS += --coverage -pg
	LDFLAGS += --coverage
    endif
    CFLAGS += -O0 -g3 -DDEBUG
else
    CFLAGS += -O2 -DNDEBUG
endif

# ------------------------------------------------------------------------------
# Automatic dependency generation
#   -MMD  — write a .d file alongside every .o with header dependencies
#   -MP   — add a phony target for each header to avoid errors on deletion
# ------------------------------------------------------------------------------
DEPFLAGS = -MMD -MP

# --- Sources shared by ALL executables ----------------------------------------
SHARED_SRCS := \
    $(SRCDIR)/term_draw.c \
    $(SRCDIR)/bitboard.c \
    $(SRCDIR)/piece_moves.c \
    $(SRCDIR)/player_input.c \
    $(SRCDIR)/print_board.c

# --- Per-executable sources (include their own main + any private sources) -----
SERVER_SRCS := \
    $(SRCDIR)/cmd_chess_server_main.c

CLIENT_SRCS := \
    $(SRCDIR)/cmd_chess_client_main.c

TOOL_SRCS := \
    $(SRCDIR)/cmd_chess_main.c 

# --- Test sources --------------------------------------------------------------
TEST_SRCS := $(wildcard $(TESTDIR)/*.c)

# Derive object and dependency file lists from source lists
#
# Objects land in $(BUILDDIR)/<original-path-without-srcdir>.o so that
# src/foo/bar.c → build/foo/bar.o (subdirectory layout is preserved).
src_to_obj = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(1))

SHARED_OBJS := $(call src_to_obj,$(SHARED_SRCS))
SERVER_OBJS := $(call src_to_obj,$(SERVER_SRCS))
CLIENT_OBJS := $(call src_to_obj,$(CLIENT_SRCS))
TOOL_OBJS   := $(call src_to_obj,$(TOOL_SRCS))

ALL_OBJS := $(sort $(SHARED_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS) $(TOOL_OBJS))
DEPS     := $(ALL_OBJS:.o=.d)

# Executable names — override with  make BINDIR=/usr/local/bin  if desired
BINDIR  := $(BUILDDIR)/bin
TBINDIR := $(BUILDDIR)/tests

SERVER := $(BINDIR)/cmd_chess_server
CLIENT := $(BINDIR)/cmd_chess_client
TOOL   := $(BINDIR)/cmd_chess

TEST_BINS := $(patsubst $(TESTDIR)/%.c,$(TBINDIR)/%, $(TEST_SRCS))

# Default target — must come before any includes (the -include below could
# theoretically define targets if .d files are malformed).
.PHONY: all
all: $(SERVER) $(CLIENT) $(TOOL)

# Link rules — each executable gets shared objects + its own objects
$(SERVER): $(SHARED_OBJS) $(SERVER_OBJS) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(CLIENT): $(SHARED_OBJS) $(CLIENT_OBJS) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TOOL): $(SHARED_OBJS) $(TOOL_OBJS) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Pattern rule — compile every .c under $(SRCDIR) to a .o under $(BUILDDIR)
#
# The order-only prerequisite '| <dir>' creates the output directory on demand
# without causing the object to be considered out of date when the directory's
# mtime changes.
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TBINDIR)/%: $(TESTDIR)/%.c $(SHARED_OBJS) | $(TBINDIR)
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $(TFLAGS) -o $@ $^

# Test target, will clean, then run test with coverage and debug flags set
# cleans so all files will be rebuilt with coverage enabled, fine for small project,
# should probably be cleaned up for a large project
.PHONY: test
test: clean
	$(MAKE) BUILD=debug COVERAGE=1 _test

# Internal target, only meant to be called by test
.PHONY: _test
_test: $(TEST_BINS)
	@echo "==== Running Tests ===="
	@failed=0; \
	for t in $(TEST_BINS); do \
		echo " ---- $$t ----"; \
		$$t; \
		if [ $$? -ne 0 ]; then failed=1; fi; \
	done; \
	if [ $$failed -eq 1 ]; then \
		echo "\n **** SOME TESTS FAILED ****"; exit 1; \
	else \
		echo "\n==== All Tests Passed ===="; \
	fi

# Directory creation (order-only prerequisites)
$(BUILDDIR) $(BINDIR) $(TBINDIR):
	mkdir -p $@

# Include auto-generated dependency files.
# The leading '-' suppresses errors when they do not yet exist (first build).
-include $(DEPS)

# Generate compile_commands.json for clangd / LSP tooling.
# Forces a clean build so every translation unit is captured.
.PHONY: bear
bear: clean
	bear -- $(MAKE) all

# Remove compiled outputs but keep the source tree intact
.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR) .cache/
