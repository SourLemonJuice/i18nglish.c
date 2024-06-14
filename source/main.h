#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include <stdlib.h>

/* For compiler defin flag(gcc -D) */
#ifndef APP_GIT_COMMIT_INFO
    #define APP_GIT_COMMIT_INFO "ERROR: APP_GIT_COMMIT_INFO should be defined by compiler"
#endif

/* Self define */
#define APP_VERSION_STRING "Development"

/* Enumerates */
enum AppExitType {
    AppExitOk = EXIT_SUCCESS,
    AppExitStd = EXIT_FAILURE,
    AppExitGetFlag,
    MainProcessorError,
};

#endif
