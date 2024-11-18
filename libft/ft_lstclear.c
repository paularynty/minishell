/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:45:55 by prynty            #+#    #+#             */
/*   Updated: 2024/07/29 13:45:57 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*curr;

	if (lst && *lst && del)
	{
		curr = (t_list *)*lst;
		while (curr)
		{
			temp = curr->next;
			ft_lstdelone(curr, del);
			curr = temp;
		}
		*lst = NULL;
	}
}
