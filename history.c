#include "21sh.h"

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