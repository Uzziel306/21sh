/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <asolis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:37:11 by asolis            #+#    #+#             */
/*   Updated: 2017/09/02 17:50:15 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>

typedef struct		s_term
{
	struct termios	term;
	int				tab_cursor;
	int				shll_cursor;
	int				max;
	int				win_x;
	int				win_y;
}					t_term;

typedef struct		s_shll
{
	char			*p_bin;
	char			*p_home;
	char			*p_user;
}					t_shll;

typedef struct		s_axe
{
	int				i;
	int				j;
	size_t			count;
	char			*start;
	char			*end;
	char			*tmp;
}					t_axe;

typedef struct		s_msh
{
	t_shll			sh;
	t_axe			axe;
	t_term			term;
}					t_msh;

/*
** lists functions used in the proyect.. lists_functions.c
*/
void				ft_lstsearch(t_list *e, char *name);
void				ft_lstaddnth(t_list *e, t_list	*new, int nb);
void				ft_lstedit(t_list *e, char *name, char *value);
void				ft_lstdeletenode(t_list *e, int nb);
char				**ft_lst_to_mtx(t_list *e);
/*
** cd command functions used in the proyect.. cd_command.c and cd_command_2.c
*/
char				*cd(char **mtx, char *pwd);
void				validation_cd_command(char **matrix, t_msh *f, t_list *e);
void				cd_command(char *pwd, char	*old_pwd, t_list *e);
int					general(char *direction, char	*old_pwd, t_list *e);
void				cd_command_minus(t_list *e);
void				cd_command_home(t_list *e);
void				cd_command_len_1(t_msh *f, t_list *e);
/*
** echo command functions used in the proyect.. echo_command.c
*/
void				validation_echo(char **c, t_list *e);
int					echo(char *c);
/*
** setenv command functions used in the proyect.. get_env.c
*/
t_list				*get_env();
void				set_env(t_list *e, char *name, char *value);
void				multi_setenv(t_list *e, char **values, int len, t_msh *f);
void				setenv_validation(t_list *e, char **mtx, t_msh *f);
int					validation_name(char *str);
/*
** unsetenv command functions used in the proyect.. unsetenv.c
*/
void				unsetenv_validation(t_list *e, char **name);
int					unset_env(t_list *e, char *name, int i);
/*
** helper functions used in the proyect.. helper.c helper_2.c
*/
int					ft_error_path(char *pwd);
char				*get_last_part();
void				ft_printlst(t_list *e);
void				free_shit(char *a, char *b, char *c);
int					ft_memdel_int(void **ap);
int					ft_ismayus(int c);
t_msh				*get_t_msh(t_msh *f);
/*
** main functions used in the proyect.. main.c
*/
char				*readline(void);
void				get_command(char *str, t_msh *f, t_list *e);
int					get_shell(t_msh *f);
void				pre_get_command(char *str, t_msh *f, t_list *e);
/*
** run commands functions used in the proyect.. run_command.c
*/
char				*get_path(t_list *e);
void				executable(char **mtx, t_list *e);
int					path_command(char **mtx, t_list *e);
/*
** exit functions used in the proyect.. exit.c
*/
void				exitazo(t_list *e, t_msh *f);
void				pwd(void);
char				*join_path(char *str, char *str2);
void				changing_pwd_oldpwd(char *new_pwd, char *old_pwd, t_list *e);
char				*cutting_last_path(char *str);
/*
** readterm functions used in the proyect.. readterm.c
*/
void				starting_env(t_msh *f);
char				*get_lines(void);
char				*readterm(void);
void				put_cursor(char c);
#endif
