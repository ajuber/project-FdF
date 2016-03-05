/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:42:23 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/05 16:29:47 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		**alloc(t_pnt size)
{
	int i;
	int **tab;

	i = 0;
	tab = (int **)malloc(sizeof(int *) * size.y);
	while (i < size.y)
	{
		tab[i] = (int *)malloc(sizeof(int) * size.x);
		i++;
	}
	return (tab);
}

int		**char_to_int(t_pnt size, char **str)
{
	int		**tab;
	t_pnt	i;
	int		j;

	tab = alloc(size);
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
