# minishell
A lightweight, custom shell written in C, designed to replicate key features and behaviors of Bash. Developed and tested on Linux, `minishell` provides a foundation for understanding shell internals, while supporting a subset of Bash functionality.

---

## **Features**

- **Command Parsing**: Handles single and double quotes for complex input.
- **Redirection**: Supports input (`<`), output (`>`), append (`>>`) and heredoc (`<<`) redirections.
- **Pipelines**: Implements Unix-style piping (`|`).
- **History**: Tracks command history within the session.
- **Environment Variable Expansion**: Supports `$VAR` and `$?` for the last exit status.
- **Signal Handling**: 
  - `Ctrl-C`: Sends interrupt signal.
  - `Ctrl-D`: Sends EOF (exit).
  - `Ctrl-\`: Handled gracefully.
- **Built-in Commands**:
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute paths)
  - `pwd` (prints the current directory)
  - `export` (sets environment variables)
  - `unset` (removes environment variables)
  - `env` (prints environment variables)
  - `exit` (exits the shell)

---

## **Not Implemented**

- `\` (backslash escaping)
- `;` (semicolon for separating commands)
- `&&` and `||` (logical operators)
- Parentheses for priority grouping
- Wildcards (`*` and others)

---

## **Installation**

Clone the repository and build the project using the provided `Makefile`.

```bash
$ git clone https://github.com/your-username/minishell.git
$ cd minishell
$ make
```

---

## **Usage**

Run `minishell` from the terminal after building:

```bash
$ ./minishell
```

### Example:
```bash
$ echo "Hello, world!"
Hello, world!
$ pwd
/home/username/minishell
$ export MYVAR=test
$ echo $MYVAR
test
$ exit
```

---

## **Known Limitations**

- No support for backslash escaping (`\`).
- Logical operators (`&&` and `||`) are not implemented.
- Command grouping with parentheses is unsupported.
- Wildcards are not recognized.

---

## **Team**

This project was developed by:
- **zhedlund** ([GitHub](https://github.com/zhedlund))  
- **jelliott** ([GitHub](https://github.com/jelliott))

---

## **Made For**

- Linux operating systems.

---

## **Acknowledgments**

`minishell` was developed as part of a hands-on exploration of shell internals at 42 Berlin.

---

## **License**

This project is licensed under the [MIT License](LICENSE).
