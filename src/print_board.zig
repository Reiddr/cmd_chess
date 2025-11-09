const std = @import("std");

pub fn print_board(a: u64) !i8 {

    const stdout_file = std.io.getStdOut().writer();
    var bw = std.io.bufferedWriter(stdout_file);
    const stdout = bw.writer();

    // const green = "\x1b[0;32m";
    // const black = "\x1b[0;30m";
    // const white = "\x1b[0;37m";
    const reset = "\x1b[0m";
    const brown_bg = "\x1b[48;5;94m";
    const grey_bg = "\x1b[48;5;250m";
    // const knight_w = '\u{2658}';
    const knight_b = '\u{265E}';
    for (0..8) |row| {
        //try stdout.print("{d}, {d}: ", .{a, row});
        for (0..8) |col| {
            if ((row + col) % 2 == 1) {
                try stdout.print("{s}", .{brown_bg});
            } else {
                try stdout.print("{s}", .{grey_bg});
            }
            if (a << @intCast(8*row + col) == 1) {
                try stdout.print(" {u} ", .{knight_b});
            } else {
                try stdout.print("   ", .{});
            }
        }
        try stdout.print("{s}\n", .{reset});
    }
    try stdout.print("{s}\n", .{reset});
    //try stdout.print("knight_w: {s}{s}{u}{s} knight_b: {s}{s}{u}{s}\n", .{brown_bg, white, knight_b, reset, brown_bg, white, knight_w, reset});

    try bw.flush(); // Don't forget to flush!

    return 0;
}

