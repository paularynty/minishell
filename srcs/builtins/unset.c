/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:56 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 16:23:54 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//if you create with export something, it goes to env
//if you say export var XXX, it goes to pending list
//in unset you need to keep track to remove both from env and pending list

int	builtin_unset(char **cmd)
{
	if (!cmd[1])
		return (0);
	return (0);
}
