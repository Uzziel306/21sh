# include "21sh.h"

int			len_dir(char *pwd, t_msh *f)
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

void		autocompleteJoin(t_msh *f, char *line)
{
	t_line	*tmp;
	int		i;

	i = -1;
	tmp = (t_line*)ft_memalloc(sizeof(t_line));
	tmp->content = ' ';
	tmp->next = NULL;
	ft_lstaddbackline(&f->line, tmp);
	while (line[++i])
	{
		tmp = (t_line*)ft_memalloc(sizeof(t_line));
		tmp->content = line[i];
		tmp->next = NULL;
		ft_lstaddbackline(&f->line, tmp);
	}
}

void		get_autocomplete(t_msh *f)
{
	int		i;
	struct dirent	*pdirent;
	DIR		*pep;
	char	*pwd;

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
	autocompleteJoin(f, pdirent->d_name);
	closedir(pep);
}

void		auto_complete(t_msh *f)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	char			*pwd;
	static int		i;
	int				len;
	struct winsize	win;

	i = 0;
	pwd = getcwd(NULL, 0);
	len = len_dir(pwd, f);
	f->term.win_x = win.ws_col;
	f->term.win_y = win.ws_row;
	pdir = opendir(pwd);
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
}
