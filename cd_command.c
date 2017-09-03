/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:15:05 by asolis            #+#    #+#             */
/*   Updated: 2017/09/01 20:10:01 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char			*cd(char **mtx, char *pwd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(pwd);
	i = -1;
	while (mtx[++i] != NULL)
	{
		if (ft_strcmp("..", mtx[i]) == 0)
		{
			tmp2 = cutting_last_path(tmp);
			ft_strswap(&tmp2, &tmp);
			ft_memdel((void**)&tmp2);
		}
		else
		{
			tmp2 = join_path(tmp, mtx[i]);
			ft_strswap(&tmp2, &tmp);
			ft_memdel((void**)&tmp2);
		}
	}
	if (chdir(tmp) == 0)
		return (tmp);
	ft_memdel((void**)&tmp);
	return (0);
}

void		validation_cd_command(char **matrix, t_msh *f, t_list *e)
{
	char	*old_pwd;
	char	*mierda;

	old_pwd = getcwd(NULL, 0);
	if (ft_matrixlen(matrix) > 1)
		mierda = ft_strsub(matrix[1], 2, ft_strlen(matrix[1]));
	if (ft_matrixlen(matrix) == 1)
		cd_command_len_1(f, e);
	else if (ft_strcmp(matrix[1], "/") == 0)
		cd_command_home(e);
	else if (ft_strcmp(matrix[1], "-") == 0)
		cd_command_minus(e);
	else if (ft_strncmp(matrix[1], "~", 1) == 0)
			cd_command(mierda, f->sh.p_home, e);
	else if (ft_matrixlen(matrix) == 2)
		cd_command(matrix[1], old_pwd, e);
	else if (ft_matrixlen(matrix) >= 3)
		ft_printfcolor("%s", "ERROR: TOO MANY ARGUMENTS\n", 31);
	if (ft_matrixlen(matrix) > 1)
		ft_strdel(&mierda);
	ft_strdel(&old_pwd);
}

void		cd_command(char *pwd, char	*old_pwd, t_list *e)
{
	char	**mtrx;
	char	*i;
	char	*new_pwd;
	char	*aux;
	int		a;
	aux = getcwd(NULL, 0);
	if (!(a = general(pwd, old_pwd, e)))
		chdir(aux);
	else if ((i = ft_strchr(pwd, '/')) && a == 0)
		{
			mtrx = ft_strsplit(pwd, '/');
			if ((new_pwd = cd(mtrx, old_pwd)))
				{
					changing_pwd_oldpwd(new_pwd, old_pwd, e);
					ft_strdel(&new_pwd);
				}
			else
				ft_printfcolor("%s%s\n", "cd: no such file or directory: ", 31, pwd, 31);
			ft_free_mtx(mtrx);
		}
	ft_strdel(&aux);
}
