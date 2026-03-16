*This project has been created as part of the 42 curriculum by ryatan

# PIPEX

## Description

This project focuses on handling pipes in the format equivalent to:
 ```shell
< file1 cmd1 | cmd2 > file2
```
Where:
    file1 and file2 are filenames.
    cmd1 and cmd2 are shell commands with their parameters.

### Allowed functions to use and their descriptions

file operations: open, close, read
printing: write
memory: malloc, free

perror(): print a readable error message based on the current errno.
          when a syscall fails, it sets a global var errno.
          perror() prints a message that describes that error.
          (used if syscall fork(), execve(), pipe() etc fails)

strerror(): convert an error number into a human-readable string.a
            unlike perror as it returns a strong not print it.
            formatting own error messages
            errno -> strerror(errno) -> "Permission denied"

access(): check if files exists of permissions to use it. (before executing a
          command check if it exists in path /usr/bin/

dup(): duplicate a file descriptor. Both fd will refer to the same open file

dup2(): duplicate file descriptor into a specific descriptor number (core for
        redirection. dup2(pip_write, STDOUT) : stdout -> pipe : cmd1 | cmd2

execve(): Replace the current process with another program. Does not create
          a new process. fork() -> child: execve() -> becomes new program

exit(): terminates current process

fork(): process creation, creates new child. After fork(), will have 2 of the 
        same processes.

pipe(): create a communication channel between processes. Returns two fds.
        fd[0] -> read, fd[1] -> write
        processA -> pipe -> processB
        processA | processB

unlink(): Delete a file from the filesystem. (rm file.txt)
          used for cleanup

wait(): Pause parent process until any child finishes. If not used child
        child processes become zombie processes.
        parent -> wait() -> child finishes

waitpid(): wait for a specific child process. More control than wait().
           pass the PID of the child you want to wait for. 
           Allows non-blocking checks, waiting for specific children

Typical command exec:

        pipe()
        fork()
            child:
                dup2() - redirection of IO
                execve() - run command
                exit() - if exec fails

            parent:
                waitpid()

## Instructions
## Resources
