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
	REDIRECT_APPEND, // Append redirection (">>")
	HEREDOC, // ("<<")
	DELIMETER // EOF after heredoc
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
	struct s_command	*next; // Next command (if part of a chain, separated by pipes)
} t_command;

//lexer/lexer.c
int 		valid_input(char *input);
char		*expand_input(t_mini *minish, char *input);
int 		lexer(t_mini *minish, char *line);

//lexer/valid_input.c
int 		str_is_whitespace(const char *str);
int			char_is_whitespace(char c);
int			matching_quotes(const char *str);
int 		valid_redirection(const char *input);
int			valid_pipes(const char *input);
int			closed_pipes(const char *input);

//parser
void	    print_list(t_command *commands);
void		add_token(t_token **head, t_token *new_token);
int			count_pipes(const char *input);
t_command	*create_command(char *cmd_str);
void		free_2d_array(char **array);
void		free_commands(t_command *commands);
void		free_tokens(t_token *tokens);
char		*ft_strndup(const char *src, size_t n);
int			quotes_offset(const char *input, char quote);
char		*prod_quoted_arg(char *str, int *i, int len);
char		**split_by_pipes(const char *input);
int			tokenize_args(t_command *command, char **args);
t_command	*tokenizer(const char *input);

#endif