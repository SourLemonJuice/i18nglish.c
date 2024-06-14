#include "main.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

int i7h_processor_argv(int argc, char *argv[], int argc_begin)
{
    if (argc_begin > argc - 1) {
        puts("ERROR: Parameter invalid.");
        exit(AppExitGetFlag);
    }

    // create and init i7h data
    struct I7hDataStruct i7h_data;
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;
    // process all arguments
    for (int i = argc_begin; i < argc; i++) {
        // call the main function
        if ((i7h_proc_result = i7hProcessor(&i7h_data, argv[i])) == 0) {
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

int i7h_processor_file(char *file_path)
{
    // file stuff
    FILE *file_handle = fopen(file_path, "r");
    char next_char;
    char temp_string[1024 * 2]; // TODO I'm tired... no one will input more than 4 KiB chars.

    // create i7h data(buffer)
    struct I7hDataStruct i7h_data;
    // init structure
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;

    // TODO Can this detecter be rewritten as a macro?
    while ((next_char = getc(file_handle)) != EOF) {
        // separate all speace/lineBreaks char
        if (next_char == ' ' or next_char == '\n')
            continue;
        else
            ungetc(next_char, file_handle); // this char just used for detect EOF

        /*  great debug code
            printf("%d\n", fscanf(file_handle, "%s", temp_string)); */
        fscanf(file_handle, "%s", temp_string);
        // call the main function
        if ((i7h_proc_result = i7hProcessor(&i7h_data, temp_string)) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            exit(i7hProcessorExitLog(temp_string, i7h_proc_result));
        }
    }
    printf("\n");

    // to free something
    i7hFreeStructure(&i7h_data);
    fclose(file_handle);

    return 0;
}

int i7h_processor_stdin(void)
{
    char next_char;
    char temp_string[1024 * 2]; // TODO same like i7h_processor_file()

    struct I7hDataStruct i7h_data;
    i7hInitStructure(&i7h_data);
    int i7h_proc_result;

    // Sames like i7h_processor_file, here is just copy
    while ((next_char = getc(stdin)) != EOF) {
        if (next_char == ' ' or next_char == '\n')
            continue;
        else
            ungetc(next_char, stdin); // EOF detect

        fscanf(stdin, "%s", temp_string);
        if ((i7h_proc_result = i7hProcessor(&i7h_data, temp_string)) == 0) {
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
            printf("Version: %s\n", APP_VERSION_STRING);
            printf("Build Date: %s, Time: %s\n", __DATE__, __TIME__);
            printf("Git commit: %s\n", APP_GIT_COMMIT_INFO);
            printf("By 酸柠檬猹/SourLemonJuice 2024\n");
            printf("Published under MIT license\n");
            exit(AppExitOk);
        }
        // --source_file
        if (strcmp(argv[i], "--source_file") == 0) {
            i++;
            if (i + 1 <= argc) {
                i7h_processor_file(argv[i]);
            } else {
                puts("Flag value ERROR");
                exit(AppExitGetFlag);
            }
            exit(AppExitOk);
        }
        // --stdin
        if (strcmp(argv[i], "--stdin") == 0) {
            i7h_processor_stdin();
            exit(AppExitOk);
        }
        // --
        if (strcmp(argv[i], "--") == 0) {
            i7h_processor_argv(argc, argv, ++i);
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
