# i18nglish.c

Short name is `i7h.c`.\
This is a transplant of [RimoChan/i7h](https://github.com/RimoChan/i7h), to support c language.\
See the original repository/README for more ideas about `i18nglish`.

## What is getting Batter

- Faster, of course. It's a C program not Python.
- Yeah... Anyway, it's built with C.

## Build

Goto `source/` folder, and run `make`.\
The executable file will named `main.out`.

## Command Line Inputs

No `--help` or any flags yet, so I'll put them here first.\
um... It looked like...

```text
$ ./main.out string
s4g
```

And now it only accepts `one` string...\
I'm thinking about this.

## Functions

The main process function is `i7n_processor`, this is it's prototype:

```c
int i7n_processor(char *buffer, size_t buffer_size, const char *src_string)
```

The caller need create a buffer to store the output string.\
Hum, for now I'll leave the jobs to the caller.

## Other Idea(implementation)

Why is this word so long?

Ah..\
If just use it in CLI/Shell/STDOUT, you can do it this way(untested):

```c
int src_string_length = strlen(src_string); // get length

putc(src_string[0], stdout); // first char
printf("%d", src_string_length - 2); // the numbers between
putc(src_string[src_string_length - 1], stdout); // last char
putc('\n');
```

## Todo List

- Muti word input, or file input/output.
- Flags? But what about injection attacks? Use stdin/stdout? Maybe.
- Can we just return a pointer to a string? That way other one can use it easily.

## License

Published Under MIT License.
