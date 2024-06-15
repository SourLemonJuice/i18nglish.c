#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include <stdlib.h>

/* For compiler defin flag(gcc -D) */
#ifndef APP_GIT_COMMIT_INFO
#define APP_GIT_COMMIT_INFO "ERROR: APP_GIT_COMMIT_INFO should be defined by compiler"
#endif

/* Self define */
#define APP_VERSION_STRING "ver-1.0"
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
