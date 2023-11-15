Simple Shell

This is a UNIX command line interpreter, also known as a shell. It allows you to interact     with your computer by typing commands in a text-based interface.
Table of Contents

	Features
	Getting Started
	Usage
	Built-in Commands
	Shell Operators
	Variables
	Comments
	File Input
	Contributing

Features

	Display a prompt and wait for the user to type a command. The command line always ends     with a new line.
	The prompt is displayed again each time a command has been executed.
	Execute command lines with or without arguments.
	Handle errors gracefully, including when an executable cannot be found.
	Implement the built-in exit command to exit the shell.
	Implement the built-in env command to print the current environment.
	Write a custom getline function to handle user input efficiently.
	Handle command separators (;).
	Implement logical operators (&& and ||).
	Define aliases using the alias command.
	Handle variables replacement, including special variables like $? and $$.
	Support comments in the form of #.

Getting Started

To use the Simple Shell, follow these steps:

	Clone the repository to your local machine.
	Compile the source files.
	Run the shell executable.

Usage

Once the shell is running, you can start typing commands. Here are some examples:

sh
$ ls -l
$ cd /path/to/directory
$ echo "Hello, World!"

Built-in Commands

The shell supports the following built-in commands:

	exit: Exit the shell.
	env: Print the current environment.
	setenv VARIABLE VALUE: Initialize a new environment variable or modify an existing one    .
	unsetenv VARIABLE: Remove an environment variable.
	cd [DIRECTORY]: Change the current directory of the process.
	cd -: Change to the previous directory.

Shell Operators

The shell supports the following operators:

	;: Separates commands, allowing multiple commands on a single line.
	&&: Executes the second command only if the first command succeeds.
	||: Executes the second command only if the first command fails.

Variables

The shell supports variable replacement. Additionally, it provides the following special v    ariables:

	$?: Represents the exit status of the last command.
	$$: Represents the current process ID.

Comments

Comments in the shell start with #. Anything following the # on a line is treated as a com    ment and is ignored by the shell.

sh

# This is a comment

echo "Hello, World!" # This is also a comment

File Input

You can pass a file as a command line argument to the shell. The file should contain one c    ommand per line. The shell will execute the commands in the file before exiting. In this m    ode, the shell will not print a prompt and will not read from stdin.

sh

$ ./simple_shell my_commands.txt

Contributing

If you'd like to contribute to the development of this shell, please follow our contributi    on guidelines.
