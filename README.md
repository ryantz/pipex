*This project has been created as part of the 42 curriculum by ryatan.*

# pipex

## Description

pipex is a C program that replicates the behaviour of the shell pipe mechanism. It takes two commands and two files as arguments, executing the first command with the input file as stdin, piping its output into the second command, and writing the final result to the output file.

This is equivalent to the following shell command:

```shell
< file1 cmd1 | cmd2 > file2
```

Where `file1` and `file2` are filenames, and `cmd1` / `cmd2` are shell commands with their parameters.

The project explores UNIX process management concepts including `fork`, `execve`, `pipe`, `dup2`, and file descriptor redirection.

---

## Instructions

### Compilation

```shell
make
```

Other Makefile rules:

```shell
make clean   # remove object files
make fclean  # remove object files and binary
make re      # fclean + make
```

### Execution

```shell
./pipex file1 cmd1 cmd2 file2
```

Examples:

```shell
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep hello" "wc -w" outfile
```

These are equivalent to:

```shell
< infile ls -l | wc -l > outfile
< infile grep hello | wc -w > outfile
```

### Testing

Basic test and comparison against shell:

```shell
echo "hello world" > infile
./pipex infile "cat" "wc -w" outfile
< infile cat | wc -w > expected
diff outfile expected   # should be empty if correct
```

---

## Program Design

### Structs

```c
typedef struct s_commandpaths
{
    char    *cmd1_path;   // full path to cmd1 binary
    char    *cmd2_path;   // full path to cmd2 binary
    char    **cmd1;       // cmd1 split into argv array
    char    **cmd2;       // cmd2 split into argv array
    int     fd_in;        // file descriptor for input file
    int     fd_out;       // file descriptor for output file
}   t_commandpaths;

typedef struct s_filefds
{
    int fd_in;
    int fd_out;
}   t_filefds;
```

### Enums

```c
enum e_error
{
    ERR_NO_FILE,        // no such file or folder
    ERR_INVALID_INPUT,  // wrong number of arguments
};
```

### Functions

#### Error Handling
```c
void            print_error(int err_code);
```

#### Struct Initialisation
```c
int             init_cp_struct(t_commandpaths **cp_struct);
int             init_filefds(t_filefds **file_fds);
```

#### File Operations
```c
t_filefds       *open_create_files(char **argv);
```

#### Path & Command Resolution
```c
char            *get_path(char **envp);
char            *get_command_path(char *full_path, char *command);
t_commandpaths  *get_cp_struct(char **argv, char *full_path, t_filefds *fds);
```

#### Process Management
```c
pid_t           fork_process_cmd1(t_commandpaths *cp_struct, char **envp, int *pipefd);
pid_t           fork_process_cmd2(t_commandpaths *cp_struct, char **envp, int *pipefd);
void            pipex(t_commandpaths *cp_struct, char **envp, int *pipefd);
```

#### Memory Management
```c
int             free_all(char **item);
int             free_struct(t_commandpaths *cp_struct);
```

### Execution Flow

```
pipe()
├── fork() → child 1
│     dup2(fd_in  → stdin)
│     dup2(pipe write end → stdout)
│     execve(cmd1)
│
└── fork() → child 2
      dup2(pipe read end → stdin)
      dup2(fd_out → stdout)
      execve(cmd2)

parent: waitpid() for both children
```

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
| `perror()` | Prints a human-readable error message based on the current `errno` |
| `strerror()` | Converts an error number into a human-readable string |

### Process Management

| Function | Description |
|----------|-------------|
| `fork()` | Creates a new child process |
| `execve()` | Replaces the current process image with a new program |
| `exit()` | Terminates the current process |
| `wait()` | Waits for any child process to finish |
| `waitpid()` | Waits for a specific child process by PID |
| `pipe()` | Creates a unidirectional communication channel between processes |
| `access()` | Checks file existence or execute permission |

### File Descriptor Manipulation

| Function | Description |
|----------|-------------|
| `dup()` | Duplicates a file descriptor |
| `dup2()` | Duplicates a file descriptor into a specific descriptor number |
| `unlink()` | Deletes a file from the filesystem |

---

## Resources

- [fork() system call — CodeVault](https://www.youtube.com/watch?v=xVSPv-9x3gk)
- [pipe() for Linux — CodeVault](https://www.youtube.com/watch?v=uHH7nHkgZ4w)
- [dup() / dup2() system calls — CodeVault](https://www.youtube.com/watch?v=EqndHT606Tw)
- [execve() man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [waitpid() man page](https://man7.org/linux/man-pages/man2/waitpid.2.html)

### AI Usage

Claude (claude.ai) was used during this project for the following:

- Generating this README structure based on the subject requirements
