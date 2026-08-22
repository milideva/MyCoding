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
