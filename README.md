# i18nglish.c

Or AKA `i7h.c`.\
This is a transplant of [RimoChan/i7h](https://github.com/RimoChan/i7h), to support c language.\
**Please** check the README of the original repository to get more details about `i18nglish`.

## What's getting better

- Faster, of course. It's a C program not Python script.
- Yeah... Anyway, it's built with C.
- Anyway, I'm learning C-language, so it's a great way to practice language and learn how to build CI workflow.

## Use in Command Line

### Build

Goto `source/` folder, and run `make`.\
The executable file will named `i18nglish.out`.

When all is stabled, I'll release the binary file.

### How to use

#### Simply start

You can run it with `--help` to get all flags.\
um... In simplest case it looked like...

```text
$ ./i18nglish.out -- hello world
h3o w3d
```

#### Flags/Arguments

```text
$ ./i18nglish.out --help
All flags/arguments are unstabled.
--help | --version | -- <string> <...> | --source_file <filePath> | --stdin
```

NOTE: All flags are unstabled!!!

## Move function to you programe

All the functions/defines you need are in *source/i7h_processor.c / .h*

The main process function is `i7h_processor`, this is its prototype:

```c
int i7h_processor(struct i7h_data_struct i7h_data[restrict], const char src_string[]);
```

And the structure `i7h_data_struct`:

```c
struct i7h_data_struct
{
    char *buffer;
    size_t buffer_size;
};
```

When the `i7h_processor` is called it'll auto `malloc()` the buffer with the right size.\
Caller doesn't need to free the buffer in every loop. But **must** call `i7h_reset_structure()` at the END of the loop to free them.

See usage details in *source/main.c*

## Other Idea(implementation)

Why is this word so long?

Ah..\
If just use it in CLI/stdout, you can do it this way(untested):

```c
int src_string_length = strlen(src_string); // get length

putc(src_string[0], stdout); // first char
printf("%d", src_string_length - 2); // the numbers between
putc(src_string[src_string_length - 1], stdout); // last char
putc('\n');
```

## Todo List

- Improve the way to handle CLI flags
- Add clang-format config
- Github CI
- Punctuation is not part of the word

## License

Published Under MIT License.
