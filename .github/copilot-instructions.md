# Copilot Instructions for kongfig

## Build, Test, and Install

```sh
make            # build all: k5f2.h.gch, libkongfig.a, kongfigtest
make clean      # remove build artifacts
make test       # run full test suite (uses a tmp/ directory)
make install    # install kongfig binary + man page to $PREFIX (~/.local)
```

Run a subset of the test manually by setting `KONGFIG` to a temp dir:

```sh
mkdir -p tmp
KONGFIG=tmp ./kongfigtest -k name -v 'Fred'
KONGFIG=tmp ./kongfigtest -k name
rm -rf tmp
```

## Architecture

This project implements a filesystem-native key/value config store. **Keys are symlink names; values are symlink targets** stored under `$KONGFIG` (defaults to `$HOME/.kongfig`).

```
$KONGFIG/           ← root (app="" means keys live directly here)
$KONGFIG/<app>/     ← named application namespace
$KONGFIG/<app>/<key> → <value>   (each entry is a symlink)
```

Components:

- **`k5f2.h`** — Shared utility header providing `error()`, `syserror()`, `verbose()`, and `set_verbose()`. Implementations are gated behind `#define LIBK5F2` (see convention below).
- **`libkongfig.c` / `libkongfig.h`** — C library. Exposes `get_kongfig(app, key)` and `set_kongfig(app, key, value)`. Internally uses a rotating 8-slot string pool (`pool[]`) so returned pointers are only valid until the pool wraps.
- **`kongfig`** — POSIX shell script CLI. Uses **positional arguments** (not flags). Validates that keys and values contain no `/`.
- **`kongfigtest.c`** — C demo/test binary. Uses `-k`/`-v`/`-n`/`-d` option flags via `getopt`.

## Key Conventions

### `k5f2.h` — define-before-include pattern

`#define LIBK5F2` must appear **before** `#include "k5f2.h"` in exactly **one** translation unit (the implementation file). All other files include `k5f2.h` without the define (getting only declarations).

```c
// In the .c implementation file only:
#define LIBK5F2
#include "k5f2.h"
```

### Return value lifetime (string pool)

`get_kongfig()` returns a pointer into a static 8-slot rotating pool. Do not hold the pointer across more than 8 subsequent calls to `get_kongfig()`.

### `KONGFIG` environment variable

Both the shell script and the C library honour `$KONGFIG` as the storage root. Tests set this variable to a scratch directory to avoid touching real config.

### Shell script validation

The shell `isok()` function rejects any key or value containing `/` using a `case` pattern match (not external tools). The C library does **not** perform this validation — keep that asymmetry in mind if extending either side.

### Verbosity

Call `set_verbose()` (or pass `-d` to `kongfigtest`) to enable `verbose()` output on stderr, prefixed with `#🟩`.
