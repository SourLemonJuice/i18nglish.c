# i18nglish.c

Or AKA `i7h.c`.\
This is a transplant of [RimoChan/i7h](https://github.com/RimoChan/i7h), to support c language.\
**Please** check the README of the original repository to get more details about `i18nglish`.

It's just a joke.

## What's getting better

- Faster, of course. It's a C program not a Python script.
- Yeah... Anyway, it's built with C.

I'm learning C-language, so it's a great way to practice language and learn how to build CI workflow.\
I have also learned a lot of stuff about memory manager, really thanks to this project.

## Use in Command Line

### Build

Goto `source/` folder, and run `make`.\
The executable file will named `i18nglish.out`. For now, the compiler is `clang`.

If need to compile a release version, run make with the argument `releaseBuild=1`.

In addition, GitHub Workflow may already have the latest exec artifact that can be download.

### How to use

#### Simply start

You can run it with `--help` to get all flags.\
um... In simplest case it looked like...

```text
$ ./i18nglish.out -- hello world
h3o w3d
```

#### All flags/arguments

```text
$ ./i18nglish.out --help
All flags/arguments are unstabled.
--help | --version | -- <string> <...> | --source_file <filePath> | --stdin
```

NOTE: All flags are unstable.

### Precautions

stdin/file mode only can process words with a maximum length of (1024 * 1) chars. This limit defined in *source/main.h*\
Although there is no **word**(separated with `space` and `\n`) as long as this.

Only use for ASCII(single char type) characters, don't do this:

```shell
./i18nglish.out -- — 或者这种字符串
```

If it's happend, I won't care of them.\
Maybe, error looked like: `�16�`\
This program just an English joke, so it's should be fine.

## Move main functions to other project

All the functions/defines you need are in *source/i7h_processor.c / .h*

The main process function is `i7hProcessor()`, this is its prototype:

```c
int i7hProcessor(struct I7hDataStruct i7h_D[restrict], const char src_string[]);
```

And the structure `I7hDataStruct`, it's like a buffer of processor.

When the `i7hProcessor()` is called, it'll auto resize the buffer in structure.\
Caller doesn't need to free the buffer in every loop. But **must**:\
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

> Todo list is for myself, not for showing off. The history todo only needs store in git history.

- Unit test(only for core processor)
- Improve the way to handle CLI flags

## Code style

Variable names reference [Google Style Guide C++](https://google.github.io/styleguide/cppguide.html)(or just want to be).\
Most block styles are from Linux kernel.

The clang-format config has already been added to the repo, but it may still be incomplete.

## Just put something at last

![Build CI Badge](https://github.com/SourLemonJuice/i18nglish.c/actions/workflows/Build.yml/badge.svg)

## License

Published Under MIT License.
