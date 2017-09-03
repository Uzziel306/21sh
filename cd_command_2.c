/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:53:15 by asolis            #+#    #+#             */
/*   Updated: 2017/09/01 20:09:41 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			general(char *direction, char	*old_pwd, t_list *e)
{
	char	*new_pwd;

	chdir(old_pwd);
	if ((chdir(direction)) == 0)
	{
		if (ft_strcmp("..", direction) == 0)
			new_pwd = cutting_last_path(old_pwd);
		else
			new_pwd = join_path(old_pwd, direction);
		changing_pwd_oldpwd(new_pwd, old_pwd, e);
		ft_memdel((void**)&new_pwd);
		return (1);
	}
	ft_printfcolor("%s%s\n", "cd: no such file or directory:", 31, direction, 31);
	return (0);
}

void		cd_command_minus(t_list *e)
{
	char	*tmp_pwd;
	char	*old_pwd;
	char	*new_pwd;
	t_list	*tmp;

	tmp = e;
	old_pwd = getcwd(NULL, 0);
	while (tmp != NULL)
	{
		tmp_pwd = ft_strsub(tmp->content, 0, 6);
		if (ft_strcmp(tmp_pwd, "OLDPWD") == 0)
		{
			new_pwd = ft_strsub(tmp->content, 7, ft_strlen(tmp->content));
			if (chdir(new_pwd) == 0)
			{
				ft_lstedit(e, "PWD", new_pwd);
				ft_lstedit(e, "OLDPWD", old_pwd);
				free_shit(new_pwd, tmp_pwd, ft_strdup("huevos"));
				break ;
			}
		}
		ft_memdel((void**)&tmp_pwd);
		tmp = tmp->next;
	}
	ft_memdel((void**)&old_pwd);
}

void		cd_command_home(t_list *e)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if ((chdir("/")) == 0)
	{
		ft_lstedit(e, "PWD", "/");
		ft_lstedit(e, "OLDPWD", old_pwd);
	}
	ft_memdel((void**)&old_pwd);
}

void		cd_command_len_1(t_msh *f, t_list *e)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	new_pwd = ft_strdup(f->sh.p_home);
	if ((chdir(new_pwd)) == 0)
	{
		ft_lstedit(e, "PWD", new_pwd);
		ft_lstedit(e, "OLDPWD", old_pwd);
	}
	ft_memdel((void**)&old_pwd);
	ft_memdel((void**)&new_pwd);
}
