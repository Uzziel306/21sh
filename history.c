#include "21sh.h"

void			history(char *line, t_msh *f)
{
	t_list		*tmp;
	t_list		*tmp2;

	tmp2 = f->term.x;
	if (!line)
		return ;
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

char			*get_history(char *line, t_msh *f)
{
	f->term.ln_len = ft_strlen(line);
	f->term.ln_cursor = f->term.ln_len;
	f->term.history_flag = 1;
	return (ft_strdup(line));
}


void			print_history(char **line, t_msh *f, int o, int i)
{
	t_list		*tmp;

	ft_strdel(line);
	if (f->term.history_len == 0)
	{
		ft_termcmd("bl");
		return ;
	}
	tmp = f->term.x;
	if (o == 1)
		f->term.history_cursor += 1;
	else
		f->term.history_cursor -= 1; 
	if (f->term.history_cursor > f->term.history_len || f->term.history_cursor < 0)
	{
		put_cursor(' ');
		f->term.history_cursor = 0;
		return ;
	}
	while (tmp)
	{
		if (i == f->term.history_cursor)
			*line = get_history(tmp->content, f);
		i++;
		tmp = tmp->next;
	}
}