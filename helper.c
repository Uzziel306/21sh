/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:22:40 by asolis            #+#    #+#             */
/*   Updated: 2017/08/30 19:08:29 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_error_path(char *pwd)
{
	ft_printfbasic("-bash: cd: ");
	ft_printfbasic("%s", pwd);
	ft_printfbasic(": No such file or directory\n");
	return (0);
}

void		zap(t_msh *f)
{
	f->axe.j = 0;
	f->axe.i = 1;
}

int			ft_matrixlen(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

void		ft_putmatrix(char **matrix)
{
	int		i;

	i = -1;
	while (matrix[++i] != NULL)
		ft_printfbasic("%s\n", matrix[i]);
}

void		ft_printlst(t_list *e)
{
	t_list	*tmp;

	tmp = e;
	while (tmp)
	{
		ft_printfbasic("%s\n", tmp->content);
		tmp = tmp->next;
	}
	free(tmp);
}
