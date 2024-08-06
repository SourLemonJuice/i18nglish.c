#include "main.h"

#include <ctype.h>
#include <iso646.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i7h/i7h_processor.h"

/*
    print some common log
 */
static void i7hProcessorExitLog_(char source_string[], int proc_result)
{
    printf("Error: Something wrong while processing.\n");
    printf("Source string: '%s', Result code: %d\n", source_string, proc_result);
    return;
}

/*
    [Useless]
    Delete all punctuation in the string.
    src_string must be larger then des_string, for safe.
    Maybe this restriction will lifted in future.
 */
static int deletePunctuations_(char src_string[], int src_size, char des_string[], int des_size)
{
    if (src_size > des_size)
        return 1;

    int des_index = 0;
    for (int src_index = 0; src_index < src_size; src_index++) {
        if (ispunct(src_string[src_index]) != 0) {
            continue;
        } else {
            if (des_index < des_size) {
                des_string[des_index] = src_string[src_index];
                des_index++;
            }
        }
    }
    des_string[des_index] = '\0';

    return 0;
}

int i7hProcessorArgv(int argc, char *argv[], int argc_begin)
{
    if (argc_begin > argc - 1) {
        puts("ERROR: Parameter invalid.");
        exit(kErrorAppGetFlag);
    }

    // create and init i7h data
    struct I7hDataStruct i7h_data;
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;

    // process all arguments
    for (int i = argc_begin; i < argc; i++) {
        // call the main function
        i7h_proc_result = i7hProcessor(&i7h_data, argv[i]);
        if (i7h_proc_result == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            i7hProcessorExitLog_(argv[i], i7h_proc_result);
            exit(kErrorParserProcessing);
        }
    }
    printf("\n");
    // free the buffer
    i7hFreeStructure(&i7h_data);

    return 0;
}

void i7hProcessorFile(char *file_path)
{
    // file stuff
    FILE *file_handle = fopen(file_path, "r");
    if (file_handle == NULL) {
        printf("ERROR: File con't open\n");
        exit(kErrorAppStd);
    }

    if (i7hParserStream(file_handle, stdout) != 0)
        exit(kErrorParserProcessing);

    fclose(file_handle);

    return;
}

// Sames like i7hProcessorFile, here is just copy
void i7hProcessorStdin(void)
{
    if (i7hParserStream(stdin, stdout) != 0)
        exit(kErrorParserProcessing);

    return;
}

int parseCliFlag(struct AppCliFlagConfig *flag_data, int argc, char *argv[])
{
    if (argc < 2) {
        printf("ERROR: Need some arguments, use \"--help\" flag to check more info.\n\n");
        flag_data->main_mode = kAppInputMode_ShowHelp;
        return kAppOk;
    }

    for (int i = 1; i + 1 <= argc; i++) {
        // --help
        if (strcmp(argv[i], "--help") == 0) {
            flag_data->main_mode = kAppInputMode_ShowHelp;
            return kAppOk;
        }

        // --version
        if (strcmp(argv[i], "--version") == 0) {
            flag_data->main_mode = kAppInputMode_ShowVersion;
            return kAppOk;
        }

        // --mode
        if (strcmp(argv[i], "--mode") == 0) {
            i++;
            // error detect
            if (not(i + 1 <= argc)) {
                printf("No value of --mode flag\n");
                return kErrorAppGetFlag;
            }

            // args
            if (strcmp(argv[i], "args") == 0) {
                flag_data->main_mode = kAppInputMode_ParseArgument;
                i++;
                if (i + 1 <= argc) {
                    flag_data->output_argc_begin = i;
                } else {
                    printf("Invalid/Null value of '--mode argument'\n");
                    return kErrorAppFlagValue;
                }
                return kAppOk;
            }
            // file
            if (strcmp(argv[i], "file") == 0) {
                flag_data->main_mode = kAppInputMode_ParseFile;
                i++;
                if (i + 1 <= argc) {
                    flag_data->output_file_path = argv[i];
                } else {
                    printf("Invalid/Null value of '--mode file'\n");
                    return kErrorAppFlagValue;
                }
                return kAppOk;
            }
            // stdin
            if (strcmp(argv[i], "stdin") == 0) {
                flag_data->main_mode = kAppInputMode_ParseStdin;
                return kAppOk;
            }
            // default
            printf("Invalid/Null value of '--mode'\n");
            return kErrorAppFlagValue;
        }
        // default
        printf("ERROR: Invalid Flag '%s'\n", argv[i]);
        return kErrorAppGetFlag;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    // set locale
    setlocale(LC_ALL, "en_US.UTF-8");

    // parse flags
    struct AppCliFlagConfig flag_data;
    int parse_flag_rsult = parseCliFlag(&flag_data, argc, argv);
    if (parse_flag_rsult != kAppOk)
        exit(parse_flag_rsult);

    switch (flag_data.main_mode) {
    case kAppInputMode_ShowHelp:
        printf("Usage: i18nglish [--version] [--help] --mode <MODE> [args]\n");
        printf("> Flags are just half stable\n");
        printf("\nMODE(for set input source):\n");
        printf("\targs <arg>...\tUse all arguments after it. This mode won't care punctuation\n");
        printf("\tstdin\t\tGet input from stdin stream\n");
        printf("\tfile <path>\tRead a text file\n");
        exit(kAppOk);
        break;
    case kAppInputMode_ShowVersion:
        printf("==== Versions ====\n");
        printf("App version:\t%s\n", APP_VERSION_STRING);
        printf("Build Date:\t%s\n", APP_BUILD_DATE_UTC);
        printf("Git commit:\t%s\n", APP_GIT_COMMIT_INFO);
        printf("Compiler ver:\t%s\n", __VERSION__); // __VERSION__ is not a std macro.
        printf("Build host:\t%s\n", APP_BUILD_HOST_DESCRIPTION);
        printf("==== Author info ====\n");
        printf("Developed by 酸柠檬猹/SourLemonJuice 2024\n");
        printf("Published under MIT license\n");
        exit(kAppOk);
        break;
    case kAppInputMode_ParseArgument:
        i7hProcessorArgv(argc, argv, flag_data.output_argc_begin);
        exit(kAppOk);
        break;
    case kAppInputMode_ParseStdin:
        i7hProcessorStdin();
        exit(kAppOk);
        break;
    case kAppInputMode_ParseFile:
        i7hProcessorFile(flag_data.output_file_path);
        exit(kAppOk);
        break;
    }

    // at last print some ERROR by default
    puts("ERROR: Unknow Error at 'main'");
    exit(kErrorAppStd);
}
