/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:24:12 by algasnie          #+#    #+#             */
/*   Updated: 2025/10/23 11:50:41 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*n;

	if (!*lst || !lst || !del)
		return ;
	p = *lst;
	while (p != NULL)
	{
		n = p->next;
		del(p->content);
		free(p);
		p = n;
	}
	*lst = NULL;
}
