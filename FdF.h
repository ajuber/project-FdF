#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <stdlib.h>

# define l 800
# define h 800

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
}					t_var;

int					my_key_funct(int keycode, void *param);
int					**char_to_int(t_pnt size, char **str);
t_pnt				calc_repere(t_var *var, t_pnt size_tab);

#endif
