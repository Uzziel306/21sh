#include "21sh.h"

t_list			*ft_returnnode(t_list **head_ref, int position)
{
	t_list *temp;
	int i;
	t_list *next;
	t_list *tmp;

	i = 0;
	temp = *head_ref;
	if (*head_ref == NULL)
		return NULL;
	while (temp != NULL && i < position - 1)
	{
		temp = temp->next;
		i++;
	}
	if (temp == NULL || temp->next == NULL)
		return NULL;
	tmp = temp->next;
	next = temp->next->next;
	temp->next = next;
	return tmp;
}

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
	t_list		*data;
	char		*ln;

	ft_termcmd("bl");
	ln = ft_strdup(line);
	f->term.ln_len = ft_strlen(line);
	f->term.ln_cursor = f->term.ln_len;
	f->term.history_flag = 1;
	return (ln);
}

void			print_history(char **line, t_msh *f, int o, int i)
{
	t_list		*tmp;

	ft_strdel(line);
	if (f->term.history_len == 0)
		return ;
	tmp = f->term.x;
	if (o == 1)
		f->term.history_cursor += 1;
	else
		f->term.history_cursor -= 1; 
	if (f->term.history_cursor > f->term.history_len || f->term.history_cursor < 0)
	{
		put_cursor(' ');
		ft_lstdeln(&f->line);
		f->term.history_cursor = 0;
		f->term.history_flag = 1;
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