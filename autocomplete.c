# include "21sh.h"

int			len_dir(char *pwd, t_msh *f, char *str)
{
	int		i;
	struct dirent	*pdirent;
	DIR				*pep;
	int				tmp;
	int				len;

	printf("%s\n", str);
	exit(0);
	pep = opendir(pwd);
	i = 0;
	while ((pdirent = readdir(pep)) != NULL)
	{
		len = ft_strlen(str);
		if (pdirent->d_name[0] == '.' && str[0] != '.')
			continue ;
		if (ft_strncmp(str, pdirent->d_name, len) == 0)
		{
			if (f->term.max < (tmp = (int)ft_strlen(pdirent->d_name)))
				f->term.max = tmp;
			i++;
		}
	}
	closedir(pep);
	return (i);
}

int					len_dirBasic(char *pwd, t_msh *f)
{
	int				i;
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

void		complexAutoJoin(t_msh *f, char *line)
{
	int		i;
	t_line	*tmp;

	i = -1;
	ft_lstdeln(&f->line);
	while(line[++i] != '\0')
	{
		tmp = (t_line*)ft_memalloc(sizeof(t_line));
		tmp->content = line[i];
		tmp->next = NULL;
		ft_lstaddbackline(&f->line, tmp);
	}
}

void		autocompleteJoin(t_msh *f, char *line)
{
	t_line	*tmp;
	int		i;
	char	**secondWord;

	secondWord = ft_split_whitespaces(line);
	if (ft_matrixlen(secondWord) > 1)
		complexAutoJoin(f, secondWord[0]);
	i = -1;
	tmp = (t_line*)ft_memalloc(sizeof(t_line));
	tmp->content = ' ';
	tmp->next = NULL;
	ft_lstaddbackline(&f->line, tmp);
	while (f->term.autoCompleteStr[++i])
	{
		tmp = (t_line*)ft_memalloc(sizeof(t_line));
		tmp->content = f->term.autoCompleteStr[i];
		tmp->next = NULL;
		ft_lstaddbackline(&f->line, tmp);
	}
	ft_free_mtx(secondWord);
}

void				printFile(t_msh *f, char *str, int *index)
{
	int				white_spaces;
	int				i;

	i = -1;
	if (((*index % f->term.cols) == 0) && *index > 0)
			ft_putchar_fd('\n', 2);
	white_spaces = (f->term.max - (int)ft_strlen(str));
	if (*index == f->term.tab_cursor)
	{
		if (f->term.autoCompleteStr != NULL)
			ft_strdel(&f->term.autoCompleteStr);
		ft_printfcolor("%s", str, 46);
		f->term.autoCompleteStr = ft_strdup(str);
	}
	else
		ft_printfcolor("%s", str, 36);
	*index += 1;
	while (++i < white_spaces + 3)
		ft_putchar_fd(' ', 2);
}

void				printDirectori(t_msh *f, char *pwd, char *str)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	int				i;
	double			cols;

	f->term.cols = (f->term.win_x / (f->term.max + 2));
	pdir = opendir(pwd);
	ft_putchar_fd('\n', 2);
	i = 0;
	while ((pdirent = readdir(pdir)) != NULL)
	{
		if (str != NULL)
		{
			if (ft_strncmp(str, pdirent->d_name, ft_strlen(str)) == 0)
				printFile(f, pdirent->d_name, &i);
		}
		else if (pdirent->d_name[0] != '.')
			printFile(f, pdirent->d_name, &i);
	}
	closedir(pdir);
	ft_termcmd("rc");
}

int				canUseAutoComplete(char *line)
{
	int				i;
	int				len;

	len = ft_strlen(line);
	i				= -1;
	while(line[++i] != '\0')
	{
		if ((i + 1) <= len)
			if (ft_isprint(line[i]) && ft_isspace(line[i + 1]))
				return (1);
	}
	return (0);
}

void				auto_complete(t_msh *f, char *line)
{
	int				len;
	struct winsize	win;
	char			*pwd;
	char			**autoCompleteMtx;

	pwd = getcwd(NULL, 0);
	autoCompleteMtx = ft_split_whitespaces(line);
	len = ft_matrixlen(autoCompleteMtx);
	if (ft_matrixlen(autoCompleteMtx) > 1)
		len = len_dir(pwd, f, autoCompleteMtx[len -1]);
	else
		len = len_dirBasic(pwd, f);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	f->term.win_x = win.ws_col;
	f->term.win_y = win.ws_row;
	printDirectori(f, pwd, autoCompleteMtx[1]);
	f->term.tab_cursor += 1;
	if (f->term.tab_cursor == len)
		f->term.tab_cursor = 0;
	ft_strdel(&pwd);
	ft_free_mtx(autoCompleteMtx);
}
