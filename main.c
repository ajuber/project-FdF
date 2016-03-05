/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:02:43 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/05 15:41:49 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "FdF.h"
#include <fcntl.h>
#include <stdio.h>

t_pnt	count(char **str)
{
	t_pnt	size;
	int		i;
	int		test;

	test = 1;
	i = 0;
	size.x = 0;
	size.y = 0;
	while (str[size.y][0] != '\0')
		size.y++;
	while (str[0][i])
	{
		if (str[0][i] == ' ')
			test = 1;
		if (str[0][i] != ' ' && test)
		{
			size.x++;
			test = 0;
		}
		i++;
	}
	return (size);
}

char	**recup_file(char *str)
{
	int		fd;
	char	**line;
	char	*str1;
	char	*tmp;

	line = (char **)malloc(sizeof(char *) * 1);
	line[0] = ft_strdup("\0");
	str1 = ft_strdup("\0");
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, line))
	{
		tmp = &str1[0];
		str1 = ft_strjoin(tmp, line[0]);
		free(tmp);
		tmp = &str1[0];
		str1 = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	line = ft_strsplit(str1, '\n');
	return (line);
}

void	ligne(t_var var)
{
	float	a;
	float	b;
	int		mem_size_x;
	int		mem_size_y;
	int		i;

	i = 1;
	mem_size_y = var.size.y;
	var.size.x = var.size.x - ((var.repere / 2) * var.pnt.y);
	mem_size_x = var.size.x + var.repere;
	a = (float)(var.tab[var.pnt.y][var.pnt.x + 1]
			- var.tab[var.pnt.y][var.pnt.x]) / var.repere;
	var.size.x++;
	while (var.size.x < mem_size_x)
	{
		var.size.y = mem_size_y - var.tab[var.pnt.y][var.pnt.x] + i * -a;
		mlx_pixel_put(var.param.mlx, var.param.win,
				var.size.x, var.size.y, 0x00FFFFFF);
		var.size.x++;
		i++;
	}
	var.size.y = mem_size_y + 1;
}

void	colonne(t_var var)
{
	float	mem_size_y;
	float	mem_size_x;
	float	a;
	float	b;
	float	i;

	i = 0;
	mem_size_x = (float)(var.size.x - ((var.repere / 2) * var.pnt.y));
	b = var.size.y - var.tab[var.pnt.y][var.pnt.x];
	mem_size_y = (float)(var.size.y + var.repere
			- var.tab[var.pnt.y + 1][var.pnt.x]);
	var.size.y = var.size.y - var.tab[var.pnt.y][var.pnt.x];
	a = (float)(1.000 / ((mem_size_y - var.size.y) / ((var.size.x
						- ((var.repere / 2) * (var.pnt.y + 1))) - mem_size_x)
				* 0.5));
	printf("a : %f -------- b : %f\n", a, b);
	while (++var.size.y < mem_size_y)
	{
		i += 0.5;
		var.size.x = mem_size_x + (i * a);
		if (var.size.x > 0 && var.size.x < l &&
				var.size.y > 0 && var.size.y < l)
			mlx_pixel_put(var.param.mlx, var.param.win,
					var.size.x, var.size.y, 0x00FFFFFF);
	}
}

int		main(int argc, char **argv)
{
	char	**str;
	t_pnt	size_tab;
	t_pnt	test;
	t_var	var;

	str = recup_file(argv[1]);
	size_tab = count(str);
	var.tab = char_to_int(size_tab, str);
	var.param.mlx = mlx_init();
	var.pnt.y = 0;
	test = calc_repere(&var, size_tab);
	var.param.win = mlx_new_window(var.param.mlx, l, h, "FdF");
	while (var.size.y <= test.y + ((size_tab.y - 1) * var.repere))
	{
		var.pnt.x = 0;
		var.size.x = (l / 2) - ((size_tab.x / 2) * var.repere);
		while (var.size.x <= test.x + ((size_tab.x - 1) * var.repere))
		{
			mlx_pixel_put(var.param.mlx, var.param.win, var.size.x - ((var.repere / 2) * var.pnt.y), var.size.y - var.tab[var.pnt.y][var.pnt.x], 0x00FFFFFF);
			if (var.pnt.x < size_tab.x - 1)
				ligne(var);
			if (var.pnt.y < size_tab.y - 1)
				colonne(var);
			var.size.x += var.repere;
			var.pnt.x++;
		}
		var.size.y += var.repere;
		var.pnt.y++;
	}
	mlx_key_hook(var.param.win, my_key_funct, 0);
	mlx_loop(var.param.mlx);
	return (0);
}
