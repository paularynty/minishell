/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:16:04 by prynty            #+#    #+#             */
/*   Updated: 2024/11/19 13:28:00 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	set_prompt_user(char *username)
// {
// 	//look for USER in env and save the result in username;
// }

static void	set_prompt_cwd(t_mini *shell, size_t size)
{
	shell->cwd = getcwd(shell->cwd, size);
}

void	get_prompt(t_mini *shell, char *prompt, size_t size)
{
	//char	*username;
	ft_bzero(prompt, size);
	//set_prompt_username(username);
	//if (!username)
		//username = "unknown";
	ft_strlcat(prompt, "prynty", size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell:", size);
	set_prompt_cwd(shell, size);
	ft_strlcat(prompt, "~", size);
	ft_strlcat(prompt, shell->cwd, size);
	ft_strlcat(prompt, "$ ", size);
}
