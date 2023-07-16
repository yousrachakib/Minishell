# Minishell

we are going to create our own shell. staring this project I've readed the bash manual (which is very long but very useful).

## What is Shell?
At its base, a shell is simply a macro processor that executes commands. The term macro processor means functionality where text and symbols are expanded to create larger expressions.
A Unix shell is both a command interpreter and a programming language. As a command interpreter, the shell provides the user interface to the rich set of GNU utilities. 
The programming language features allow these utilities to be combined. Files containing commands can be created, and become commands themselves. 
These new commands have the same status as system commands in directories such as /bin, allowing users or groups to establish custom environments to automate their common tasks.
Shells may be used interactively or non-interactively. In interactive mode, they accept input typed from the keyboard. When executing non-interactively, shells execute commands read from a file.
A shell allows execution of GNU commands, both synchronously and asynchronously. The shell waits for synchronous commands to complete before accepting more input; 
asynchronous commands continue to execute in parallel with the shell while it reads and executes additional commands. The redirection constructs permit fine-grained control of the input and output of those commands. 
Moreover, the shell allows control over the contents of commands’ environments.
