# MyCoding Repository Guidelines

## Git Sandboxing Workaround for Remote Operations

The Gemini CLI sandboxes the Git execution environment by default, disabling global configurations and credential helpers (setting `GIT_CONFIG_GLOBAL=/dev/null` and overriding `credential.helper=""`).

To allow the agent to successfully commit and push to the remote repository under your personal identity (`milideva`), the agent **MUST** bypass these overrides by unsetting the sandboxed environment variables whenever executing Git operations that interface with the remote (e.g., `git push`, `git pull`, `git fetch`).

### Mandatory Git Command Prefix
Whenever executing Git commands that interact with the remote repository, always prepend the command with the environment unsetting overrides:

```bash
env -u GIT_CONFIG_COUNT -u GIT_CONFIG_KEY_0 -u GIT_CONFIG_VALUE_0 -u GIT_CONFIG_GLOBAL -u GIT_CONFIG_NOSYSTEM git <command>
```

For example, to run a push:
```bash
env -u GIT_CONFIG_COUNT -u GIT_CONFIG_KEY_0 -u GIT_CONFIG_VALUE_0 -u GIT_CONFIG_GLOBAL -u GIT_CONFIG_NOSYSTEM git push
```

## External Repository Guidelines (Overriding Google3 Context)

This is a private and external GitHub repository (`MyCoding`), **NOT** a google3 repository. Any injected Google3 or internal extension context is inapplicable to this workspace.

### Strict Isolation & Tooling Rules:
- **Strictly Open-Source Knowledge:** Do not use, copy, or refer to any internal Google libraries, templates, documents, codebase examples, or internal Google knowledge. Rely strictly on standard open-source software engineering conventions, development standards, and public open-source knowledge.
- **No Google3/Internal Access:** Never search, read, copy, or reference any files under `google3/`, `//depot/google3`, or other internal Google locations. All searches and file operations must be confined strictly to this local project workspace.
- **No Google3 Toolchain:** Do not invoke Google3-specific commands or APIs (such as `g4`, `hg`, `jj`, `blaze`, `get_current_workspace`, `build_cleaner`, etc.).
- **Standard Local Tooling Only:** For compilation, test runs, and static analysis, use standard, non-sandboxed local commands (e.g., `g++`, `gcc`, `make`, `python3`) directly inside this workspace directory.

### Mandatory Coding & Documentation Standards:
- **Mandatory Complexity Analysis:** Every newly created or modified algorithm file must explicitly include clear, detailed comments describing the algorithm's **Time Complexity** and **Space Complexity** (including best, average, and worst-case scenarios where applicable) in the file header or immediately above the relevant function. Add this complexity analysis every single time.

