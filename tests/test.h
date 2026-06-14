#ifndef TEST_H
#define TEST_H

#include <stdio.h>

static int TESTS_RUN = 0;
static int TESTS_FAILED = 0;

/* An assert macro that incremements the static variables above
 * The do while(0) is so that the entire macro is a single valid statement
 * this avoids breaking if statements with no {}
 * Usage: ASSERT(i < 0, "i should be negative");
 */
#define ASSERT(cond, msg) \
        do { \
                TESTS_RUN++; \
                if (cond) { \
                        printf("    PASS: %s\n", msg); \
                } else { \
                        TESTS_FAILED++; \
                        printf("    FAIL: %s [%s:%d] \n", msg, __FILE__, __LINE__); \
                } \
        } while (0) 

/* Helper function to print test info 
 * returns true if any tests have failed and false otherwise
 * this avoid the user having to check the TESTS_* variables themselves
 * intented usage at the end of main 
 *      return any_test_failed();
 */
int any_test_failed(void)
{
        printf("\n%d/%d tests passed\n", TESTS_RUN - TESTS_FAILED, TESTS_RUN);
        return TESTS_FAILED > 0 ? 1 : 0;
}

#endif /* TEST_H */
