#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

typedef struct s_mini t_mini;
typedef struct s_cmd t_cmd;
typedef struct s_token t_token;
// typedef enum e_token_type t_token_type;

//lexer/expansion.c
char		*expand_exit_code(t_mini *shell, char *input, int *i);
char		*expand_input(t_mini *shell, char *input);
char		*expand_variable(t_mini *shell, char *input, int *i);
char		*get_variable(t_mini *shell, char *key, int key_len);
char		*replace_segment(char *input, int start, int end, char *replacement);

//lexer/lexer.c
int 		valid_input(t_mini *shell, char *input);
int 		lexer(t_mini *shell, char *line);

//lexer/lexer_utils.c
int 		str_is_whitespace(const char *str);
void		error_pipes(t_mini *shell, int pipes);

//lexer/valid_input.c
int			closed_pipes(t_mini *shell, const char *input);
int			matching_quotes(t_mini *shell, const char *str);
int			valid_pipes(t_mini *shell, const char *input);
int 		valid_redirection(t_mini *shell, const char *input);

//lexer/valid_input2.c
int			backslash(t_mini *shell, const char *input);

//parser/parser_utils.c
int 		count_token_type(t_token *tokens, enum e_token_type type);
int			char_is_whitespace(char c);
void		free_2d_array(char **array);
int			count_pipes(const char *input);

//parser/free_cmd_contents.c
int			quote_offset(const char *input, char quote);

//parser/create_command.c
t_cmd		*create_command(char *cmd_str, int i);

//parser/create_tokens.c
void		add_token(t_token **head, t_token *new_token);
int			tokenize_args(t_cmd *cmd, char **args);

//parser/create_command_args.c
char		**split_cmd_args(char *cmd_str);

//parser/create_quoted_arg.c
char		*create_quoted_arg(char *str, int *i, int len);

//parser/split_by_pipes.c
char		**split_by_pipes(const char *input);

//parser/parser.c
t_cmd		*tokenizer(t_mini *shell, const char *input);

#endif