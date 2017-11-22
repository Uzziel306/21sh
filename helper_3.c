#include "21sh.h"

int			ft_is_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// void		printlst(t_line **l)
// {
// 	t_line *h = *l;
// 	while (h)
// 	{
// 		printf("%c", h->content);
// 		h = h->next;
// 	}
// 	printf("!!\n");
// }

void		ft_str_to_lst(t_msh *f, char **line)
{
	int		i;
	t_line	*tmp;
	char	*lolas;

	if (!*line)
		return ;
	lolas = ft_strdup(*line);
	i = -1;
	ft_lstdeln(&f->line);
	while (lolas[++i])
	{
		tmp = (t_line*)ft_memalloc(sizeof(t_line));
		tmp->content = lolas[i];
		tmp->next = NULL;
		ft_lstaddbackline(&f->line, tmp);
	}
	ft_memdel((void**)&lolas);
}

void		ft_key(int c, t_msh *f, t_line	**l, char **line)
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
		f->term.history_cursor = 0;
	}
	else if (c == KEY_DEL)
			del(f, line, l);
	else if (c == KEY_ESC)
		esc(f, line);
}