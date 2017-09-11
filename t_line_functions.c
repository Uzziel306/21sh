#include "21sh.h"

void		ft_lstdeletenodeline(t_line *e, int nb)
{
	t_line	*tmp;
	t_line	*tmp2;
	int		i;

	i = -1;
	tmp = e;
	if (nb == 1)
	{
		e = tmp->next;
		ft_memdel((void**)tmp);
		return ;
	}
	while (++i < nb - 2)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	free(tmp2);
	tmp2 = NULL;
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

char		*get_char(t_line **l, t_msh *f, char c, char *line)
{
	t_line	*tmp;

	if (c >= 32 && c <= 126)
	{
		if (line != NULL)
			ft_strdel(&line);
		f->term.ln_cursor += 1;
		f->term.ln_len += 1;
		tmp = (t_line*)ft_memalloc(sizeof(t_line));
		tmp->content = c;
		tmp->next = NULL;
		if (f->term.ln_cursor == f->term.ln_len)
			ft_lstaddbackline(l, tmp);
		else
			ft_lstaddnthline(l, tmp, f->term.ln_cursor - 1);
		line = ft_lst_to_str(l, f);
		return (line);
	}
	return (line);
}

char		*ft_lst_to_str(t_line **line, t_msh *f)
{
	int		i;
	t_line	*tmp;
	char	*ln;

	ln = (char*)ft_memalloc(sizeof(char) * f->term.ln_len + 1);
	i = 0;
	tmp = *line;
	while(tmp)
	{
		ln[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	ln[i] = '\0';
	// ft_putstr_fd(ln, 2);
	// exit(0);
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

	i = -1;
	if (nb == 1)
	{
		new->next = *e;
		*e = new;
		return ;
	}
	tmp = *e;
	while (i < nb - 2)
	{
		tmp = tmp->next;
		i++;
	}
	new->next = tmp->next;
	tmp->next = new;
}