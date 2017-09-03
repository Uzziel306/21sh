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

char		*get_line(void)
{
	long	key;
	char	c;
	int		ret;
	char	*line;
	int		i;
	int		cursor;

	cursor = 0;
	ret = 0;
	i = 0;
	line = ft_strnew(4080);
	// line = NULL;
	// put_cursor(' ');
	while ((ret += read(0, &c, sizeof(char)) != 0))
	{
		key = (long)c;
		// printf("%ld\n", key);
		ft_termcmd("sc");
		ft_termcmd("ce");
		// key = (long)c;
		if (key == 10) //enter
			break ;
		if (key == 127)
		{
			ft_termcmd("dm");
			line[i - 1] = '\0';
			printing_line(line, i);
			ft_termcmd("rc");
			i --;
			continue ;
		}
		// if (key == 68)
		// {
		// 	printing_line(line, i - 2);
		// 	ft_termcmd("rc");
		// 	continue ;
		// }
		line[i] = c;
		line[i + 1] = '\0';
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
		ft_termcmd("rc");
	}
	ft_termcmd("ve");
	ft_putstr_fd(line, 2);
	// ft_termcmd("dm");
	return (line);
}

void		readterm(t_msh *f)
{
	starting_env(f);
	get_line();
	exit (3);
}
