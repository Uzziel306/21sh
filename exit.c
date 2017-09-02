/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:19:36 by asolis            #+#    #+#             */
/*   Updated: 2017/08/31 18:11:50 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitazo(t_list *e, t_msh *f)
{
	int	i;

	i = 0;
	ft_memdel((void**)&f->sh.p_home);
	ft_memdel((void**)&f->sh.p_user);
	ft_memdel((void**)&f->axe.end);
	ft_memdel((void**)&f->axe.tmp);
	ft_lstdel(&e, ft_bzero);
	exit(3);
}

void				pwd(void)
{
	char			*pwd;

	pwd = getcwd(NULL, 0);
	ft_printfcolor("%s\n", pwd, 44);
	ft_memdel((void**)&pwd);
}

char				*join_path(char *str, char *str2)
{
	char			*tmp;
	char			*tmp2;

	tmp = ft_strjoin(str, "/");
	tmp2 = ft_strjoin(tmp, str2);
	ft_memdel((void**)&tmp);
	return (tmp2);
}

void				changing_pwd_oldpwd(char *new_pwd, char *old_pwd, t_list *e)
{
	ft_lstedit(e, "PWD", new_pwd);
	ft_lstedit(e, "OLDPWD", old_pwd);
}


char				*cutting_last_path(char *str)
{
	char			*i;
	char			*res;

	i = ft_strrchr(str, '/');
	res = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(i));
	return (res);
}

void				ft_strswap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}
