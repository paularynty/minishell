/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:50 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 15:58:16 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO DO: need to update pwd in env as well

#include "../../includes/minishell.h"

int	builtin_pwd(t_mini *shell)
{
	printf("%s\n", shell->cwd);
	return (0);
}
