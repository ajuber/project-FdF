/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:42:23 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/03 15:59:01 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int		**char_to_int(t_pnt size, char **str)
{
	int		**tab;
	t_pnt		i;
	int			j;

	i.y = 0;
	tab = (int **)malloc(sizeof(int *) * size.y);
	while (i.y < size.y)
	{
		tab[i.y] = (int *)malloc(sizeof(int) * size.x);
		i.y++;
	}
	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		j = 0;
		while (str[i.y][j] == ' ')
			j++;
		while (i.x < size.x)
		{
			tab[i.y][i.x] = ft_atoi(&str[i.y][j]);
			while (str[i.y][j] != ' ' && str[i.y][j])
				j++;
			while (str[i.y][j] == ' ' && str[i.y][j])
				j++;
			i.x++;
		}
		i.y++;
	}
	return (tab);
}
