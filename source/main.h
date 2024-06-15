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
#define APP_VERSION_RELEASE_BUILD false
// release version
#if APP_VERSION_RELEASE_BUILD
#define APP_VERSION_STRING "ver-1.0"
#else
#define APP_VERSION_STRING "Development"
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
