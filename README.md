# pipex
Pipex is a small command-line program that emulates the functionality of the shell's pipe feature. It reads input from a file, runs two commands as separate child processes, and then sends the output of the first command as input to the second command. The output is then written to another file. Pipex is implemented using the C programming language and various system calls, such as fork, pipe, dup2, and execve.

## Concepts

1. **Subprocesses:** Let's work with different processes. One for the first command to be executed, and one to the second.For this, we will use the `fork()` function that creates a child process.
2. **Pipes:** To connect the processes, let's use pipes. Pipes are bufffers that allow communication between processes. To create a pipe, we use the `pipe()` function.
3. **Redirection:** To redirect the input and output of the processes, we will use the `dup2()` function.It receives two file descriptors as a parameter, and causes the file descriptor received as a second parameter to be a copy of the file descriptor received as the first parameter. Thus, we can redirect the input and exit of the processes to the pipes.
4. **Execution of commands:** To execute the commands, we will use the `execve()` function. It receives as parameters the path of the executable file, a string array with the command arguments. With this, in the command being called, the process that called it is replaced by the command process.

## How it works

1. The program receives as parameters the name of the `input file`, the `first command`, the `second command`, and the name of the `output file`.
2. The program creates a pipe (read-end `fd[3]` | write-end `fd[4]`).
3. The program creates a child process.
	- It open the input file `fd[5]`.
	- It redirects the stdout `fd[1]` to the pipe `fd[4]`.
	- Then redirects the input file `fd[5]` to the stdin `fd[0]`.
	- Close the read-end of the pipe `fd[3]`.
	- Execute the first command.
	- The output of the first command is written to the pipe because the previous redirection.
	- The child process exits.
4. The program wait for the child process to finish.
5. The program call the parent process.
	- It open the output file `fd[5]`.
	- It redirects the stdin `fd[0]` to the pipe `fd[3]`, that is, the output buffer of the first command.
	- Then redirects the output file `fd[5]` to the stdout `fd[1]`.
	- Close the write-end of the pipe `fd[4]`.
	- Execute the second command.
	- The output of the second command is written to the output because the previous redirection.
	- The parent process exits.
6. If you don't have any errors, the program ends successfully.

## How to use
To compile this program, run the following commands:
```bash
make
```
Then, to run the program, run the following command:
```bash
./pipex file1 cmd1 cmd2 file2
```

## Memory leaks test
For test memory leaks, run:
```bash
valgrind --leak-check=full --trace-children=yes ./pipex file1 cmd1 cmd2 file2
```
## Grade: 100 / 100

## Used tests
- PIPEXaminator: https://github.com/mariadaan/PIPEXaminator
- pipex-tester: https://github.com/vfurmane/pipex-tester