/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:33:53 by asolis            #+#    #+#             */
/*   Updated: 2017/06/28 17:56:23 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		forkzazo(char **matrix, t_list *e, char *path)
{
	pid_t		pid;
	char		**env;

	env = ft_lst_to_mtx(e);
	pid = fork();
	if (pid == -1)
		ft_printfcolor("ERROR: RUNING\n", 31);
	if (pid == 0)
	{
		if (execve(path, matrix, env) != -1)
		{
			ft_free_mtx(env);
			return (1);
		}
	}
	if (pid > 0)
		pid = wait(0);
	ft_free_mtx(env);;
	return (0);
}

int				bin_command(char **mtx, t_list *e)
{
	if (access(mtx[0], X_OK) == 0)
	{
		forkzazo(mtx, e, mtx[0]);
		return (1);
	}
	return (0);
}

int				command(char **path_mtx, char **mtx, t_list *e)
{
	int			i;
	char		*tmp;
	char		*tmp2;

	i = -1;
	while (path_mtx[++i])
	{
		tmp2 = ft_strjoin(path_mtx[i], "/");
		tmp = ft_strjoin(tmp2, mtx[0]);
		if (access(tmp, X_OK) == 0)
		{
			forkzazo(mtx, e, tmp);
			ft_memdel((void**)&tmp);
			ft_memdel((void**)&tmp2);
			return (1);
		}
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
	}
	return (0);
}

int				path_command(char **mtx, t_list *e)
{
	char		**path_mtx;
	char		*tmp_path;

	if ((bin_command(mtx, e)))
		return (1);
	tmp_path = get_path(e);
	path_mtx = ft_strsplit(tmp_path, ':');
	if (command(path_mtx, mtx, e))
	{
		ft_memdel((void**)&tmp_path);
		ft_free_mtx(path_mtx);
		return (1);
	}
	ft_memdel((void**)&tmp_path);
	ft_free_mtx(path_mtx);
	return (0);
}

void			executable(char **mtx, t_list *e)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp2 = ft_strsub(mtx[0], 2, ft_strlen(mtx[0]));
	tmp3 = ft_strjoin(getcwd(NULL, 0), "/");
	tmp = ft_strjoin(tmp3, tmp2);
	forkzazo(mtx, e, tmp);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
	ft_memdel((void**)&tmp3);
}
