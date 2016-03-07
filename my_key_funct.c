/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_key_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 18:10:19 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/07 13:57:33 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		zoom(t_var *var)
{
	t_pnt i;
	t_pnt test;

	var->repere *= 1.5;
	return (0);
	i.y = 0;
	while (i.y < var->size_tab.y)
	{
		i.x = 0;
		while (i.x < var->size_tab.x)
		{
			if (var->tab[i.y][i.x] > 0)
				var->tab[i.y][i.x] *= 1.5;
				i.x++;
		}
		i.y++;
	}
	mlx_clear_window(var->param.mlx, var->param.win);
	test = calc_repere(var);
	pre_calc(*var, test);
}

int		my_key_funct(int keycode, t_var *var)
{
	t_pnt	i;
	t_pnt	test;

	if (keycode == 53)
		exit(0);
	if (keycode == 126)
	{
		i.y = 0;
		while (i.y < var->size_tab.y)
		{
			i.x = 0;
			while (i.x < var->size_tab.x)
			{
				if (var->tab[i.y][i.x] > 0)
					var->tab[i.y][i.x] += 5;
				i.x++;
			}
			i.y++;
		}
		mlx_clear_window(var->param.mlx, var->param.win);
		test = calc_repere(var);
		pre_calc(*var, test);
	}
	if (keycode == 69)
		zoom(var);
	return (0);
}
