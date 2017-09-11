/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:30:05 by asolis            #+#    #+#             */
/*   Updated: 2017/09/02 19:38:51 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char				*readline(void)
{
	char			buffsazo[1025];
	int				ret;
	char			*line;

	ret = read(0, buffsazo, 1024);
	if (ret == 0)
	{
		line = ft_strdup("exit");
		return (line);
	}
	buffsazo[ret - 1] = '\0';
	line = ft_strsub(buffsazo, 0, ft_strlen(buffsazo));
	return (line);
}

void				get_command(char *str, t_msh *f, t_list *e)
{
	char			**matrix;

	matrix = ft_split_whitespaces(str);
	if (matrix[0] != NULL)
	{
		if (matrix[0][0] == '.' && matrix[0][1] == '/')
			executable(matrix, e);
		else if (ft_strcmp(matrix[0], "pwd") == 0)
			pwd();
		else if (ft_strcmp(matrix[0], "echo") == 0)
			validation_echo(matrix, e);
		else if (ft_strcmp(matrix[0], "cd") == 0)
			validation_cd_command(matrix, f, e);
		else if (ft_strcmp(matrix[0], "env") == 0)
			ft_printlst(e);
		else if (ft_strcmp(matrix[0], "setenv") == 0)
			setenv_validation(e, matrix, f);
		else if (ft_strcmp(matrix[0], "unsetenv") == 0)
			unsetenv_validation(e, matrix);
		else if (!path_command(matrix, e))
			ft_printfcolor("%s %s\n", matrix[0], 31, ": command not found", 31);
		ft_free_mtx(matrix);
	}
}

int					get_shell(t_msh *f)
{
	extern char		**environ;
	int				i;

	f->term.x = NULL;
	get_t_msh(f);
	i = -1;
	while (environ[++i] != NULL)
	{
		if (environ[i][4])
		{
			if (environ[i][0] == 'U' && environ[i][1] == 'S' &&
				environ[i][2] == 'E' && environ[i][3] == 'R' && environ[i][4] == '=')
				f->sh.p_user = ft_strsub(environ[i], 5, ft_strlen(environ[i]));
			else if (environ[i][0] == 'H' && environ[i][1] == 'O' &&
				environ[i][2] == 'M' && environ[i][3] == 'E' && environ[i][4] == '=')
				f->sh.p_home = ft_strsub(environ[i], 5, ft_strlen(environ[i]));
		}
	}
	return (0);
}

void				pre_get_command(char *str, t_msh *f, t_list *e)
{
	char			*i;
	char			**multi_cmd;
	int				j;

	j = -1;
	if ((i = ft_strchr(str, ';')))
	{
		multi_cmd = ft_strsplit(str, ';');
		while (multi_cmd[++j])
			get_command(multi_cmd[j], f, e);
		ft_free_mtx(multi_cmd);
	}
	else
		get_command(str, f, e);
}

int					main(int ac, char **ag)
{
	char			*command;
	t_msh			f;
	t_list			*e;
	char 			*pwd;

	ac += 1;
	ag += 1;
	ft_bzero(&f, sizeof(t_msh));
	get_shell(&f);
	e = get_env(&f);
	starting_env();
	while (42)
	{
		pwd = get_last_part();
		ft_printfcolor("%s%s%s", "@", 33, f.sh.p_user, 33, "$>", 33);
		ft_printfcolor("%s%s%s", "*[", 34, pwd, 31, "]* ", 34);
		command = readterm(&f);
		if (ft_strcmp(command, "exit") == 0)
			break ;
		if (ft_strlen(command))
			pre_get_command(command, &f, e);
		ft_strdel(&command);
		f.term.tab_cursor = 0;
		ft_strdel(&pwd);
	}
	ft_lstdel(&e, ft_bzero);
	ft_memdel((void**)&command);
	exitazo(e, &f);
	return (1);
}
