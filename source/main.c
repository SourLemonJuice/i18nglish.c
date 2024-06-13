#include "main.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i7h_processor.h"
#include "error_type.h"

int i7h_processor_argv(int argc, char *argv[], int argc_begin)
{
    if (argc_begin > argc - 1) {
        puts("ERROR: Parameter invalid.");
        exit(APP_ERROR_GET_FLAG);
    }

    // create i7h data
    struct i7h_data_struct i7h_data;
    // process all arguments
    for (int i = argc_begin; i < argc; i++) {
        // call the main function
        if (i7h_processor(&i7h_data, argv[i]) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            printf("Error: Something wrong while processing.\n");
            printf("Loop cycles is %d, string: %s\n", i, argv[i]);
            exit(APP_ERROR_STD);
        }
    }
    printf("\n");
    // free the buffer
    i7h_reset_structure(&i7h_data);

    return 0;
}

int i7h_processor_file(char *file_path)
{
    // file stuff
    FILE *file_handle = fopen(file_path, "r");
    char temp_string[128];

    // create i7h data
    struct i7h_data_struct i7h_data;

    while (not feof(file_handle) != 0 or ferror(file_handle) != 0) {
        fscanf(file_handle, "%s", temp_string);
        // call the main function
        if(i7h_processor(&i7h_data, temp_string) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            printf("Error: Something wrong while processing.\n");
            printf("String: %s\n", temp_string);
            exit(APP_ERROR_STD);
        }
    }
    printf("\n");

    // free something
    i7h_reset_structure(&i7h_data);
    fclose(file_handle);

    return 0;
}

int i7h_processor_stdin(void)
{
    char temp_string[128];
    struct i7h_data_struct i7h_data;

    while (not feof(stdin) != 0 or ferror(stdin) != 0) {
        fscanf(stdin, "%s", temp_string);
        if (i7h_processor(&i7h_data, temp_string) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            exit(APP_ERROR_STD);
        }
    }
    printf("\n");

    return 0;
}

int main(int argc, char *argv[])
{
    // handle CLI inputs
    if (argc < 2) {
        puts("ERROR: Need some arguments, use \"--help\" flag to check more info.");
        exit(APP_ERROR_GET_FLAG);
    }
    // flags
    // TODO This handle way was not good, right?
    for (int i = 1; i < argc; i++) {
        // --help
        if (strcmp(argv[i], "--help") == 0) {
            puts("All flags/arguments are unstabled.");
            puts("--help | --version | -- <string> <...> | --source_file <filePath> | --stdin");
            exit(EXIT_SUCCESS);
        }
        // --version
        if (strcmp(argv[i], "--version") == 0) {
            printf("Version: %s\n", APP_VERSION_STRING);
            printf("Build Date: %s, Time: %s\n", __DATE__, __TIME__);
            printf("Git commit: %s\n", APP_GIT_COMMIT_INFO);
            puts("By 酸柠檬猹/SourLemonJuice 2024");
            puts("Published under MIT license");
            exit(EXIT_SUCCESS);
        }
        // --source_file
        if (strcmp(argv[i], "--source_file") == 0) {
            i++;
            if (i + 1 <= argc) {
                i7h_processor_file(argv[i]);
            } else {
                puts("Flag value ERROR");
                exit(APP_ERROR_GET_FLAG);
            }
            exit(EXIT_SUCCESS);
        }
        // --stdin
        if (strcmp(argv[i], "--stdin") == 0) {
            i7h_processor_stdin();
            exit(EXIT_SUCCESS);
        }
        // --
        if (strcmp(argv[i], "--") == 0) {
            i7h_processor_argv(argc, argv, ++i);
            exit(EXIT_SUCCESS);
        }
        // default
        puts("ERROR: Invalid Flag");
        exit(APP_ERROR_GET_FLAG);
    }

    // last default
    puts("ERROR: Unknow Error");
    exit(APP_ERROR_STD);
}
