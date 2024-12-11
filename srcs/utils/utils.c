/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:44:23 by prynty            #+#    #+#             */
/*   Updated: 2024/11/28 12:58:31 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_array_elements(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (count);
	while (array[count])
		count++;
	return (count);
}
