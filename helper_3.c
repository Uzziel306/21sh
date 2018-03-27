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

void		ft_str_to_lst(t_msh *f, char *line)
{
	int		i;
	t_line	*tmp;

	ft_lstdeln(&f->line);
	if (!line)
		return ;
	i = -1;
	while (line[++i])
	{
		tmp = (t_line*)ft_memalloc(sizeof(t_line));
		tmp->content = line[i];
		tmp->next = NULL;
		ft_lstaddbackline(&f->line, tmp);
	}
	ft_memdel((void**)&line);
}

void		history_enter(t_msh *f)
{
	t_list	*data;
	t_list	*new;

	if (f->term.history_cursor > 1)
	{
		f->term.history_flag = 0;
		data = ft_returnnode(&f->term.x, f->term.history_cursor - 1);
		new = ft_lstnew(data->content, ft_strlen(data->content) + 1);
		ft_memdel((void**)&data->content);
		ft_memdel((void**)&data);
		ft_lstaddnth(&f->term.x, new, 1);
	}
}

void		ft_key(char *buf, t_msh *f)
{
	// ft_putstr_fd("huevos", 2);
	// exit(3);
	if (KEY_LEFT ||KEY_RIGHT || KEY_DOWN || KEY_UP) //arrows
		arrows(buf, f);
	else if (KEY_FN_LEFT ||KEY_FN_RIGHT)
		fn_arrows(f, buf);
}