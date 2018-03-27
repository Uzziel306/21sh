#include "21sh.h"

int			ErrorPipeDetector(char *str)
{
	int		i;
	int		cont;

	i = 0;
	cont = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] != '\0')
			if (str[i] == '|' && str[i + 1] == '|')
				return (0);
		i++;
	}
	return (1);
}

void		pipes(char *str, t_msh *f)
{
	char	**cmds;

	if (ErrorPipeDetector(str))
	{
		ft_matrixlen(cmds = ft_strsplit(str, '|'));
	}
}