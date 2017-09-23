#include "21sh.h"

void		starting_env(void)
{
	char	*env;
	int		ret;
	struct termios term;

	if (!(env = getenv("TERM")))
		ft_error("didn't find TERM enviroment");
	if (!(ret = tgetent(NULL, env)))
		ft_error("getting the TERM enviroment");
	if (tcgetattr(0, &term) != 0)
		ft_error("didn't store the attributes of termios structure");
	term.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT
			| ECHOKE | ICRNL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
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
	if (flag == 0)
		put_cursor(' ');
}

char		*get_lines(t_msh *f)
{
	int		c;
	char	*line;
	t_line	*l;
	int		flag;
	long	key;

	l = NULL;
	line = NULL;
	ft_termcmd("sc");
	put_cursor(' ');
	while ((read(0, &c, sizeof(int))) != 0)
	{
		// ft_putchar_fd(c, 2);
		// printf("%d\n", c);
		// if (c >= 32 && c <= 126)
		// 	flag = 0;
		// else
		// 	flag = 1;
		ft_termcmd("rc");
		if (c == KEY_LEFT || c == KEY_RIGHT) //arrows
		{
			if (c == KEY_LEFT && f->term.ln_len == 0)
			{
				ft_termcmd("bl");
				continue ;
			}
			else if (c == KEY_LEFT && f->term.ln_len > 0)
				f->term.ln_cursor -= 1;
			else if (c == KEY_RIGHT && f->term.ln_cursor < f->term.ln_len)
				f->term.ln_cursor += 1;
		}
		// if (c == 0x50)
		// 	printf("rico\n" );
		// if (c == 0x41 || c == 0x42) //up down
		// {
		// 	ft_putstr_fd("up/donw\n", 2);
		// 	continue ;
		// }
		// 	// if (c == 0x42 && f->term.history_cursor == 0)
		// 	// {
		// 	// 	printf("lolas\n");
		// 	// 	ft_termcmd("bl");
		// 	// 	continue ;
		// 	// }
		// 	// else if (c == 0x42 && f->term.history_cursor > 0)
		// 	// 	f->term.history_cursor -= 1;
		// 	// else if (c == 0x41 && f->term.history_cursor == f->term.history_len)
		// 	// 	f->term.history_cursor = 0;
		// 	// else if (c == 0x41 && f->term.history_cursor < f->term.history_len)
		// 	// 	f->term.history_cursor += 1;
		// 	// if (!(line = print_history(line, f)))
		// 	// {
		// 	// 	i = 0;
		// 	// 	continue ;
		// 	// }
		// 	// i = ft_strlen(line);

		ft_termcmd("ce");
		if (c == KEY_TAB) //tab
		{
			if (f->term.ln_len == 0)
			{
				put_cursor(' ');
				ft_termcmd("bl");
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
		else if (c == KEY_DEL) //del
		{
			if (f->term.ln_len == 0)
			{
				put_cursor(' ');
				continue ;
			}
			ft_lstdeletenodeline(&l, f->term.ln_cursor);
			line = ft_lst_to_str(&l, f);
			printing_line(line, f->term.ln_cursor);
			f->term.ln_cursor -= 1;
			f->term.ln_len -= 1;
			continue ;
		}
		else if (c == KEY_ESC) //esc
		{
			if (f->term.tab_flag == 1)
			{
				ft_termcmd("cd");
				f->term.tab_flag = 0;
			}
		}
		line = get_char(&l, f, c, line);
		ft_putnbr_fd(f->term.ln_cursor, 2);
		ft_putnbr_fd(f->term.ln_len, 2);
		ft_putchar_fd('\n', 2);
		printing_line(line, f->term.ln_cursor);
		ft_putchar_fd('\n', 2);
		c = 0;
	}
	ft_lstdeln(&l);
	ft_putstr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	f->term.ln_cursor = 0;
	f->term.ln_len = 0;
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
	ft_strdel(&line);
	if (f->term.history_len == 0)
	{
		ft_termcmd("bl");
		return (NULL);
	}
	i = 1;
	tmp = f->term.x;
	while (tmp)
	{
		// printf("%d\n", f->term.history_cursor);
		if (i == f->term.history_cursor)
		{
			f->term.history_cursor = 0;
			printf("%s\n", f->term.x->content);
			exit (0);
			// return (f->term.x->content);
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
