#ifndef PARSER_H
# define PARSER_H

// Token types (no need for AND/OR)
typedef enum e_token_type
{
	CMD,            // Command name
	ARG,            // Argument
	REDIRECT_IN,    // Input redirection ("<")
	REDIRECT_OUT,   // Output redirection (">")
	REDIRECT_APPEND, // Append redirection (">>")
	HEREDOC // ("<<")
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


void		add_token(t_token **head, t_token *new_token);
int			count_pipes(const char *input);
t_command	*create_command(char *cmd_str);
void		free_commands(t_command *commands);
void		free_tokens(t_token *tokens);
char		*ft_strndup(const char *src, size_t n);
int			quotes_offset(const char *input, char quote);
char		**split_by_pipes(const char *input);
int			tokenize_args(t_command *command, char **args);
t_command	*tokenizer(const char *input);
#endif