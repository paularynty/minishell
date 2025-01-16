#ifndef FUNC_DEFINITIONS_H
# define FUNC_DEFINITIONS_H

# include "structs.h"

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
// typedef enum e_token_type t_token_type;

//lexer/add_missing_spaces.c

/********************************************************************
 * If the syntax contains nested redirections, add_missing_spaces(); 
 * adds a space in front of and/or behind the operator.
 * For example:
 * input: cat<Makefile|<<LIM>"outfile"
 * return value: cat < Makefile| << LIM > "outfile"
*********************************************************************/
char		*add_missing_spaces(char *input);

/********************************************************************
 * Copys the char *input to a newly allocated str until index [end]
 * is reached, then copies ' ' (space) to end's index. After that
 * continues input's copying process until input[i] == '\0'.
 * Then returns new spaced input.
 ********************************************************************/
char		*add_space(char *input, int end);

/******************************************************************
 * Moves &i as long as input[*i] is whitespace.
 *****************************************************************/
void		move_i_past_whitespace(char *input, int *i);

/****************************************************************
 * add_missing_spaces() helper function, calls spaces_to_input();
 ****************************************************************/
char		*spaces_to_input(char *input, int *i);

//lexer/expansion.c
char		*expand_exit_code(t_mini *shell, char *input, int *i);
char		*expand_input(t_mini *shell, char *inp);
char		*expand_variable(t_mini *shell, char *input, int *i);
char		*get_variable(t_mini *shell, char *key, int key_len);
char		*replace_segment(char *input, int start, int end, char *repl);

//lexer/lexer.c
/*************************************************************************
 * Validates the initial user input before parsing.
 *
 * @shell: Pointer to the shell structure.
 * @input: The expanded input string (shell->input).
 *
 * - Checks if the input consists only of whitespace.
 * - Validates that all quotes in the input are properly matched.
 * - Ensures there are no improper backslashes in the input.
 * - Verifies the correctness of input redirection syntax.
 * - Confirms that all pipes are closed and valid.
 * 
 * Returns TRUE if the input is valid, FALSE if any validation fails and 
 * prints out correct error message.
 ************************************************************************/
int			valid_input(t_mini *shell, char *input);

/**********************************************************************
 * Check the command's syntax by calling valid_input() and returns
 * FALSE (=0) in case of a syntax error. After that expands input if
 * $ is encountered. Saves the expanded input into shell->input. 
 * Returns FALSE and frees if malloc fails in expansion. After exp calls
 * add_missing_spaces(). Overall lexer saves a valid, expanded and
 * "spaced" input into shell->input and returns TRUE upon success.
 *********************************************************************/
int			lexer(t_mini *shell, char *line);

//lexer/lexer_utils.c
int			char_is_quote(char c);
int			char_is_whitespace(char c);
int			str_is_whitespace(const char *str);
void		error_pipes(t_mini *shell, int pipes);

//lexer/valid_input.c
int			closed_pipes(t_mini *shell, const char *input);
int			matching_quotes(t_mini *shell, const char *str);
int			valid_pipes(t_mini *shell, const char *input);
int			valid_redirection(t_mini *shell, const char *input);

//lexer/valid_input2.c
int			backslash(t_mini *shell, const char *input);

//parser/parser_utils.c
int			count_token_type(t_token *tokens, enum e_token_type type);
void		free_2d_array(char **array);

/*************************************************************
 * 
 * we count how many pipes occur, but discard anything that's
 * inside quotes (using quote_offset())
 * 
 ************************************************************/
int			count_pipes(const char *input);

int			quote_offset(const char *input, char quote);
/*************************************************************
 * Counts the length of a quoted segment.
 * The insides of the quotes are their own argument, so we 
 * count how long this argument is (including quotes). 
 * We already have quotes opened, so offset is initialized to 1.
 *************************************************************/

//parser/free_cmd_contents.c

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
t_cmd		*tokenizer(t_mini *shell, char *input);

#endif