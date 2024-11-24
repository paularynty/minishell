/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:24 by prynty            #+#    #+#             */
/*   Updated: 2024/11/19 13:29:07 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//remember that getcwd is a big help
//in cd, if you use getcwd, it takes in absolute or relative path
//you can give the path to getcwd
//if path exists, you can move to it with chdir
//getcwd you can use for pwd

//1. with empty cd you go to home
//2. "cd -" goes to OLDPWD
//3. with path, you go to the cmd path

void	builtin_cd(void)
{
	chdir("/");
}