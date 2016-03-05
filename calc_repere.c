/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_repere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 15:28:34 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/05 16:29:27 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pnt	calc_repere(t_var *var, t_pnt size_tab)
{
	t_pnt	test;

	if (size_tab.x < size_tab.y)
		var->repere = (H / 2) / (size_tab.y - 1);
	else
		var->repere = (L / 2) / (size_tab.x - 1);
	var->size.y = (H / 2) - ((size_tab.y / 2) * var->repere);
	test.y = var->size.y;
	var->size.x = (L / 2) - ((size_tab.x / 2) * var->repere);
	test.x = var->size.x;
	return (test);
}
