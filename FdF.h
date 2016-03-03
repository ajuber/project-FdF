#ifndef FDF_H
# define FDF_H

# include "libft.h"

typedef struct		s_pnt
{
	int				x;
	int				y;
}					t_pnt;

int					**char_to_int(t_pnt size, char **str);

#endif
