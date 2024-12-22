#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_mini t_mini;

// Token types (no need for AND/OR)
typedef enum e_token_type
{
	CMD,            // Command name
	FILENAME,       // Filename
	REDIRECT_IN,    // Input redirection ("<")
	REDIRECT_OUT,   // Output redirection (">")
	REDIRECT_APPEND,// Append redirection (">>")
	HEREDOC, 		// ("<<")
	DELIMITER 		// EOF after heredoc
} t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;  // Type of the token (CMD, ARG, etc.)
	char	*value;// Token value (e.g., "echo", "file.txt")
	struct s_token	*next;
} t_token;

// Command structure
typedef struct	s_command
{
	t_token	*tokens;    // Linked list of tokens for the command
	int		input_fd;       // Input redirection file descriptor
	int		output_fd;      // Output redirection file descriptor
	int		cmd_i;
	int		cmd_count;
	struct s_command	*next; // Next command (if part of a chain, separated by pipes)
} t_command;

//lexer/expansion.c
char		*expand_exitcode(t_mini *shell, char *input, int *i);
char		*expand_input(t_mini *shell, char *input);
char		*expand_variable(t_mini *shell, char *input, int *i);
char		*get_variable(t_mini *shell, char *key, int key_len);
char		*replace_segment(char *input, int start, int end, char *replacement);

//lexer/lexer.c
int 		valid_input(char *input);
int 		lexer(t_mini *shell, char *line);

//lexer/valid_input.c
int			closed_pipes(const char *input);
int			matching_quotes(const char *str);
int 		str_is_whitespace(const char *str);
int			valid_pipes(const char *input);
int 		valid_redirection(const char *input);

//lexer/valid_input2.c
int			backslash(const char *input);

//parser/helper_funcs.c
int			char_is_whitespace(char c);
void		free_2d_array(char **array);
int			count_pipes(const char *input);
void	    print_list(t_command *commands);

//parser/free_cmd_contents.c
void		free_commands(t_command *commands);
void		free_tokens(t_token *tokens);
int			quotes_offset(const char *input, char quote);

//parser/create_command.c
t_command	*create_command(char *cmd_str, int pipes, int i);

//parser/create_tokens.c
void		add_token(t_token **head, t_token *new_token);
int			tokenize_args(t_command *command, char **args);

//parser/create_command_args.c
char		**split_cmd_args(char *cmd_str);

//parser/create_quoted_arg.c
char		*create_quoted_arg(char *str, int *i, int len);

//parser/split_by_pipes.c
char		**split_by_pipes(const char *input, int *pipes);

//parser/parser.c
t_command	*tokenizer(t_mini *shell, const char *input);

#endif