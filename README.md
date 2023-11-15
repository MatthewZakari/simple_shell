  1 Simple Shell
  2
  3 This is a UNIX command line interpreter, also known as a shell. It allows you to interact     with your computer by typing commands in a text-based interface.
  4 Table of Contents
  5
  6     Features
  7     Getting Started
  8     Usage
  9     Built-in Commands
 10     Shell Operators
 11     Variables
 12     Comments
 13     File Input
 14     Contributing
 15
 16 Features
 17
 18     Display a prompt and wait for the user to type a command. The command line always ends     with a new line.
 19     The prompt is displayed again each time a command has been executed.
 20     Execute command lines with or without arguments.
 21     Handle errors gracefully, including when an executable cannot be found.
 22     Implement the built-in exit command to exit the shell.
 23     Implement the built-in env command to print the current environment.
 24     Write a custom getline function to handle user input efficiently.
 25     Handle command separators (;).
 26     Implement logical operators (&& and ||).
 27     Define aliases using the alias command.
 28     Handle variables replacement, including special variables like $? and $$.
 29     Support comments in the form of #.
 30
 31 Getting Started
 32
 33 To use the Simple Shell, follow these steps:
 34
 35     Clone the repository to your local machine.
 36     Compile the source files.
 37     Run the shell executable.
 38
 39 Usage
 40
 41 Once the shell is running, you can start typing commands. Here are some examples:
 42
 43 sh
 44
 45 $ ls -l
 46 $ cd /path/to/directory
 47 $ echo "Hello, World!"
 48
 49 Built-in Commands
 50
 51 The shell supports the following built-in commands:
 52
 53     exit: Exit the shell.
 54     env: Print the current environment.
 55     setenv VARIABLE VALUE: Initialize a new environment variable or modify an existing one    .
 56     unsetenv VARIABLE: Remove an environment variable.
 57     cd [DIRECTORY]: Change the current directory of the process.
 58     cd -: Change to the previous directory.
 59
 60 Shell Operators
 61
 62 The shell supports the following operators:
 63
 64     ;: Separates commands, allowing multiple commands on a single line.
 65     &&: Executes the second command only if the first command succeeds.
 66     ||: Executes the second command only if the first command fails.
 67
 68 Variables
 69
 70 The shell supports variable replacement. Additionally, it provides the following special v    ariables:
 71
 72     $?: Represents the exit status of the last command.
 73     $$: Represents the current process ID.
 74
 75 Comments
 76
 77 Comments in the shell start with #. Anything following the # on a line is treated as a com    ment and is ignored by the shell.
 78
 79 sh
 80
 81 # This is a comment
 82 echo "Hello, World!" # This is also a comment
 83
 84 File Input
 85
 86 You can pass a file as a command line argument to the shell. The file should contain one c    ommand per line. The shell will execute the commands in the file before exiting. In this m    ode, the shell will not print a prompt and will not read from stdin.
 87
 88 sh
 89
 90 $ ./simple_shell my_commands.txt
 91
 92 Contributing
 93
 94 If you'd like to contribute to the development of this shell, please follow our contributi    on guidelines.

