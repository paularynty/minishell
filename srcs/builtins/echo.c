/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:29 by prynty            #+#    #+#             */
/*   Updated: 2024/11/26 15:22:59 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//echo needs to take into account expanding

void	builtin_echo(char **cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	if (!cmd[1])
		return ;
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		newline = FALSE;
		i++;
	}
	while (cmd[i])
		printf("%s", cmd[i++]);
	if (newline)
		printf("\n");
}
