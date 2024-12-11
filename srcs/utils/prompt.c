/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:16:04 by prynty            #+#    #+#             */
/*   Updated: 2024/12/04 12:31:19 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	set_prompt_cwd(t_mini *shell, size_t size)
// {
// 	shell->cwd = getcwd(shell->cwd, size);
// }

void	get_prompt(t_mini *shell, char *prompt, size_t size)
{
	char	*username;

	ft_bzero(prompt, size);
	username = env_get_variable(shell->env, "USER");
	if (!username)
		username = "unknown";
	ft_strlcat(prompt, PINK, size);
	ft_strlcat(prompt, username, size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell:", size);
	update_pwd(shell);
	ft_strlcat(prompt, "~", size);
	ft_strlcat(prompt, shell->cwd, size);
	ft_strlcat(prompt, "$ ", size);
	ft_strlcat(prompt, RESET, size);
}
