/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:24:41 by asolis            #+#    #+#             */
/*   Updated: 2017/09/01 19:55:55 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_lstsearch(t_list *e, char *name)
{
	t_list	*tmp;
	char	*i;
	char	*tamp;
	char	*res;

	tmp = e;
	while (tmp)
	{
		if ((i = ft_strchr(tmp->content, '=')))
		{
			tamp = ft_strsub(tmp->content, 0,
ft_strlen(tmp->content) - ft_strlen(i));
			if (ft_strcmp(tamp, name) == 0)
			{
				res = ft_strsub(tmp->content, ft_strlen
(name) + 1, ft_strlen(i));
				ft_printfbasic("%s", res);
				ft_memdel((void**)&res);
			}
			ft_memdel((void**)&tamp);
		}
		tmp = tmp->next;
	}
	free(tmp);
}

char		**ft_lst_to_mtx(t_list *e)
{
	int		i;
	t_list	*tmp;
	char	**mtx;

	i = 0;
	tmp = e;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	mtx = (char**)malloc(sizeof(char*) * (i + 1));
	tmp = e;
	mtx[i] = NULL;
	i = -1;
	while (tmp)
	{
		mtx[++i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (mtx);
}

void		ft_lstaddnth(t_list **e, t_list *new, int nb)
{
	t_list	*tmp;
	int		i;

	i = 1;
	if (nb == 1)
	{
		new->next = *e;
		*e = new;
		return ;
	}
	tmp = *e;
	while (i < nb - 1)
	{
		tmp = tmp->next;
		i++;
	}
	new->next = tmp->next;
	tmp->next = new;
}

void		ft_lstedit(t_list *e, char *name, char *value)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	t_list	*lst_tmp;

	i = unset_env(e, name, 0);
	tmp = ft_strjoin(name, "=");
	tmp2 = ft_strjoin(tmp, value);
	lst_tmp = ft_lstnew(tmp2, ft_strlen(tmp2) + 1);
	ft_lstaddnth(&e, lst_tmp, i);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);

}

void		ft_lstdeletenode(t_list *e, int nb)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		i;

	i = -1;
	tmp = e;
	if (nb == 1)
	{
		e = tmp->next;
		ft_memdel((void**)tmp);
		return ;
	}
	while (++i < nb - 2)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	ft_memdel((void**)tmp2);
}
