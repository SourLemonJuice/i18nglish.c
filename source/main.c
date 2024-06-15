#include "main.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "i7h_processor.h"

/*
    This func will return an exit code,
    the main program need exit with this code.
    like: `exit(thisFunc(str, int))`
 */
int i7hProcessorExitLog(char source_string[], int proc_result)
{
    printf("Error: Something wrong while processing.\n");
    printf("Source string: '%s', Result code: %d\n", source_string, proc_result);
    return MainProcessorError;
}

/*
    Delete all punctuation in the string.
    src_string must be larger then des_string, for safe.
    Maybe this restriction will lifted in future.
 */
int deletePunctuations(char src_string[], int src_size, char des_string[], int des_size)
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
        exit(AppExitGetFlag);
    }

    // this buffer use to store argv without punctuation
    char argv_nopunct[INPUT_BUFFER_SIZE];

    // create and init i7h data
    struct I7hDataStruct i7h_data;
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;

    // process all arguments
    for (int i = argc_begin; i < argc; i++) {
        // delete punct
        if (deletePunctuations(argv[i], strlen(argv[i]) + 1, argv_nopunct, INPUT_BUFFER_SIZE) != 0) {
            exit(AppPreProcessorError);
        }
        // call the main function
        i7h_proc_result = i7hProcessor(&i7h_data, argv_nopunct);
        if (i7h_proc_result == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            exit(i7hProcessorExitLog(argv[i], i7h_proc_result));
        }
    }
    printf("\n");
    // free the buffer
    i7hFreeStructure(&i7h_data);

    return 0;
}

int i7hProcessorFile(char *file_path)
{
    // file stuff
    FILE *file_handle = fopen(file_path, "r");
    char next_char_tmp;
    char next_string[INPUT_BUFFER_SIZE];
    char next_string_nopunct[INPUT_BUFFER_SIZE];

    // create i7h data(buffer)
    struct I7hDataStruct i7h_data;
    // init structure
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;

    // TODO Can this detecter be rewritten as a macro?
    while ((next_char_tmp = getc(file_handle)) != EOF) {
        // separate all speace/lineBreaks char
        if (next_char_tmp == ' ' or next_char_tmp == '\n')
            continue;
        else
            ungetc(next_char_tmp, file_handle); // this char just used for detect EOF

        /*  great debug code
            printf("%d\n", fscanf(file_handle, "%s", next_string)); */
        fscanf(file_handle, "%s", next_string);
        // delete punctuations
        if (deletePunctuations(next_string, INPUT_BUFFER_SIZE, next_string_nopunct, INPUT_BUFFER_SIZE) != 0) {
            exit(AppPreProcessorError);
        }
        // call the main function
        if ((i7h_proc_result = i7hProcessor(&i7h_data, next_string_nopunct)) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            exit(i7hProcessorExitLog(next_string, i7h_proc_result));
        }
    }
    printf("\n");

    // to free something
    i7hFreeStructure(&i7h_data);
    fclose(file_handle);

    return 0;
}

int i7hProcessorStdin(void)
{
    char next_char;
    char temp_string[INPUT_BUFFER_SIZE];
    char temp_string_nopunct[INPUT_BUFFER_SIZE];

    struct I7hDataStruct i7h_data;
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;

    // Sames like i7hProcessorFile, here is just copy
    while ((next_char = getc(stdin)) != EOF) {
        if (next_char == ' ' or next_char == '\n')
            continue;
        else
            ungetc(next_char, stdin); // EOF detect

        fscanf(stdin, "%s", temp_string);
        // delete punctuations
        if (deletePunctuations(temp_string, INPUT_BUFFER_SIZE, temp_string_nopunct, INPUT_BUFFER_SIZE) != 0) {
            exit(AppPreProcessorError);
        }
        if ((i7h_proc_result = i7hProcessor(&i7h_data, temp_string_nopunct)) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            exit(i7hProcessorExitLog(temp_string, i7h_proc_result));
        }
    }
    printf("\n");

    i7hFreeStructure(&i7h_data);

    return 0;
}

int main(int argc, char *argv[])
{
    // handle CLI inputs
    if (argc < 2) {
        puts("ERROR: Need some arguments, use \"--help\" flag to check more info.");
        exit(AppExitGetFlag);
    }
    // flags
    // TODO This handle way was not good, right?
    for (int i = 1; i < argc; i++) {
        // --help
        if (strcmp(argv[i], "--help") == 0) {
            puts("All flags/arguments are unstabled.");
            puts("--help | --version | -- <string> <...> | --source_file <filePath> | --stdin");
            exit(AppExitOk);
        }
        // --version
        if (strcmp(argv[i], "--version") == 0) {
            printf("==== Versions ====\n");
            printf("App version:\t%s\n", APP_VERSION_STRING);
            printf("Build Date:\t%s, Time: %s\n", __DATE__, __TIME__);
            printf("Git commit:\t%s\n", APP_GIT_COMMIT_INFO);
            printf("Compiler ver:\t%s\n", __VERSION__); // __VERSION__ is not a std macro.
            printf("Build host:\t%s\n", APP_BUILD_HOST_DESCRIPTION);
            printf("==== Author info ====\n");
            printf("Developed by 酸柠檬猹/SourLemonJuice 2024\n");
            printf("Published under MIT license\n");
            exit(AppExitOk);
        }
        // --source_file
        if (strcmp(argv[i], "--source_file") == 0) {
            i++;
            if (i + 1 <= argc) {
                i7hProcessorFile(argv[i]);
            } else {
                puts("Flag value ERROR");
                exit(AppExitGetFlag);
            }
            exit(AppExitOk);
        }
        // --stdin
        if (strcmp(argv[i], "--stdin") == 0) {
            i7hProcessorStdin();
            exit(AppExitOk);
        }
        // --
        if (strcmp(argv[i], "--") == 0) {
            i7hProcessorArgv(argc, argv, ++i);
            exit(AppExitOk);
        }
        // default
        puts("ERROR: Invalid Flag");
        exit(AppExitGetFlag);
    }

    // last default
    puts("ERROR: Unknow Error");
    exit(AppExitStd);
}
