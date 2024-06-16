#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include <stdlib.h>

/*
    For compiler defin flag(gcc -D)
    Those macros should be defined by compiler
 */
#ifndef APP_GIT_COMMIT_INFO
#define APP_GIT_COMMIT_INFO "[Build ERROR] APP_GIT_COMMIT_INFO not defined"
#endif

#ifndef APP_BUILD_HOST_DESCRIPTION
#define APP_BUILD_HOST_DESCRIPTION "[Build ERROR] APP_BUILD_HOST_DESCRIPTION not defined"
#endif

/* Self define */
// switch between release build mode...
#if APP_BUILD_RELEASE_MODE == 1
#define APP_VERSION_STRING "ver-1.0"
#else // ...and develop build
// cheating the code analyzer
#define APP_BUILD_RELEASE_MODE 0
#define APP_VERSION_STRING "Under Development"
#endif

/*
    TODO I'm tired...
    This size use for some input string preprocessor, like fscanf() or deletePunctuations()
    It's not perfet. Only auto size can keep pointer safe. BUT:
    There's no any word that has more than 1KiB length, whatever...
 */
#define INPUT_BUFFER_SIZE (1024 * 1)

/* Enumerates */
enum AppExitType {
    AppExitOk = EXIT_SUCCESS,
    AppExitStd = EXIT_FAILURE,
    AppExitGetFlag,
    MainProcessorError,
    AppPreProcessorError,
};

#endif
