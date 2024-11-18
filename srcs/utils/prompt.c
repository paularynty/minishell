/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:16:04 by prynty            #+#    #+#             */
/*   Updated: 2024/11/11 12:24:35 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    get_prompt(char *prompt, size_t size)
{
	//char	*username;

	ft_bzero(prompt, size);
	//set_username(username);
	//if (!username)
		//username = "unknown";
	ft_strlcat(prompt, "prynty", size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell:", size);
	///set_cwd(prompt, size);
	ft_strlcat(prompt, "~/test/cwd/", size);
	ft_strlcat(prompt, "$ ", size);
}
