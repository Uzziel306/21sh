/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:21:50 by asolis            #+#    #+#             */
/*   Updated: 2017/06/28 17:50:32 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*get_env(void)
{
	extern char	**environ;
	t_list		*tmp;
	t_list		*en;
	int			i;

	en = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		tmp = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
		ft_lstaddback(&en, tmp);
		i++;
	}
	return (en);
}

void			set_env(t_list *e, char *name, char *value)
{
	char		*tmp;
	char		*tmp2;
	char		*special;
	t_list		*env_node;

	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
	{
		special = ft_strsub(value, 1, ft_strlen(value) - 2);
		tmp2 = ft_strjoin(name, "=");
		tmp = ft_strjoin(tmp2, special);
		env_node = ft_lstnew(tmp, ft_strlen(tmp) + 1);
		ft_lstaddback(&e, env_node);
		ft_memdel((void**)&special);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
		return ;
	}
	tmp2 = ft_strjoin(name, "=");
	tmp = ft_strjoin(tmp2, value);
	env_node = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	ft_lstaddback(&e, env_node);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
}

int				validation_name(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (!ft_ismayus(str[i]))
			return (0);
	}
	return (1);
}

void			multi_setenv(t_list *e, char **values, int len, t_msh *f)
{
	int			i;
	size_t		cont;

	f->axe.start = ft_strsub(values[2], 1, ft_strlen(values[2]));
	f->axe.end = ft_strsub(values[len - 1], 0, ft_strlen(values[len - 1]) - 1);
	i = 2;
	cont = ft_strlen(f->axe.start);
	cont += ft_strlen(f->axe.end);
	while (values[++i + 1] != NULL)
		cont += ft_strlen(values[i]);
	cont += len - 2;
	i = 2;
	if (f->axe.tmp != NULL)
		ft_memdel((void**)&f->axe.tmp);
	f->axe.tmp = (char*)malloc(sizeof(char) * (cont));
	f->axe.tmp = ft_strcat(f->axe.tmp, f->axe.start);
	f->axe.tmp = ft_strcat(f->axe.tmp, ":");
	while (values[++i + 1] != NULL)
	{
		f->axe.tmp = ft_strcat(f->axe.tmp, values[i]);
		f->axe.tmp = ft_strcat(f->axe.tmp, ":");
	}
	f->axe.tmp = ft_strcat(f->axe.tmp, f->axe.end);
	set_env(e, values[1], f->axe.tmp);
	free_shit(f->axe.tmp, f->axe.start, f->axe.end);
}

void			setenv_validation(t_list *e, char **mtx, t_msh *f)
{
	int			i;

	i = 0;
	if ((i = ft_matrixlen(mtx)) == 1)
		ft_printlst(e);
	else if (!validation_name(mtx[1]))
		ft_printfcolor("%s\n", "ERROR: THE NAME MUST BE IN MAYUS", 31);
	else if (i == 3)
		set_env(e, mtx[1], mtx[2]);
	else if (i > 3)
	{
		if (mtx[2][0] == '(' && mtx[i - 1][ft_strlen(mtx[i - 1]) - 1] == ')')
			multi_setenv(e, mtx, i, f);
		else
			ft_printfcolor("%s\n", "ERROR: FOR MULTI VALUES\n", 31);
	}
}
