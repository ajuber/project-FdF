/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_key_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 18:10:19 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/05 18:36:25 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		reset(t_var var)
{
	t_pnt	i;

	i.y = 0;
	while (i.y < L)
	{
		i.x = 0;
		while (i.x < H)
		{
			mlx_pixel_put(var.param.mlx, var.param.win, i.x, i.y, 0x00000000);
			i.x++;
		}
		i.y++;
	}
	return (0);
}

int		my_key_funct(int keycode, t_var *var)
{
	t_pnt	i;
	t_pnt	test;

	if (keycode == 53)
		exit(0);
	if (keycode == 69)
	{
		i.y = 0;
		while (i.y < var->size_tab.y)
		{
			i.x = 0;
			while (i.x < var->size_tab.x)
			{
				if (var->tab[i.y][i.x] > 0)
					var->tab[i.y][i.x] *=2 ;
				i.x++;
			}
			i.y++;
		}
		reset(*var);
		test = calc_repere(var);
		pre_calc(*var, test);
	}
	return (0);
}
