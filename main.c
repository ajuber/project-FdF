/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:02:43 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/07 13:17:57 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ligne(t_var var)
{
	float	a;
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
	float	i;

	i = 0;
	mem_size_x = (float)(var.size.x - ((var.repere / 2) * var.pnt.y));
	mem_size_y = (float)(var.size.y + var.repere
			- var.tab[var.pnt.y + 1][var.pnt.x]);
	var.size.y = var.size.y - var.tab[var.pnt.y][var.pnt.x];
	a = (float)(1.000 / ((mem_size_y - var.size.y) / ((var.size.x
						- ((var.repere / 2) * (var.pnt.y + 1))) - mem_size_x)
				* 0.5));
	while (++var.size.y < mem_size_y)
	{
		i += 0.5;
		var.size.x = mem_size_x + (i * a);
		if (var.size.x > 0 && var.size.x < L &&
				var.size.y > 0 && var.size.y < L)
			mlx_pixel_put(var.param.mlx, var.param.win,
					var.size.x, var.size.y, 0x00FFFFFF);
	}
}

void	pre_calc(t_var var, t_pnt test)
{
	var.pnt.y = 0;
	while (var.size.y <= test.y + ((var.size_tab.y - 1) * var.repere))
	{
		var.pnt.x = 0;
		var.size.x = (L / 2) - ((var.size_tab.x / 2) * var.repere);
		while (var.size.x <= test.x + ((var.size_tab.x - 1) * var.repere))
		{
			mlx_pixel_put(var.param.mlx, var.param.win, var.size.x
					- ((var.repere / 2) * var.pnt.y),
					var.size.y - var.tab[var.pnt.y][var.pnt.x], 0x00FFFFFF);
			if (var.pnt.x < var.size_tab.x - 1)
				ligne(var);
			if (var.pnt.y < var.size_tab.y - 1)
				colonne(var);
			var.size.x += var.repere;
			var.pnt.x++;
		}
		var.size.y += var.repere;
		var.pnt.y++;
	}
}

int		main(int argc, char **argv)
{
	char	**str;
	t_pnt	test;
	t_var	var;

	if (argc == 1)
		ft_putendl("Pas de map");
	str = recup_file(argv[1]);
	var.size_tab = count(str);
	var.tab = char_to_int(var.size_tab, str);
	var.param.mlx = mlx_init();
	test = calc_repere(&var);
	var.param.win = mlx_new_window(var.param.mlx, L, H, "FdF");
	pre_calc(var, test);
	mlx_key_hook(var.param.win, my_key_funct, &var);
	mlx_loop(var.param.mlx);
	return (0);
}
