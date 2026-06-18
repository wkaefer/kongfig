# kongfig.py — filesystem-native key/value config for Python
#
# Keys are symlink names; values are symlink targets.
# Storage root: $KONGFIG  (defaults to $HOME/.kongfig)
#
# Usage:
#   from kongfig import get_kongfig, set_kongfig
#
#   set_kongfig("myapp", "theme", "dark")
#   val = get_kongfig("myapp", "theme")   # → "dark"
#
# Drop this file into any Python project. No dependencies beyond stdlib.

import os

KONGFIG_MAX_KEYSIZE = 512
KONGFIG_MAX_VALSIZE = 512


def _kongpath(app: str, key: str) -> str | None:
    """Resolve the filesystem path for a given app/key pair.

    Returns the full symlink path, creating the namespace directory if
    needed. Returns None on any validation failure (mirrors C behaviour).
    """
    if app is None:
        app = ""
    if not key:
        return None
    if len(key) >= KONGFIG_MAX_KEYSIZE:
        return None

    root = os.environ.get("KONGFIG") or os.path.join(
        os.environ.get("HOME", "./"), ".kongfig"
    )

    os.makedirs(root, mode=0o755, exist_ok=True)

    if app:
        namespace = os.path.join(root, app)
        os.makedirs(namespace, mode=0o755, exist_ok=True)
        return os.path.join(namespace, key)
    else:
        return os.path.join(root, key)


def get_kongfig(app: str, key: str) -> str | None:
    """Read a kongfig value.

    Returns the value string, or None if the key does not exist or on
    any error. Mirrors get_kongfig(app, key) from libkongfig.c.
    """
    path = _kongpath(app, key)
    if path is None:
        return None
    try:
        value = os.readlink(path)
    except OSError:
        return None
    if len(value) >= KONGFIG_MAX_VALSIZE:
        return None
    return value


def set_kongfig(app: str, key: str, value: str) -> str | None:
    """Write a kongfig value.

    Creates or replaces the symlink at app/key → value. Returns the
    stored value on success, None on failure. Mirrors set_kongfig(app,
    key, value) from libkongfig.c.
    """
    if value is None:
        return None
    path = _kongpath(app, key)
    if path is None:
        return None
    try:
        os.symlink(value, path)
    except FileExistsError:
        os.remove(path)
        os.symlink(value, path)
    except OSError:
        return None
    return get_kongfig(app, key)
