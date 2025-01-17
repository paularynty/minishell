#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * g_mrworldwide - A global volatile variable used for signal handling.
 *
 * This global variable of type `volatile sig_atomic_t` is used to safely 
 * communicate between signal handlers and the main program. It ensures 
 * atomic access to the variable, which is important for signal processing.
 */
extern volatile sig_atomic_t	g_mrworldwide;

/**
 * struct s_mini - Contains data needed for the shell's execution.
 * 
 * @env: Pointer to the environment variables array.
 * @cmd_count: The number of commands to execute in the current pipeline.
 * @cwd: The current working directory of the shell.
 * @input: The raw input string from the user.
 * @pipes: A 2D array representing pipe file descriptors.
 * @pids: An array of PIDs for child processes in the pipeline.
 * @exit_code: The exit code of the last executed command.
 * 
 */
typedef struct s_mini
{
	char	**env;
	int		cmd_count;
	char	*cwd;
	char	*input;
	int		**pipes;
	int		*pids;
	int		exit_code;
}	t_mini;

/**
 * enum e_builtins - Enum representing supported builtin commands.
 *
 * @BUILTIN_NONE: No builtin command.
 * @BUILTIN_CD: Represents the `cd` command.
 * @BUILTIN_ECHO: Represents the `echo` command.
 * @BUILTIN_ENV: Represents the `env` command.
 * @BUILTIN_EXIT: Represents the `exit` command.
 * @BUILTIN_EXPORT: Represents the `export` command.
 * @BUILTIN_PWD: Represents the `pwd` command.
 * @BUILTIN_UNSET: Represents the `unset` command.
 */
enum e_builtins
{
	BUILTIN_NONE,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET
};

/**
 * enum e_token_type - Enum representing different token types in the shell.
 *
 * @CMD: Represents a command token (e.g., "ls", "echo").
 * @FILENAME: Represents a filename token.
 * @REDIR_IN: Represents an input redirection token (e.g., `<`).
 * @REDIR_OUT: Represents an output redirection token (e.g., `>`).
 * @REDIR_APPEND: Represents an append redirection token (e.g., `>>`).
 * @HEREDOC: Represents a heredoc redirection token (e.g., `<<`).
 * @DELIMITER: Represents a delimiter token for heredocs.
 *
 * This enum is used to categorize tokens parsed from the input string.
 */
typedef enum e_token_type
{
	CMD,
	FILENAME,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	DELIMITER
}	t_token_type;

/**
 * struct s_token - Represents a parsed token from the shell's input.
 *
 * @type: The type of the token, as defined by `e_token_type`.
 * @value: The string value of the token (e.g., "echo", "file.txt").
 * @next: Pointer to the next token in the linked list.
 *
 * Tokens are parsed from the shell's input and represent individual components
 * of a command, such as commands, filenames, or redirection operators. This 
 * structure is used to construct a linked list of tokens.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/**
 * struct s_cmd - Represents a command in the shell's pipeline.
 *
 * @tokens: Pointer to the list of tokens for the command.
 * @cmds: An array of command arguments (e.g., {"ls", "-l", NULL}).
 * @input_fd: The input file descriptor for the command.
 * @output_fd: The output file descriptor for the command.
 * @saved_stdin: Saved copy of the standard input file descriptor.
 * @saved_stdout: Saved copy of the standard output file descriptor.
 * @cmd_i: The index of the command in the pipeline.
 * @next: Pointer to the next command in the pipeline.
 *
 * This structure represents a single command and its associated data within 
 * a pipeline. It includes information about tokens, file descriptors, and 
 * its position in the pipeline.
 */
typedef struct s_cmd
{
	t_token			*tokens;
	char			**cmds;
	int				input_fd;
	int				output_fd;
	int				saved_stdin;
	int				saved_stdout;
	int				heredoc_i;
	int				cmd_i;
	struct s_cmd	*next;
}	t_cmd;

#endif