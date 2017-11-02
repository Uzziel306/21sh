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

	if (!line)
		return ;
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

	l = NULL;
	line = NULL;
	ft_termcmd("sc");
	put_cursor(' ');
	while ((read(0, &c, sizeof(int))) != 0)
	{
		ft_termcmd("rc");
		if (c == KEY_LEFT || c == KEY_RIGHT || c == KEY_DOWN || c == KEY_UP) //arrows
			arrows(c, f);
		// ft_termcmd("fs");
		// ft_termcmd("nw");
		if (c == KEY_TAB) //tab
		{
			tabs(f, &line);
			continue ;
		}
		else if (c == '\n') //enter
		{

			if (f->term.ln_len == 0)
			{
				put_cursor(' ');
				continue ;
			}
			line = enter(f, &line);
			break ;
		}
		else if (c == KEY_DEL) //del
		{
			del(f, &line, &l);
			continue ;
		}
		else if (c == KEY_ESC) //esc
		{
			esc(f, &line);
			continue ;
		}
		line = get_char(&l, f, c, line);
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


char			*readterm(t_msh *f)
{
	char		*line;

	line = get_lines(f);
	history(line, f);
	return (line);
}
