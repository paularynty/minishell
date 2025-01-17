/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:52:10 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/17 09:27:53 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable(t_mini *shell, char *key, int key_len)
{
	int		i;
	int		env_len;
	char	*exp_var;

	i = 0;
	exp_var = NULL;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& *(shell->env[i] + key_len) == '=')
		{
			env_len = ft_strlen(shell->env[i] + key_len + 1);
			exp_var = ft_substr(shell->env[i], key_len + 1, env_len);
			if (!exp_var)
				return (NULL);
			return (exp_var);
		}
		i++;
	}
	exp_var = ft_strdup("");
	if (!exp_var)
		return (NULL);
	return (exp_var);
}

char	*replace_segment(char *input, int start, int end, char *repl)
{
	char	*new_input;
	int		input_len;
	int		repl_len;
	int		new_len;

	input_len = ft_strlen(input);
	repl_len = ft_strlen(repl);
	new_len = input_len - (end - start) + repl_len;
	new_input = (char *)malloc(sizeof(char) * new_len + 1);
	if (!new_input)
		return (NULL);
	if (ft_strlcpy(new_input, input, start + 1) == 0)
		return (NULL);
	if (repl)
		ft_strlcpy(new_input + start, repl, start + repl_len + 1);
	ft_strlcpy(new_input + start + repl_len, input + end, new_len + 1);
	return (new_input);
}

char	*expand_variable(t_mini *shell, char *input, int *i)
{
	int		end;
	char	*key;
	char	*value;
	char	*new_input;

	end = *i + 1;
	while (input[end] && !char_is_whitespace(input[end])
		&& !ft_strchr("$?\"'/", input[end]))
		end++;
	if (end <= *i + 1)
		return (input);
	key = ft_substr(input, *i + 1, end - *i - 1);
	if (!key)
		return (free(input), NULL);
	value = get_variable(shell, key, ft_strlen(key));
	free(key);
	if (!value)
		return (free(input), NULL);
	new_input = replace_segment(input, *i, end, value);
	if (!new_input)
		return (free(input), NULL);
	*i += ft_strlen(value);
	free(value);
	free(input);
	return (new_input);
}

char	*expand_or_replace(t_mini *shell, char *input, int *i)
{
	if (char_is_quote(input[*i + 1]))
		input = replace_segment(input, *i, *i + 1, NULL);
	else
		input = expand_variable(shell, input, &(*i));
	if (!input)
		return (NULL);
	return (input);
}

char	*expand_input(t_mini *shell, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (char_is_quote(input[i]))
		{
			input = handle_quotes(shell, input, &i);
			continue ;
		}
		if (input[i] == '$' && input[i + 1] && !ft_strchr("$/", input[i + 1]))
		{
			if (char_is_whitespace(input[i + 1]) || input[i + 1] == '?')
				input = wp_or_exit_code(shell, input, &i);
			else
			{
				input = expand_or_replace(shell, input, &i);
				continue ;
			}
		}
		else
			i++;
	}
	return (input);
}
