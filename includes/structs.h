#ifndef STRUCTS_H
# define STRUCTS_H

//global variable to carry the exit status. mrworldwide for now
//sig_atomic_t = atomic relative to signal handling
//(we can also just pass around the exit code in the struct, 
//let's decide on that later)
extern int	g_mrworldwide;

typedef struct s_mini
{
	char	**env;
	int		cmd_count;
	char	*cwd;
	char	*input;
	char	*heredoc;
	int		**pipes;
	int		std[2];
	int		*pids;
	int		exit_flag; // flag to check if minishell loop should be exited
	int		exit_code; //exit status to exit the entire program with
	int		abort;
}	t_mini;

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

/*Determines token type of each token. */
typedef enum e_token_type
{
	CMD,            // Command and arguments
	FILENAME,       // Filename
	REDIR_IN,    	// Input redirection ("<")
	REDIR_OUT,   	// Output redirection (">")
	REDIR_APPEND,	// Append redirection (">>")
	HEREDOC, 		// Heredoc ("<<")
	DELIMITER 		// EOF after heredoc
} t_token_type;

/*Token structure which holds token type (CMD, REDIR etc.)
and token value ("echo", "file.txt", etc.).*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;

/*cmd structure.*/
typedef struct	s_cmd
{
	t_token	*tokens;    	// Linked list of tokens for the command
	char	**cmds;      	// 2D array of command and its arguments
	int		input_fd;       // Input redirection file descriptor
	int		output_fd;      // Output redirection file descriptor
	int		saved_stdin;	// Place for saving stdin when redirecting input in parent process
	int		saved_stdout;	// Place for saving stdin when redirecting output in parent process
	int		cmd_i;
	struct s_cmd	*next; // Next command (if part of a chain, separated by pipes)
} t_cmd;

#endif