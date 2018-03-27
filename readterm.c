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
	term.c_lflag &= ~(ICANON | ECHO  | ECHOCTL);
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

void		printing_line(t_line **l, int cursor, int flag)
{
	t_line	*tmp;
	int		i;

	i = 0;
	if (!l)
	{
		put_cursor(' ');
		return ;
	}
	tmp = *l;
	flag = 0;
	while (tmp)
	{
		if (cursor == i)
		{
			ft_termcmd("us");
			flag = 1;
		}
		i++;
		ft_putchar_fd(tmp->content, 2);
		ft_termcmd("ue");
		tmp = tmp->next;
	}
	if (flag == 0)
		put_cursor(' ');
}

void		ft_char(t_msh *f, char c)
{
	if (c == '\n')
	{
		if (f->term.ln_len == 0)
			put_cursor(' ');
		if (f->term.tab_flag == 1)
			enter(f);
		f->term.enter = 1;
		if (f->term.history_flag == 1)
			history_enter(f);
		f->term.history_cursor = 0;
		return ;
	}
	else if (c == KEY_TAB)
		tabs(f);
	else if (c == KEY_DEL)
		del(f);
	else if (c == KEY_ESC)
		esc(f);
	else if (ft_is_printable(c))
		get_char(f, c, 0);
}

void			ft_copy(char *buf,t_msh *f)
{
	return ;
}

void			ft_iskeycap(char *buf, t_msh *f)
{
	if (KEY_LEFT || KEY_UP || KEY_RIGHT || KEY_DOWN || KEY_FN_LEFT || KEY_FN_RIGHT || KEY_FN_DOWN)
		ft_key(buf, f);
	else
		ft_copy(buf, f);
}

char		*get_lines(t_msh *f)
{
	char	*line;
	char	buf[2070];
	int		endLine = 0;

	line = NULL;
	ft_termcmd("sc");
	put_cursor(' ');
	while ((endLine = read(0, buf, 2070)) && f->term.enter != 1)
	{
		buf[endLine] = '\0';
		// ft_putnbr(ft_strlen(buf));
		// ft_putnbr_fd(buf[0], 2);
		// ft_putnbr_fd(buf[1], 2);
		// ft_putnbr_fd(buf[2], 2);
		// exit(2);
		ft_termcmd("rc");
		ft_termcmd("cd");
		if (ft_strlen(buf) > 1)
			ft_iskeycap(buf, f);
		else
			ft_char(f, buf[0]);
		if (f->term.enter == 1)
			break ;
		printing_line(&f->line, f->term.ln_cursor);
		ft_putchar_fd('\n', 2);
	}
	line = ft_lst_to_str(f);
	ft_lstdeln(&f->line);
	return (line);
}


char			*readterm(t_msh *f)
{
	char		*line;
	char		*pwd;

	pwd = get_last_part();
	ft_printfcolor("%s%s%s", "@", 33, f->sh.p_user, 33, "$>", 33);
	ft_printfcolor("%s%s%s", "*[", 34, pwd, 31, "]* ", 34);
	ft_strdel(&pwd);
	f->line = NULL;
	line = get_lines(f);
	ft_putstr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	f->term.enter = 0;
	f->term.ln_cursor = 0;
	f->term.ln_len = 0;
	history(line, f);
	return (line);
}