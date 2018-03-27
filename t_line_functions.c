#include "21sh.h"

int			ft_lstlen(t_line *lst)
{
	t_line	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void		ft_lstdeletenodeline(t_line **head_ref, int position)
{
	t_line *temp;
	int i;
	t_line *next;

	i = 0;
	temp = *head_ref;
	if (*head_ref == NULL)
		return;
	if (position == 0)
	{
		*head_ref = temp->next;
		free(temp);
		return;
	}
	while (temp != NULL && i < position - 1)
	{
		temp = temp->next;
		i++;
	}
	if (temp == NULL || temp->next == NULL)
		return;
	next = temp->next->next;
	free(temp->next);
	temp->next = next;
}

void		ft_lstdeln(t_line **alst)
{
	t_line 	*list;
	t_line	*prev;

	if (*alst)
	{
		list = *alst;
		while (list)
		{
			prev = list;
			list = list->next;
			free(prev);
		}
	}
	*alst = NULL;
}

void		get_char(t_msh *f, char c)
{
	t_line	*tmp;

	tmp = (t_line*)ft_memalloc(sizeof(t_line));
	tmp->content = c;
	tmp->next = NULL;
	if (f->term.ln_cursor == f->term.ln_len)
		ft_lstaddbackline(&f->line, tmp);
	else
		ft_lstaddnthline(&f->line, tmp, f->term.ln_cursor + 1);
	f->term.ln_cursor += 1;
	f->term.ln_len += 1;
}

char		*ft_lst_to_str(t_msh *f)
{
	int		i;
	t_line	*tmp;
	char	*ln;

	ln = (char*)ft_memalloc(sizeof(char) * f->term.ln_len + 1);
	i = 0;
	tmp = f->line;
	while(tmp)
	{
		ln[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	ln[i] = '\0';
	return (ln);
}

void		ft_lstaddbackline(t_line **alst, t_line *new)
{
	t_line	*tmp;

	if (!*alst && !new)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		ft_lstaddnthline(t_line **e, t_line *new, int nb)
{
	t_line	*tmp;
	int		i;

	i = 1;
	if (nb == 1)
	{
		new->next = *e;
		*e = new;
		return ;
	}
	tmp = *e;
	while (i < nb - 1)
	{
		tmp = tmp->next;
		i++;
	}
	new->next = tmp->next;
	tmp->next = new;
}
