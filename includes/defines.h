/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:41:12 by prynty            #+#    #+#             */
/*   Updated: 2024/11/25 13:18:40 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define TRUE 1
# define FALSE 0

# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"

//colors
# define RED "\033[1;91m"
# define ORANGE "\e[1m\e[38;5;202m"
# define YELLOW "\033[1;93m"
# define GREEN "\033[1;92m"
# define BLUE "\033[1;94m"
# define CYAN "\033[1;96m"
# define MAGENTA "\033[1;95m"
# define PINK "\e[1m\e[38;5;206m"
# define RESET "\033[0;39m"

#endif