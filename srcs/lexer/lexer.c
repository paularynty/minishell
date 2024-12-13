#include "minishell.h"

// This is the first argument validation check.
// We check whether the prompt is empty/whitespace, contains uneven quotes or other errors we can handle immediately
// without taking into account pipes. Upon occuring, we send correct error message, update add_history and return matching exit code.
// Add exit_code / error message handling later.

// int valid_input(char *input)
// {
// 	if (iswhitespace(input))
// 		return (FALSE); // handle whitespace separately? To an exit_function which frees any allocated memory, in bash history is added, rl_on_newline()
// 	if (!matching_quotes(input))
// 		return (FALSE);
// 	if (!valid_redirection(input))
// 		return (FALSE);
// 	if (!valid_pipes(input))
// 		return (FALSE);
// 	if (!closed_pipes(input))
// 		return (FALSE);
// 	return (TRUE);
// }


// int	expand_input(t_mini *minish)
// {
// 	char	*exp_input;
// 	int		len;
// 	int		i;

// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			exp_input = get_var(input + i + 1);
// 		}
// 	}
// }

// int lexer(t_mini *minish)
// {
// 	if (!valid_input(minish))
// 		return (FALSE);
// 	if (!expand_input(minish))
// 		return (FALSE);
// 	if (!add_redir_space(minish))
// 		return (FALSE);
// 	return (TRUE);
// }
