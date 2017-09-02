/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 17:00:25 by asolis            #+#    #+#             */
/*   Updated: 2017/01/18 17:00:26 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t size)
{
	t_list *elem;

	if (!(elem = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		elem->content = (void*)ft_memalloc(size);
		elem->content = ft_memcpy(elem->content, content, size);
		elem->content_size = size;
	}
	elem->next = NULL;
	return (elem);
}
