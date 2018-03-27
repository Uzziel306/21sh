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
	f->term.history_len += 1;
	tmp = ft_lstnew(line, ft_strlen(line) + 1);
	ft_lstaddnth(&f->term.x, tmp, 1);
}

void			get_history(char *line, t_msh *f)
{
	f->term.ln_len = ft_strlen(line);
	f->term.ln_cursor = f->term.ln_len;
	ft_str_to_lst(f, line);
	f->term.history_flag = 1;
}

void			print_history(t_msh *f, int UpDown)
{
	t_list		*tmp;
	int			i;

	i = 0;
	tmp = f->term.x;
	f->term.history_cursor = 
	(UpDown == 1) ? f->term.history_cursor + 1 : f->term.history_cursor - 1;
	if (f->term.history_cursor > f->term.history_len || f->term.history_cursor <= 0)
	{
		f->term.history_cursor = 0;
		f->term.history_flag = 1;
		return ;
	}
	while (tmp)
	{
		if (i == f->term.history_cursor)
		{
			get_history(tmp->content, f);
			break ;
		}
		i++;
		tmp = tmp->next;
	}
}