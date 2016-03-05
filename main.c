/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:02:43 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/05 13:43:11 by ajubert          ###   ########.fr       */
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
	size.x = size.x - ((repere / 2) * pnt.y);
	mem_size_x = size.x + repere;
	a = (float)(tab[pnt.y][pnt.x + 1] - tab[pnt.y][pnt.x]) / repere;
	//b = (size.y - tab[pnt.y][pnt.x]) - (a * size.x);
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
	float	mem_size_y;
	float	mem_size_x;
	float	a;
	float	b;
	float	i;

	i = 0;
	mem_size_x = (float)(size.x - ((repere / 2) * pnt.y));
	//printf("memsize.x : %d\n",mem_size_x);
	//a = (float)((tab[pnt.y + 1][pnt.x] - ((repere / 2) * pnt.y) - tab[pnt.y][pnt.x]) / repere);
	b = size.y - tab[pnt.y][pnt.x];
	mem_size_y = (float)(size.y + repere - tab[pnt.y + 1][pnt.x]);
	size.y = size.y - tab[pnt.y][pnt.x];
//	a = (float)1.000 / ((mem_size_y - size.y) / ((size.x - ((repere / 2) * (pnt.y + 1))) - mem_size_x) * 0.5);
	a = (float)(1.000 / ((mem_size_y - size.y) / ((size.x - ((repere / 2) * (pnt.y + 1))) - mem_size_x) * 0.5));
	//if (a < -1)
	//	a = a + 1;
//	else if (a > -1)
//		a = a - 1;
	printf("a : %f -------- b : %f\n", a, b);
	//a = -1;
	while (++size.y < mem_size_y)
	{
		i += 0.5;
//		size.x = mem_size_x - (0.5 * i);
		size.x = mem_size_x + (i * a);
	//	printf("size.x : %d\n",size.x);
		if (size.x > 0 && size.x < l && size.y > 0 && size.y < l)
			mlx_pixel_put(mlx, win, size.x, size.y, 0x00FFFFFF);
	}
}

int main(int argc, char **argv)
{
	t_param	param;
	char	**str;
	int		**tab1;
	t_pnt	size;
	t_pnt	size_win;
	t_pnt	pnt;
	int		repere;
	t_pnt	test;

	str = recup_file(argv[1]);
	size = count(str);
	tab1 = char_to_int(size, str);
	param.mlx = mlx_init();
	pnt.y = 0;
	if (size.x < size.y)
		repere = (h / 2) / (size.y - 1);
	else
		repere = (l / 2) / (size.x - 1);
	size_win.y = (h / 2) - ((size.y / 2) * repere);
	test.y = size_win.y;
	size_win.x = (l / 2) - ((size.x / 2) * repere);
	test.x = size_win.x;
	//size.y = 11;
	param.win = mlx_new_window(param.mlx, l, h, "mlx 42");
	ft_putendl("-------------boucle-------------");
	while (size_win.y <= test.y + ((size.y - 1) * repere))
	{
		pnt.x = 0;
		size_win.x = (l / 2) - ((size.x / 2) * repere);
		//size.x = 11;
		while (size_win.x <= test.x + ((size.x - 1) * repere))
		{
			mlx_pixel_put(param.mlx, param.win, size_win.x - ((repere / 2) * pnt.y), size_win.y - tab1[pnt.y][pnt.x], 0x00FFFFFF);
			if (pnt.x < size.x - 1)
				ligne(param.mlx, param.win, repere, size_win, pnt, tab1);
			if (pnt.y < size.y - 1)
				colonne(param.mlx, param.win, repere, size_win, pnt, tab1);
			size_win.x += repere;
			pnt.x++;
		}
		size_win.y += repere;
		pnt.y++;
	}
	ft_putendl("-------------fin boucle-------------");
	mlx_key_hook(param.win, my_key_funct, 0);
	mlx_loop(param.mlx);
	return (0);
}
