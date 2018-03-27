#include "21sh.h"

void		arrows(char *buf, t_msh *f)
{
		// if(KEY_LEFT)
		// 	exit(0);
	if (KEY_LEFT && f->term.ln_cursor > 0)
		{
			f->term.ln_cursor -= 1;
			// exit(0);
		}
	else if (KEY_RIGHT && f->term.ln_cursor < f->term.ln_len)
		{f->term.ln_cursor += 1;}
	else if (KEY_UP || KEY_DOWN)
	{
		if (f->term.history_len > 0)
			(KEY_UP) ? print_history(f, 1) : print_history(f, 0);
		else
			ft_termcmd("bl");
	}
}

void		tabs(t_msh *f)
{
	char *line;

	if (f->term.ln_len == 0)
		ft_termcmd("bl");
	else
	{
		line = ft_lst_to_str(f);
		f->term.tab_flag = 1;
		ft_termcmd("sc");
		ft_termcmd("ce");
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		auto_complete(f);
		ft_strdel(&line);
	}
}

void		esc(t_msh *f)
{
	if (f->term.ln_len == 0)
	{
		ft_termcmd("bl");
		// put_cursor(' ');
	}
	else if (f->term.tab_flag == 1)
	{
		ft_termcmd("cd");
		f->term.tab_flag = 0;
		//printing_line(*line, f->term.ln_cursor);
	}
	else
	{
		f->term.esc_flag = (f->term.esc_flag == 0) ? 1 : 0;
		ft_termcmd("bl");
		//printing_line(*line, f->term.ln_cursor);
	}
}

void		enter(t_msh *f)
{
	ft_termcmd("bl");
	ft_termcmd("cd");
	if (f->term.tab_flag == 1)
	{
		f->term.tab_flag = 0;
		get_autocomplete(f);
	}
}

void		del(t_msh *f)
{
	if (f->term.esc_flag == 1)
	{
		ft_termcmd("ce");
		f->term.esc_flag = 0;
		ft_lstdeln(&f->line);
		f->term.ln_cursor = 0;
		f->term.ln_len = 0;
		put_cursor(' ');
	}
	else
	{
		if (f->term.ln_len > 0)
		{
			ft_lstdeletenodeline(&f->line, f->term.ln_cursor - 1);
			f->term.ln_cursor -= 1;
			f->term.ln_len -= 1;
		}
		else
			ft_termcmd("bl");
	}
}