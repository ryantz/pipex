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
## Useful Shell Commands for Testing

### Simple Input/Output
| Command | Description |
|---------|-------------|
| `cat` | Reads and prints file contents |
| `echo` | Prints a string |
| `ls` | Lists directory contents |
| `wc -l` / `wc -w` | Counts lines / words |

### Filtering & Searching
| Command | Description |
|---------|-------------|
| `grep "pattern"` | Filters lines matching a pattern |
| `head -n 5` | Prints the first 5 lines |
| `tail -n 5` | Prints the last 5 lines |
| `sort` | Sorts lines alphabetically |
| `uniq` | Removes duplicate lines |

### Transformation
| Command | Description |
|---------|-------------|
| `tr 'a-z' 'A-Z'` | Transforms characters (e.g. lowercase to uppercase) |
| `cut -d',' -f1` | Cuts a column from delimited text |
| `rev` | Reverses each line |


```shell
< file1 grep "hello" | wc -l > file2
< file1 cat | grep "error" > file2
< file1 sort | uniq > file2
< file1 head -n 10 | tr 'a-z' 'A-Z' > file2
```

default behavior: cmd1 -> write to its stdout
pipe: point cmd1's stdout to the write end of pipe
default behaviour: cmd2 expects input into its stdin
pipe: point the read end of pipe into cmd2's stdin
cmd 1 -> pipe -> cmd2

## Design of the program

### Enums
```c
enum e_error
{
	ERR_NONE,
	ERR_INVALID_INPUT,
};
```
### Structures
```c
typedef struct s_commandpaths
{
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1;
	char	**cmd2;
	int		fd_in;
	int		fd_out;
}	t_commandpaths;
```
```c
typedef struct s_filefds
{
	int	fd_in;
	int	fd_out;
}	t_filefds;
```
### Created functions
#### Error handling
```c
void			print_error(int err_code);
```
#### Struct inits
```c
int				init_cp_struct(t_commandpaths **cp_struct);
```
```c
int				init_filefds(t_filefds **file_fds);
```
#### File operations
```c
t_filefds		*open_create_files(char **argv);
```
#### Get functions
```c
char			*get_path(char **envp);
```
```c
char			*get_command_path(char *full_path, char *command);
```
```c
t_commandpaths	*get_cp_struct(char **argv, char *full_path, t_filefds *fds);
```
#### Pipex main logic
```c
void			fork_process(t_commandpaths *cp_struct, char **envp,
					int *pipefd, int cmd);
```
#### Memory management
```c
int				free_all(char **item);
```
```c
int				free_struct(t_commandpaths *cp_struct);
```
## Instructions

```c
make
```
```bash
< input_file cmd1 | cmd2 > output_file
```
```c
./pipex input_file cmd1 cmd2 output_file
```
## Resources
Fork() system call tutorial: https://www.youtube.com/watch?v=xVSPv-9x3gk
Pipe() tutorial for linux: https://www.youtube.com/watch?v=uHH7nHkgZ4w
fd, dup()/dup2() system call tutorial: https://www.youtube.com/watch?v=EqndHT606Tw
