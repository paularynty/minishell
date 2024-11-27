/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:50 by prynty            #+#    #+#             */
/*   Updated: 2024/11/27 11:33:25 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO DO: need to update pwd in env as well

#include "../../includes/minishell.h"

void	builtin_pwd(t_mini *shell)
{
	printf("%s\n", shell->cwd);
}
