### Grep Clone

This a simple clone of linux/unix tool grep written in c for learning and
experimenting.

This uses `regex` and `magic` library under the hood.

### Features

- Print the line in which given pattern is founded.
- Count number of time pattern found.
- Cont number of line where pattern has been found.

### API
`main.c` file isn't necessary for API uses.
`GRET grep(const char* file_path, const char *string_pattern, uint8_t is_print)`

`GRET` stand for Grep Return is a struct.
```c
typedef struct {
    int w_count;
    int l_count;
} GRET;
```

## Enables
- `-w` count number of time pattern repeats.
- `-l` count number of line where pattern has been found.
- Since, it uses regex. Every valid regular expression can be used.

### How to use?
compile: `gcc main.c -o grep -lmagic`
use: `./grep -w pattern test.txt`

