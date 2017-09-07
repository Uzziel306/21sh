/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:22:40 by asolis            #+#    #+#             */
/*   Updated: 2017/09/01 19:55:54 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			ft_error_path(char *pwd)
{
	ft_printfbasic("-bash: cd: ");
	ft_printfbasic("%s", pwd);
	ft_printfbasic(": No such file or directory\n");
	return (0);
}

void		ft_printlst(t_list *e)
{
	t_list	*tmp;

	tmp = e;
	while (tmp)
	{
		ft_printfbasic("%s\n", tmp->content);
		tmp = tmp->next;
	}
	free(tmp);
}

t_msh		*get_t_msh(t_msh *f)
{
	static	t_msh *h = NULL;

	if (f)
		h = f;
	return (h);
}