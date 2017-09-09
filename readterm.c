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

char		*get_lines(t_msh *f)
{
	char	c;
	char	*line;
	int		i;

	i = 0;
	line = ft_strnew(4080);

	ft_termcmd("sc");
	put_cursor(' ');
	while ((read(0, &c, sizeof(char))) != 0)
	{
		ft_termcmd("rc");
		if (c == 0x43 || c == 0x44) //arrows
		{
			i -= 2;
			continue ;
		}
		else if (c == 0x41 || c == 0x42)
		{
			if (c == 0x41)
				i -= 3;
			else
				i -= 2;
			if (c == 0x42 && f->term.history_cursor == 0)
			{
				ft_termcmd("bl");
				continue ;
			}
			else if (c == 0x42 && f->term.history_cursor > 0)
				f->term.history_cursor -= 1;
			else if (c == 0x41 && f->term.history_cursor == f->term.history_len)
				f->term.history_cursor = 0;
			print_history(line, f);
			i = ft_strlen(line);
		}
		ft_termcmd("ce");
		if (c == 0x09) //tab
		{
			if (!(ft_strlen(line)))
			{
				put_cursor(' ');
				continue ;
			}
			f->term.tab_flag = 1;
			ft_termcmd("sc");
			ft_termcmd("ce");
			ft_putstr_fd(line, 2);
			// ft_termcmd("sc");
			auto_complete(line);
			continue ;
		}
		else if (c == '\n') //enter
		{
			// ft_termcmd("rc");
			ft_termcmd("cd");
			if (f->term.tab_flag == 1)
			{
				f->term.tab_flag = 0;
				line = get_autocomplete(line, f);
				break ;
			}
			break ;
		}
		else if (c == 0x7f) //del
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
		else if (c == 0x1b) //esc
		{
			if (f->term.tab_flag == 1)
			{
				ft_termcmd("cd");
				f->term.tab_flag = 0;
			}
		}
		if (c >= 32 && c <= 126)
		{
			line[i] = c;
			line[i + 1] = '\0';
		}
		i++;
		// ft_putnbr_fd(i, 2);
		printing_line(line, i);
	}
	ft_putstr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	return (line);
}

void			history(char *line, t_msh *f)
{
	t_list		*tmp;
	t_list		*tmp2;

	tmp2 = f->term.x;
	if (tmp2 != NULL)
	{
		while (tmp2)
		{
			if ((ft_strcmp(line, tmp2->content) == 0))
				return ;
			tmp2 = tmp2->next;
		}
	}
	f->term.history_len += 1;
	tmp = ft_lstnew(line, ft_strlen(line) + 1);
	ft_lstaddback(&f->term.x, tmp);
}

char			*print_history(char *line, t_msh *f)
{
	int			i;
	t_list		*tmp;


	//arreglar el history, arrgla el loop de la link list del history
	i = 0;
	tmp = f->term.x;
	while (tmp)
	{
		printf("%s\n", f->term.x->content);
		if (i == f->term.history_cursor)
		{
			ft_strdel(&line);
			f->term.history_cursor = 0;
			exit (0);
			return (f->term.x->content);
		}
		i++;
		tmp = tmp->next;
	}
	return (0);
}

char			*readterm(t_msh *f)
{
	char		*line;

	line = get_lines(f);
	history(line, f);
	return (line);
}
