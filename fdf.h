/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:26:51 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/05 18:14:27 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <stdlib.h>
# include "mlx.h"
# include <fcntl.h>

# define L 800
# define H 800

typedef struct		s_pnt
{
	int				x;
	int				y;
}					t_pnt;

typedef struct		s_param
{
	void			*mlx;
	void			*win;
}					t_param;

typedef struct		s_var
{
	t_param			param;
	int				repere;
	t_pnt			size;
	t_pnt			pnt;
	int				**tab;
	t_pnt			size_tab;
}					t_var;

int					my_key_funct(int keycode, t_var *var);
int					**char_to_int(t_pnt size, char **str);
t_pnt				calc_repere(t_var *var);
char				**recup_file(char *str);
void				pre_calc(t_var var, t_pnt test);

#endif
