/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:52:10 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/16 16:11:15 by sniemela         ###   ########.fr       */
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

char	*expand_exit_code(t_mini *shell, char *input, int *i)
{
	char	*value;
	char	*new_input;

	value = ft_itoa(shell->exit_code);
	if (!value)
		return (NULL);
	new_input = replace_segment(input, *i, *i + 2, value);
	free(input);
	if (!new_input)
		return (NULL);
	*i += ft_strlen(value) - 1;
	free(value);
	return (new_input);
}

char	*double_quotes_expand(t_mini *shell, char *input, int i)
{
	(i)++;
	while (input[i] && input[i] != '"')
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				input = expand_exit_code(shell, input, &i);
				if (!input)
					return (NULL);
			}
			else if (!char_is_whitespace(input[i + 1])
				&& input[i + 1] != '"')
			{
				input = expand_variable(shell, input, &i);
				if (!input)
					return (NULL);
			}
		}
		else
			i++;
	}
	i++;
	return (input);
}

char	*handle_quotes(t_mini *shell, char *input, int *i)
{
	if (input[*i] == '"')
	{
		input = double_quotes_expand(shell, input, *i);
		if (!input)
			return (NULL);
		*i += quote_offset(input + *i, input[*i]);
	}
	else if (input[*i] == '\'')
		*i += quote_offset(input + *i, input[*i]);
	return (input);
}

char	*wp_or_exit_code(t_mini *shell, char *input, int *i)
{
	if (char_is_whitespace(input[*i + 1]))
	{
		(*i)++;
		return (input);
	}
	else if (input[*i + 1] == '?')
		input = expand_exit_code(shell, input, &(*i));
	return (input);
}

/*
TOMORROW (FRIDAY 17th) I WILL UNITE THESE TWO:
	else if (char_is_quote(inp[i + 1]))
	{
		inp = replace_segment(inp, i, i + 1, NULL);
		continue ;
	}
	else	
	{
		inp = expand_variable(shell, inp, &i);
		continue ;
	}
TO A FUNCTION "expand_or_replace()" which call either of those 
functions (I do this to save lines / because of norm)
*/

char	*expand_input(t_mini *shell, char *inp) 
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (char_is_quote(inp[i]))
		{
			inp = handle_quotes(shell, inp, &i);	
			continue ;
		}
		if (inp[i] == '$' && inp[i + 1] && !ft_strchr("$/", inp[i + 1]))
		{
			if (char_is_whitespace(inp[i + 1]) || inp[i + 1] == '?')
				inp = wp_or_exit_code(shell, inp, &i);
			else if (char_is_quote(inp[i + 1]))
			{
				inp = replace_segment(inp, i, i + 1, NULL);
				continue ;
			}
			else
			{
				inp = expand_variable(shell, inp, &i);
				continue ;
			}
		}
		else
			i++;
	}
	return (inp);
}

// char	*expand_input(t_mini *shell, char *inp) 
// {
// 	int	i;

// 	i = 0;
// 	while (inp[i])
// 	{
// 		if (inp[i] == '"')
// 		{
// 			inp = double_quotes_expand(shell, inp, i);
// 			i += quote_offset(inp + i, inp[i]);
// 			continue ;
// 		}
// 		if (inp[i] == '\'')
// 			i += quote_offset(inp + i, inp[i]);
// 		if (inp[i] == '$' && inp[i + 1] && !ft_strchr("$/", inp[i + 1]))
// 		{
// 			if (char_is_whitespace(inp[i + 1]))
// 				inp = replace_segment(inp, i, i + 1, NULL);
// 			else if (char_is_quote(inp[i + 1]))
// 			{
// 				inp = replace_segment(inp, i, i + 1, NULL);
// 				continue ;
// 			}
// 			else if (inp[i + 1] == '?')
// 				inp = expand_exit_code(shell, inp, &i);
// 			else
// 			{
// 				inp = expand_variable(shell, inp, &i);
// 				continue ;
// 			}
// 			if (!inp)
// 				return (NULL);
// 			else
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (inp);
// }