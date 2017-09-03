/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:23:45 by asolis            #+#    #+#             */
/*   Updated: 2017/09/01 19:55:54 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*get_last_part()
{
	char	*pwd;
	char	*res;
	char	*i;

	pwd = getcwd(NULL, 0);
	if (ft_strlen(pwd) == 1)
	{
		 ft_strdel(&pwd);
		return (res = ft_strdup("/"));
	}
	i = ft_strrchr(pwd, '/');
	res = ft_strsub(pwd,(ft_strlen(pwd) - ft_strlen(i)) + 1, ft_strlen(pwd));
	 ft_strdel(&pwd);
	return (res);
}

int			ft_memdel_int(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
	return (0);
}

int			ft_ismayus(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

void		free_shit(char *a, char *b, char *c)
{
	ft_memdel((void**)&a);
	ft_memdel((void**)&b);
	ft_memdel((void**)&c);
}

char		*get_path(t_list *e)
{
	char	*tmp_path;
	char	*tmp_pwd;
	t_list	*tmp;

	tmp = e;
	while (tmp)
	{
		tmp_path = ft_strsub(tmp->content, 0, 4);
		if (ft_strcmp(tmp_path, "PATH") == 0)
		{
			tmp_pwd = ft_strsub(tmp->content, 5, ft_strlen(tmp->content));
			ft_memdel((void**)&tmp_path);
			return (tmp_pwd);
		}
		ft_memdel((void**)&tmp_path);
		tmp = tmp->next;
	}
	free(tmp);
	return (0);
}
