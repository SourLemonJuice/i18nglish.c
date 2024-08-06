# i18nglish.c

Or AKA `i7h.c`.\
This is a transplant of [RimoChan/i7h](https://github.com/RimoChan/i7h), to support c language.\
**Please** check the README of the original repository to get more details about `i18nglish`.

Anyway, it's just an English joke program.

## What's getting better

- Faster, of course. It's a C program not a Python script.
- Yeah... Anyway, it's built with C.

I'm learning C language, so it's a great way to practice language and learn how to build CI workflow.\
I have also learned a lot of stuff about memory manager, really thanks to this project.

This project really added a lot of useful peripheral components, like CI, code style, medium makefile, Windows and Linux build.

A great gift for me.

## Using the command line

### Build

For linux, goto `source/` folder, and run `make`.\
The executable file will named `i18nglish.out`. At now, the compiler is `clang`.

But for Microsoft Windows, I don't have too many ideas. I don't want to use MSVC because the complier's flags are very different.\
So now, my choice is MinGW-w64(MSYS2) in Windows OS. Goto MSYS2 bash and run `make i18nglish.exe` to build the *.exe* file.\
And... this output file looked like it can't run in other systems without MSYS2, sorry.

If need to compile a release version, run make with the argument `releaseBuild=1`.

In addition, GitHub Workflow and Release may already have the latest executable artifact that can be download(for Windows/Linux).

### How to use

um... In simplest case, it looked like...

```shell
echo "hello world" | ./i18nglish --mode stdin
# output: h3o w3d
```

It also support `args(arguments)` and `file` mode.\
Run it with `--help` to get all flags

### Precautions

stdin/file mode only can process words with a maximum length of (1024 * 1) chars. This limit defined in *source/main.h*\
Although there is no **word**(separated with `space` and `\n`) as long as this.

Only use for single 8-bit char type characters, don't do this:

```shell
echo "这种字符串 或者仅仅只是 —" | ./i18nglish.out --mode stdin
```

If it happened, I wouldn't care of them.\
The error looked like: `�16�`\
This program just an English joke, so it's should be fine.\
I don't want to adapt to UTF-8 `_(:з」∠)_`

## Using in other project

Be sure to check out the [#Stream parser](#stream-parser), it's a new and better interface

All the functions/defines you need are in *source/i7h/i7h_processor.c and .h*

The main process function is `i7hProcessor()`, this is its prototype:

```c
int i7hProcessor(struct I7hDataStruct i7h_D[restrict], const char src_string[]);
```

And the structure `I7hDataStruct`, it's like a buffer of processor

When the `i7hProcessor()` is called, it'll auto resize the buffer in structure.\
The caller doesn't need to free the buffer in every loop. But **must**:\
call `i7hInitStructure()` at the START of the loop\
call `i7hFreeStructure()` at the END of the loop to free them

See usage details in *source/main.c*

And... it won't delete punctuation with itself

## Stream parser

`i7hParserStream()` is a new interface of this project.\
It gets rid from some crappy frameworks. here's some good thing about it:

- Perfect punctuation detect
- Recognize word more correctly
- Cleaner code!
- Don't need create data structure manually
- Direct processing streams, like `stdin/stdout` or a file handle

Mode `stdin` and `file` are using this interface

## Todo List

> Todo list is for myself, not for showing off. The history todo only needs stored in git history.

- NULL

## Code style

Variable names reference [Google Style Guide C++](https://google.github.io/styleguide/cppguide.html)(or just want to be).\
Most block styles are from Linux kernel.

The clang-format config has already been added to the repo, but it may still be incomplete.

## Just put something at last

![Build CI Badge](https://github.com/SourLemonJuice/i18nglish.c/actions/workflows/Build.yml/badge.svg)

## License

Published Under MIT License.
