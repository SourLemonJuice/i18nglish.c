#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include <stdlib.h>
#include <stdbool.h>

/*
    For compiler defin flag(gcc -D)
    Those macros should be defined by compiler
 */
// git info when building
#ifndef APP_GIT_COMMIT_INFO
#define APP_GIT_COMMIT_INFO "[Build Missing] APP_GIT_COMMIT_INFO (macro) not defined"
#endif

// build UTC time
#ifndef APP_BUILD_DATE_UTC
#define APP_BUILD_DATE_UTC "[Build Missing] APP_BUILD_DATE_UTC (macro) not defined"
#endif

// build host info
#ifndef APP_BUILD_HOST_DESCRIPTION
#define APP_BUILD_HOST_DESCRIPTION "[Build Missing] APP_BUILD_HOST_DESCRIPTION (macro) not defined"
#endif

// switch between release build mode...
#if APP_BUILD_RELEASE_MODE == 1
#define APP_VERSION_STRING "ver-2.0"
#elif APP_BUILD_RELEASE_MODE == 0 // ...and develop build
// cheating the code analyzer
#define APP_BUILD_RELEASE_MODE 0
#define APP_VERSION_STRING "Develop"
#else
#error The macro APP_BUILD_RELEASE_MODE is set to non 0/1, go check make flags.
#endif

/* Self define */
/*
    TODO I'm tired...
    This size use for some input string preprocessor, like fscanf() or deletePunctuations()
    It's not perfet. Only auto size can keep pointer safe. BUT:
    There's no any word that has more than 1KiB length, whatever...
 */
#define INPUT_BUFFER_SIZE (1024 * 1)

enum AppExitType {
    kAppExitOk = EXIT_SUCCESS,
    kAppExitStd = EXIT_FAILURE,
    kAppExitGetFlagError,
    kAppExitFlagValueError,
    kMainProcessorError,
    kAppPreProcessorError,
};

enum AppCommandFlagMode {
    kAppInputMode_ParseArgument,
    kAppInputMode_ParseFile,
    kAppInputMode_ParseStdin,
    kAppInputMode_ShowHelp,
    kAppInputMode_ShowVersion,
};

// TODO TBD feature
// go to use pipe
enum AppCommandOutputMode {
    kAppOutputMode_Stdout,
    kAppOutputMode_File,
};

struct AppCliFlagConfig {
    enum AppCommandFlagMode main_mode;
    enum AppCommandOutputMode output_mode;
    char *output_file_path;
    int output_argc_begin;
};

#endif
