#include "21sh.h"

void		fn_arrows(t_msh *f, char **line, int c)
{
	if ((f->term.ln_cursor == 0 && c == KEY_FN_LEFT))
		return ft_termcmd("bl");
	else if ((f->term.ln_cursor == f->term.ln_len && c == KEY_FN_RIGHT))
		return ft_termcmd("bl");
	else if (!ft_strchr(*line, ' '))
		return ft_termcmd("bl");
	if (c == KEY_FN_RIGHT)
		fn_right(f, *line);
	else
		fn_left(f, *line);
	// printf("%d\n", f->term.ln_cursor);
	// exit (0);
}

void		fn_left(t_msh *f, char *line)
{
	while (f->term.ln_cursor > 0)
	{
		if (line[f->term.ln_cursor] == ' ' && ft_is_printable(line[f->term.ln_cursor - 1]))
		{
			f->term.ln_cursor--;
			break ;
		}
		f->term.ln_cursor--;
	}
}

void		fn_right(t_msh *f, char *line)
{
	while (f->term.ln_cursor < f->term.ln_len)
	{
		if (line[f->term.ln_cursor + 1] == ' ' && ft_is_printable(line[f->term.ln_cursor]))
		{
			f->term.ln_cursor++;
			break ;
		}
		f->term.ln_cursor++;
	}
}