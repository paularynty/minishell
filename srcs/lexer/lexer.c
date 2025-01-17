#include "minishell.h"

int	valid_input(t_mini *shell, char *input)
{
	if (str_is_whitespace(input))
		return (FALSE);
	if (!matching_quotes(shell, input))
		return (FALSE);
	if (backslash(shell, input))
		return (FALSE);
	if (!valid_redirection(shell, input))
		return (FALSE);
	if (!closed_pipes(shell, input))
		return (FALSE);
	if (!valid_pipes(shell, input))
		return (FALSE);
	return (TRUE);
}

int	lexer(t_mini *shell, char *line)
{
	if (!valid_input(shell, line))
		return (FALSE);
	shell->input = expand_input(shell, line);
	if (!shell->input)
	{
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
		return (FALSE);
	}
	shell->input = add_missing_spaces(shell->input);
	if (!shell->input)
	{
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
