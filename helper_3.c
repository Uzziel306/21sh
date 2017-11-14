#include "21sh.h"

int			ft_is_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

void		ft_key(int c, t_msh *f, t_line	*l, char **line)
{
	if (c == KEY_LEFT || c == KEY_RIGHT || c == KEY_DOWN || c == KEY_UP) //arrows
		arrows(c, f, line);
	else if (c == KEY_TAB)
		tabs(f, line);
	else if (c == '\n')
	{
		if (f->term.ln_len == 0)
			put_cursor(' ');
		if (f->term.tab_flag == 1)
			*line = enter(f, line);
		f->term.enter = 1;
	}
	else if (c == KEY_DEL)
			del(f, line, &l);
	else if (c == KEY_ESC)
		esc(f, line);
}