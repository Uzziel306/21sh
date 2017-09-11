# include "21sh.h"

int		len_dir(char *pwd, t_msh *f)
{
	int		i;
	struct dirent	*pdirent;
	DIR				*pep;
	int				tmp;

	pep = opendir(pwd);
	i = 0;

	while ((pdirent = readdir(pep)) != NULL)
	{
		if (pdirent->d_name[0] == '.')
			continue ;
		if (f->term.max < (tmp = (int)ft_strlen(pdirent->d_name)))
			f->term.max = tmp;
		i++;
	}
	closedir(pep);
	return (i);
}

char		*get_autocomplete(char *line, t_msh *f)
{
	int		i;
	struct dirent	*pdirent;
	DIR		*pep;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	pep = opendir(pwd);
	i = 0;

	while ((pdirent = readdir(pep)) != NULL)
	{
		if (pdirent->d_name[0] == '.')
			f->term.tab_cursor += 1;
		if (i + 1 == f->term.tab_cursor)
			break ;
		i++;
	}
	ft_memdel((void**)&pwd);
	tmp = ft_strjoin(line, " ");
	ft_strdel(&line);
	line = ft_strjoin(tmp, pdirent->d_name);
	ft_memdel((void**)&tmp);
	closedir(pep);
	return (line);
}

char		*auto_complete(char *line)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	char			*pwd;
	static int		i;
	t_msh			*f;
	int				len;
	struct winsize	win;

	ft_termcmd("bl");
	f = get_t_msh(NULL);
	i = 0;
	pwd = getcwd(NULL, 0);
	len = len_dir(pwd, f);
	f->term.win_x = win.ws_col;
	f->term.win_y = win.ws_row;
	pdir = opendir(pwd);
	ft_putchar_fd('\n', 2);
	ft_termcmd("cd");
	while ((pdirent = readdir(pdir)) != NULL)
	{
		if (pdirent->d_name[0] != '.')
		{
			if (i == f->term.tab_cursor)
				ft_termcmd("so");
			ft_printfcolor("%s ", pdirent->d_name, 35);
			ft_putchar_fd(' ', 2);
			ft_termcmd("se");
			i++;
		}
	}
	ft_termcmd("rc");
	f->term.tab_cursor += 1;
	if (f->term.tab_cursor == len)
		f->term.tab_cursor = 0;
	ft_putchar_fd('\n', 2);
	ft_strdel(&pwd);
	closedir(pdir);
	return(line);
}
