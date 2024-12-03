# FLS

This library collects utility functions and data structures to use in c programs.
Use cmake to install.

```console
mkdir build
cd build
cmake ..
make install
```

example use:

```c
#include <fls/logger.h>

int main() {
    fls_logger_level_set(FlsINFO);

    fls_logger(FlsDEBUG, "Hello World");
    char *msg = "unexpected";
    fls_logger(FlsWARNING, "something happen: %s", msg);

    return 0;
}
```

link with fls lib on your build system e.g. `clang main.c -lmylib`.

## ROADMAP
 - [ ] v0.1.0: logger.h memory.h collection.h
    - [ ] v0.1.1: string.h (optional. How often we need string slices, concat etc...)
 - [ ] v0.2.0: tokenizer.h json.h
 - [ ] v0.3.0: graphics.h
 - [ ] v1.0.0: ui.h

