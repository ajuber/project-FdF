/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:02:43 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/03 16:01:26 by ajubert          ###   ########.fr       */
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

void	ligne(void *mlx, void *win, int repere,t_pnt size, t_pnt pnt,int **tab)
{
	float	a;
	float	b;
	int		mem_size_x;
	int 	mem_size_y;
	int		i;
	char	*str;
	int		color;
	int		j;
	int		pow;

	j = 0;
	color = 0;
	str = ft_strdup("0x00FFFFFF");
	i = 1;
	mem_size_y = size.y;
	mem_size_x = size.x + repere;
	a = (float)(tab[pnt.y][pnt.x + 1] - tab[pnt.y][pnt.x]) / repere;
	b = (size.y - tab[pnt.y][pnt.x]) - (a * size.x);
	size.x++;
	if (tab[pnt.y][pnt.x + 1] > 0)
		str = ft_strcpy(str, "0x00FFFFFF");
	while (j < 10)
	{
		pow = ft_iterative_power(10, 9 - j);
		color = (int)str[j] * pow + color;
		j++;
	}
	while (size.x < mem_size_x)
	{
		size.y = mem_size_y - tab[pnt.y][pnt.x] + i * -a;
		mlx_pixel_put(mlx, win, size.x, size.y, 0x00FFFFFF);
		size.x++;
		i++;
	}
	size.y = mem_size_y + 1;
}

void	colonne(void *mlx, void *win, int repere, t_pnt size, t_pnt pnt, int **tab)
{
	int mem_size_y;

	mem_size_y = size.y + repere - tab[pnt.y + 1][pnt.x];
	printf("%d----------%d\n",mem_size_y, size.y);
	size.y = size.y - tab[pnt.y][pnt.x];
	while (++size.y < mem_size_y)
		mlx_pixel_put(mlx, win, size.x, size.y, 0x00FFFFFF);
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	char	**str;
	int		**tab1;
	t_pnt	size;
	t_pnt	pnt;
	int		repere;

	str = recup_file(argv[1]);
	size = count(str);
	tab1 = char_to_int(size, str);
	mlx = mlx_init();
	pnt.y = 0;
	repere = 378/18;
	size.y = 11;
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	while (size.y <= 230)
	{
		pnt.x = 0;
		size.x = 11;
		while (size.x <= 390)
		{
			mlx_pixel_put(mlx, win, size.x, size.y - tab1[pnt.y][pnt.x], 0x00FFFFFF);
			if (pnt.x < 18)
				ligne(mlx, win, repere, size, pnt, tab1);
			if (pnt.y < 10)
				colonne(mlx, win, repere, size, pnt, tab1);
			size.x += repere;
			pnt.x++;
		}
		size.y += repere;
		pnt.y++;
	}
	mlx_loop(mlx);
	return (0);
}
