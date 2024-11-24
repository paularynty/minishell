/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:29 by prynty            #+#    #+#             */
/*   Updated: 2024/11/24 12:17:28 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//echo needs to take into account expanding

void	builtin_echo(char *line)
{
	int	newline;

	newline = TRUE;
	printf("%s", line);
	if (newline)
		printf("\n");
}
