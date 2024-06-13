#include "main.h"

#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    i7h_free_structure(&i7h_data);

    return 0;
}

int i7h_processor_file(char *file_path)
{
    // file stuff
    FILE *file_handle = fopen(file_path, "r");
    char next_char;
    char temp_string[10]; // TODO I'm tired... no one will use more than 16 KiB memory.
    // and why processor still can work??? and why when the structure be freed, stack broken!!!
    // is the scanf's problem?

    // create i7h data(buffer)
    struct i7h_data_struct i7h_data;
    // init structure
    i7h_init_structure(&i7h_data);

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
        if (i7h_processor(&i7h_data, temp_string) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            printf("Error: Something wrong while processing.\n");
            printf("String: %s\n", temp_string);
            exit(APP_ERROR_STD);
        }
    }
    printf("\n");

    // to free something
    i7h_free_structure(&i7h_data);
    fclose(file_handle);

    return 0;
}

int i7h_processor_stdin(void)
{
    char next_char;
    char temp_string[1024 * 16]; // TODO same like i7h_processor_file()
    struct i7h_data_struct i7h_data;
    i7h_init_structure(&i7h_data);

    // Sames like i7h_processor_file, here is just copy
    while ((next_char = getc(stdin)) != EOF) {
        if (next_char == ' ' or next_char == '\n')
            continue;
        else
            ungetc(next_char, stdin); // EOF detect

        fscanf(stdin, "%s", temp_string);
        if (i7h_processor(&i7h_data, temp_string) == 0) {
            printf("%s ", i7h_data.buffer);
        } else {
            exit(APP_ERROR_STD);
        }
    }
    printf("\n");

    i7h_free_structure(&i7h_data);

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
            printf("By 酸柠檬猹/SourLemonJuice 2024\n");
            printf("Published under MIT license\n");
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
