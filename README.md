# i18nglish.c

Or AKA `i7h.c`.\
This is a transplant of [RimoChan/i7h](https://github.com/RimoChan/i7h), to support c language.\
**Please** check the README of the original repository to get more details about `i18nglish`.

It's just an English joke program, but did you want to look at the code details?

## What's getting better

- Faster, of course. It's a C program not a Python script.
- Yeah... Anyway, it's built with C.

I'm learning C-language, so it's a great way to practice language and learn how to build CI workflow.\
I have also learned a lot of stuff about memory manager, really thanks to this project.

This project really added a lot of useful peripheral components, like CI/code-style/medium-Makefile/WindowsAndUnix-Build

A great gift for me.

## Use in Command Line Utility

### Build

For linux, goto `source/` folder, and run `make`.\
The executable file will named `i18nglish.out`. At now, the compiler is `clang`.

But for Microsoft Windows, I don't have too many ideas. I don't want to use MSVC because the complier's flags are very different.\
So now, my choice is MinGW-w64(MSYS2) in Windows OS. Goto MSYS2 bash and run `make i18nglish.exe` to build the *.exe* file, as for garbled-character Bug... just ignore them.

If need to compile a release version, run make with the argument `releaseBuild=1`.

In addition, GitHub Workflow and Release may already have the latest executable artifact that can be download(Windows/Linux).

### How to use

#### Simply start

You can run it with `--help` to get all flags.\
um... In simplest case, it looked like...

```text
$ ./i18nglish.out --mode arguments hello world
h3o w3d
```

#### All flags/arguments

```text
$ ./i18nglish.out --help
NOTE: Flags are just half stable
Usage: i18nglish [--version] [--help] --mode <MODE> [args]

MODE(for set input source):
        arguments       Use all arguments after it
        file <path>     Read a text file
        stdin   Same 'file' but use stdin
```

### Precautions

stdin/file mode only can process words with a maximum length of (1024 * 1) chars. This limit defined in *source/main.h*\
Although there is no **word**(separated with `space` and `\n`) as long as this.

Only use for ASCII(single char type) characters, don't do this:

```shell
./i18nglish.out --mode arguments 这种字符串 或者 —
```

If it happened, I wouldn't care of them.\
Maybe, the error looked like: `�16�`\
This program just an English joke, so it's should be fine.

## Move main functions to other project

All the functions/defines you need are in *source/i7h/i7h_processor.c and .h*

The main process function is `i7hProcessor()`, this is its prototype:

```c
int i7hProcessor(struct I7hDataStruct i7h_D[restrict], const char src_string[]);
```

And the structure `I7hDataStruct`, it's like a buffer of processor.

When the `i7hProcessor()` is called, it'll auto resize the buffer in structure.\
The caller doesn't need to free the buffer in every loop. But **must**:\
call `i7hInitStructure()` at the START of the loop\
call `i7hFreeStructure()` at the END of the loop to free them

See usage details in *source/main.c*

## Other Idea

Ah..\
If just use it in CLI/stdout, you can do it this way(untested):

```c
int src_string_length = strlen(src_string); // get length

putc(src_string[0], stdout); // first char
printf("%d", src_string_length - 2); // the numbers between
putc(src_string[src_string_length - 1], stdout); // last char
putc('\n');
```

Maybe I'll put them to *main.c* at later.

## Todo List

> Todo list is for myself, not for showing off. The history todo only needs stored in git history.

- Unit test(only for core processor)

## Code style

Variable names reference [Google Style Guide C++](https://google.github.io/styleguide/cppguide.html)(or just want to be).\
Most block styles are from Linux kernel.

The clang-format config has already been added to the repo, but it may still be incomplete.

## Just put something at last

![Build CI Badge](https://github.com/SourLemonJuice/i18nglish.c/actions/workflows/Build.yml/badge.svg)

## License

Published Under MIT License.
