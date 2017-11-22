#include "21sh.h"

void		arrows(int c, t_msh *f, char **line)
{
	if (((c == KEY_LEFT || c == KEY_RIGHT) && f->term.ln_len == 0)
|| ((c == KEY_DOWN || c == KEY_UP) && f->term.history_len == 0))
	{
		ft_termcmd("bl");
		put_cursor(' ');
	}
	else if (c == KEY_LEFT && f->term.ln_cursor > 0)
		f->term.ln_cursor -= 1;
	else if (c == KEY_RIGHT && f->term.ln_cursor < f->term.ln_len)
		f->term.ln_cursor += 1;
	else if (c == KEY_UP)
	{
		print_history(line, f, 1, 1);
		ft_str_to_lst(f, line);
	}
	else if (c == KEY_DOWN)
	{
		print_history(line, f, 0, 1);
		ft_str_to_lst(f, line);
	}

}

void		tabs(t_msh *f, char **line)
{
	if (f->term.ln_len == 0)
		{
			put_cursor(' ');
			ft_termcmd("bl");
		}
	else
	{
		f->term.tab_flag = 1;
		ft_termcmd("sc");
		ft_termcmd("ce");
		ft_putstr_fd(*line, 2);
		// ft_termcmd("sc");
		auto_complete(*line);
	}
}

void		esc(t_msh *f, char **line)
{
	if (f->term.ln_len == 0)
	{
		ft_termcmd("bl");
		put_cursor(' ');
	}
	else if (f->term.tab_flag == 1)
	{
		ft_termcmd("cd");
		f->term.tab_flag = 0;
		printing_line(*line, f->term.ln_cursor);
	}
	else
	{
		f->term.esc_flag = (f->term.esc_flag == 0) ? 1 : 0;
		ft_termcmd("bl");
		printing_line(*line, f->term.ln_cursor);
	}
}

char		*enter(t_msh *f, char **line)
{
	ft_termcmd("cd");
	if (f->term.tab_flag == 1)
	{
		f->term.tab_flag = 0;
		*line = get_autocomplete(*line, f);
	}
	return (*line);
}

void		del(t_msh *f, char **line, t_line	**l)
{
	if (f->term.ln_len == 0)
		put_cursor(' ');
	else if (f->term.esc_flag == 1)
	{
		ft_termcmd("ce");
		f->term.esc_flag = 0;
		ft_lstdeln(l);
		ft_strdel(line);
		f->term.ln_cursor = 0;
		f->term.ln_len = 0;
		put_cursor(' ');
	}
	else
	{
		ft_strdel(line);
		ft_lstdeletenodeline(l, f->term.ln_cursor - 1);
		f->term.ln_cursor -= 1;
		f->term.ln_len -= 1;
		*line = ft_lst_to_str(l, f);
		// printing_line(*line, f->term.ln_cursor);
	}
}