#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_mini t_mini;

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

/*Command structure.*/
typedef struct	s_command
{
	t_token	*tokens;    	// Linked list of tokens for the command
	char	**cmd;      	// 2D array of command and its arguments
	int		input_fd;       // Input redirection file descriptor
	int		output_fd;      // Output redirection file descriptor
	int		cmd_i;
	struct s_command	*next; // Next command (if part of a chain, separated by pipes)
} t_cmd;

//lexer/expansion.c
char		*expand_exit_code(t_mini *shell, char *input, int *i);
char		*expand_input(t_mini *shell, char *input);
char		*expand_variable(t_mini *shell, char *input, int *i);
char		*get_variable(t_mini *shell, char *key, int key_len);
char		*replace_segment(char *input, int start, int end, char *replacement);

//lexer/lexer.c
int 		valid_input(char *input);
int 		lexer(t_mini *shell, char *line);

//lexer/lexer_utils.c
int 		str_is_whitespace(const char *str);
void		error_pipes(int pipes);

//lexer/valid_input.c
int			closed_pipes(const char *input);
int			matching_quotes(const char *str);
int			valid_pipes(const char *input);
int 		valid_redirection(const char *input);

//lexer/valid_input2.c
int			backslash(const char *input);

//parser/parser_utils.c
int 		count_token_type(t_token *tokens, enum e_token_type type);
int			char_is_whitespace(char c);
void		free_2d_array(char **array);
int			count_pipes(const char *input);
void	    print_list(t_cmd *commands);

//parser/free_cmd_contents.c
void		free_commands(t_cmd *commands);
void		free_tokens(t_token *tokens);
int			quote_offset(const char *input, char quote);

//parser/create_command.c
t_cmd	*create_command(char *cmd_str, int i);

//parser/create_tokens.c
void		add_token(t_token **head, t_token *new_token);
int			tokenize_args(t_cmd *command, char **args);

//parser/create_command_args.c
char		**split_cmd_args(char *cmd_str);

//parser/create_quoted_arg.c
char		*create_quoted_arg(char *str, int *i, int len);

//parser/split_by_pipes.c
char		**split_by_pipes(const char *input);

//parser/parser.c
t_cmd	*tokenizer(t_mini *shell, const char *input);

#endif