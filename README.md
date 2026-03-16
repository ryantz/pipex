*This project has been created as part of the 42 curriculum by ryatan

# PIPEX

## Description

This project focuses on handling pipes in the format equivalent to:
```shell
< file1 cmd1 | cmd2 > file2
```

Where `file1` and `file2` are filenames, and `cmd1` and `cmd2` are shell commands with their parameters.

---

## Allowed Functions

### File Operations
| Function | Description |
|----------|-------------|
| `open()` | Open a file |
| `close()` | Close a file descriptor |
| `read()` | Read from a file descriptor |
| `write()` | Write to a file descriptor |

### Memory
| Function | Description |
|----------|-------------|
| `malloc()` | Allocate memory |
| `free()` | Free allocated memory |

### Error Handling
| Function | Description |
|----------|-------------|
| `perror()` | Prints a human-readable error message based on the current `errno`. Called when a syscall like `fork()`, `execve()`, or `pipe()` fails. |
| `strerror()` | Converts an error number into a human-readable string. Unlike `perror()`, it returns a string rather than printing it — useful for formatting custom error messages (e.g. `errno` → `strerror(errno)` → `"Permission denied"`). |

### Process Management
| Function | Description |
|----------|-------------|
| `fork()` | Creates a new child process. After `fork()`, two identical processes exist. |
| `execve()` | Replaces the current process with another program. Does not create a new process — used after `fork()` in the child. |
| `exit()` | Terminates the current process. |
| `wait()` | Pauses the parent process until any child finishes. Without it, finished children become zombie processes. |
| `waitpid()` | Waits for a specific child process by PID. Offers more control than `wait()`, including non-blocking checks. |
| `pipe()` | Creates a communication channel between processes. Returns two file descriptors: `fd[0]` (read end) and `fd[1]` (write end). |
| `access()` | Checks if a file exists or if the process has permission to use it (e.g. verifying a command exists in `/usr/bin/`). |

### File Descriptor Manipulation
| Function | Description |
|----------|-------------|
| `dup()` | Duplicates a file descriptor. Both fds refer to the same open file. |
| `dup2()` | Duplicates a file descriptor into a specific descriptor number — core to redirection (e.g. `dup2(pipe_write, STDOUT)` redirects stdout into the pipe). |
| `unlink()` | Deletes a file from the filesystem (equivalent to `rm file.txt`). Used for cleanup. |

---

## Typical Command Execution Flow
```c
pipe()
fork()
    // Child process:
    dup2()    // Redirect I/O
    execve()  // Run the command
    exit()    // If exec fails

    // Parent process:
    waitpid() // Wait for child to finish
```

---

## Instructions

## Resources
