#include "21sh.h"

void		starting_env(t_msh *f)
{
	char	*env;
	int		ret;

	if (!(env = getenv("TERM")))
		ft_error("didn't find TERM enviroment");
	if (!(ret = tgetent(NULL, env)))
		ft_error("getting the TERM enviroment");
	if (tcgetattr(0, &f->term.term) != 0)
		ft_error("didn't store the attributes of termios structure");
	f->term.term.c_lflag &= ~(ICANON | ECHO);
	f->term.term.c_cc[VMIN] = 1;
	f->term.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &f->term.term);
	// ft_termcmd("ti");
	ft_termcmd("vi");
}

void		put_cursor(char c)
{
	ft_termcmd("us");
	ft_putchar_fd(c, 2);
	ft_termcmd("ue");
}

void		printing_line(char *line, int cursor)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (line[++i] != '\0')
	{
		if (cursor == i)
		{
			ft_termcmd("us");
			ft_putchar_fd(line[i], 2);
			ft_termcmd("ue");
			flag = 1;
			continue ;
		}
		ft_putchar_fd(line[i], 2);
	}
	if (flag != 1)
		put_cursor(' ');
}

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

void		auto_complete(void)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	char			*pwd;
	static int		i;
	t_msh			*f;
	int				len;
	struct winsize	win;

	// ft_termcmd("ce");
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
		// printf("%s\n", pdirent->d_name);
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

char		*get_lines(void)
{
	long	key;
	char	c;
	int		ret;
	char	*line;
	int		i;
	int		cursor;
	// t_list	*v;

	cursor = 0;
	ret = 0;
	i = 0;
	line = ft_strnew(4080);

	ft_termcmd("sc");
	put_cursor(' ');
	while ((read(0, &key, sizeof(int))) != 0)
	{
		ft_termcmd("rc");
		c = (char)key;
		// ft_termcmd("dl");
		// ft_termcmd("mr");
		// printf("%ld\n", key);
		if (4299447067 == key)
			continue;
		ft_termcmd("ce");
		if (key == 9) //tab
		{
			ft_termcmd("sc");
			ft_termcmd("ce");
			ft_putstr_fd(line, 2);
			// ft_termcmd("sc");
			auto_complete();
			continue ;
		}
		// if (key == 27 || key == 91)
		// 	continue ;
		if (c == '\n') //enter
		{
			// ft_termcmd("rc");
			ft_termcmd("cd");
			break ;
		}
		if (c == 0x7f) //del
		{
			if (i == 0)
			{
				put_cursor(' ');
				continue ;
			}
			ft_termcmd("dm");
			line[i - 1] = '\0';
			printing_line(line, i);
			ft_termcmd("rc");
			i --;
			continue ;
		}
		if (key == 140734606957339) //arriba
		{
			printing_line(line, i);
		// 	ft_termcmd("rc");
			continue ;
		}
		if (key == 140734607088411) // derecha
		{
			printing_line(line, i);
		// 	ft_termcmd("rc");
			continue ;
		}
		if (key == 140734607022875) //abajo
		{
			printing_line(line, i);
		// 	ft_termcmd("rc");
			continue ;
		}
		if (key == 140734607153947) //izquierda
		{
			printing_line(line, i);
			continue ;
		}
		if (c >= 32 && c <= 126)
		{
			line[i] = c;
			line[i + 1] = '\0';
		}
		i++;
		// // ft_putnbr_fd(i, 2);
		// // ft_putchar_fd('\n', 2);
		printing_line(line, i);
		// // ft_putnbr_fd(key, 2);
		// // if (key == 2791)
		// // 	ft_termcmd("bt");
		// // ft_putchar_fd(c, 2);
		//
		// // ft_clrscreen(1);
		key = 0;
	}
	// ft_putchar_fd('!', 2);
	ft_putstr_fd(line, 2);
	// ft_putchar_fd('!', 2);
	ft_putchar_fd('\n', 2);
	// ft_termcmd("dm");
	return (line);
}

char			*readterm(void)
{
	char		*line;
	t_list	*x;

	x = NULL;
	line = get_lines();
	return (line);
}
