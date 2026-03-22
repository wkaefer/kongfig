# libKongfig + kongfig 🦍⚙️

Gorilla-simple configuration using symbolic links as key/value storage. 🔗

- Key = symlink name 🏷️
- Value = symlink target 🎯

C API:

```c
get_kongfig(application, key);
set_kongfig(application, key, value);
```

Storage location:

- Default: `$HOME/.kongfig` 🏠
- Override with environment variable: `KONGFIG` 🌿

This project is intentionally minimal and experimental. 👀

## Why 🧠

- 🦍 Gorilla numbers are sometimes all you need.
- 🦍 Gorilla code is sometimes all you need too.
- 🔧 Filesystem-native config can be inspected with normal tools.

## What Is In This Repo 📦

- `kongfig`: shell CLI using positional arguments (`key` and optional `value`) 🔩
- `libkongfig.c`, `libkongfig.h`: C library API 🧪
- `kongfigtest`, `kongfigtest.c`: test/demo binary and source 🔨
- `makefile`: build/install/test targets 🚂

## Build And Install 🛠️

Build:

```sh
make
```

Install command + man page:

```sh
make install
```

## Correct CLI Usage ✅

### `kongfig` (shell script)

`kongfig` uses positional arguments (not `-k/-v` flags):

```text
kongfig
kongfig <key>
kongfig <key> <value>
```

Behavior:

- `kongfig` → list current entries in `$KONGFIG`
- `kongfig <key>` → show a single key symlink
- `kongfig <key> <value>` → create/update key to point to value

Validation rules:

- Key cannot contain `/` 🚫
- Value cannot contain `/` when assigning with shell `kongfig` 🚫

Note: current script prints `KONGFIG=<path>` on invocation. 📝

### `kongfigtest` (C demo tool)

`kongfigtest` supports option flags:

```text
kongfigtest -k <key>
kongfigtest -k <key> -v <value>
kongfigtest -n <name> -k <key>
kongfigtest -n <name> -k <key> -v <value>
kongfigtest -d
```

Use `-d` to increase verbosity. 🔍

## Examples 💡

Shell `kongfig`:

```sh
KONGFIG=/tmp/kongfig-demo kongfig name "Fred Flintstone"
KONGFIG=/tmp/kongfig-demo kongfig wife Wilma
KONGFIG=/tmp/kongfig-demo kongfig city Bedrock
KONGFIG=/tmp/kongfig-demo kongfig
```

C demo `kongfigtest`:

```sh
KONGFIG=/tmp/kongfig-demo ./kongfigtest -k name -v "Fred Flintstone"
KONGFIG=/tmp/kongfig-demo ./kongfigtest -k name
KONGFIG=/tmp/kongfig-demo ./kongfigtest -n child1 -k name -v Pebbles
```

## Storage Model 🔗

Keys are stored directly under `$KONGFIG` (same in both the shell tool and the C library):

```text
$KONGFIG/<app>/<key>    # app is optional (empty = root level)
```

When `KONGFIG` is not set, both tools default to `$HOME/.kongfig`.

## ToDo / Ideas 🚀

- Validate key/value characters more strictly in library code
- Clarify depth/path semantics (for names like `name.first`)
- Add optional allowed-value files (for example `key.selection`)
- Add optional hook execution on change (for example `key.exec`)
- Support file-backed values for large or binary content

## Files 📚

| File                 | 🧿 | Description                                |
|----------------------|----|--------------------------------------------|
| k5f2.h               | 📑 | Libk5f2                                    |
| kongfig              | 🔩 | Shell Version                              |
| kongfig.1            | 📄 | Man Page                                   |
| kongfigtest          | 🔨 | Test Program                               |
| kongfigtest.c        | 📄 | Test Program                               |
| libkongfig.c         | 📄 | Functions                                  |
| libkongfig.h         | 📑 | Definitions                                |
| makefile             | 🚂 | Instructions                               |
| README2.md           | 📝 | Markdown file                              |
