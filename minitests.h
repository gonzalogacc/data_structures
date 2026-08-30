#ifndef MINITEST_H
#define MINITEST_H

extern int tests_run;
extern int tests_failed;

#define FAIL(msg) do {\
    printf("  \033[31m[FAIL]\033[0m %s:%d: %s\n", __FILE__, __LINE__, msg); \
    tests_failed++;\
    return;\
} while (0)

#define ASSERT(test, msg) do {\
    if (!(test)) FAIL(msg);\
} while (0)

#define RUN_TEST(test) do { \
    printf("Running %s...\n", #test); \
    tests_run++; \
    test(); \
} while (0)

#define TEST_REPORT() do { \
    printf("\n--- Test Results ---\nPassed: %d/%d\nFailed: %d\n", \
           tests_run - tests_failed, tests_run, tests_failed); \
} while (0)

#endif