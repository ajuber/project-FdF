#include "mlx.h"
#include "FdF.h"
#include <fcntl.h>
/*
t_pnt	count(char **str)
{
	t_pnt	size;

	size.x = 0;
	size.y = 0;
	while (str[size.y][0])
		size.y++;
	ft_putendl("----------fail--------------");
	while (str[0][size.x])
		size.x++;
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
	ft_putendl("----------avant GNL-------------");
	while (get_next_line(fd, line))
	{
		tmp = &str1[0];
		str1 = ft_strjoin(tmp, line[0]);
		free(tmp);
		tmp = &str1[0];
		str1 = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	ft_putendl("----------apres GNL-------------");
	line = ft_strsplit(str1, '\n');
	ft_putendl("----------apres strsplit-------------");
	return (line);
}*/

void	ligne(void *mlx, void *win, int repere,t_pnt size, t_pnt pnt,int tab[11][19])
{
	float	a;
	float	b;
	int		mem_size_x;
	int 	mem_size_y;
	int		i;

	i = 1;
	mem_size_y = size.y;
	mem_size_x = size.x + repere;
	a = (float)(tab[pnt.y][pnt.x + 1] - tab[pnt.y][pnt.x]) / repere;
	b = (size.y - tab[pnt.y][pnt.x]) - (a * size.x);
	size.x++;
	while (size.x < mem_size_x)
	{
		size.y = mem_size_y - tab[pnt.y][pnt.x] + i * -a;
		mlx_pixel_put(mlx, win, size.x, size.y, 0x00FFFFFF);
		size.x++;
		i++;
	}
	size.y = mem_size_y + 1;
}

void	colonne(void *mlx, void *win, int repere, t_pnt size, t_pnt pnt, int tab [11][19])
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
//	char	**str;
	int		tab[11][19] =
			{
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,10,10,0,0,10,10,0,0,0,10,10,10,10,10,0,0,0},
				{0,0,10,10,0,0,10,10,0,0,0,0,0,0,0,10,10,0,0},
				{0,0,10,10,0,0,10,10,0,0,0,0,0,0,0,10,10,0,0},
				{0,0,10,10,10,10,10,10,0,0,0,0,10,10,10,10,0,0,0},
				{0,0,0,10,10,10,10,10,0,0,0,10,10,0,0,0,0,0,0},
				{0,0,0,0,0,0,10,10,0,0,0,10,10,0,0,0,0,0,0},
				{0,0,0,0,0,0,10,10,0,0,0,10,10,10,10,10,10,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			};
	t_pnt	size;
	t_pnt	pnt;
	int		repere;

	//str = recup_file(argv[1]);
	//size = count(str);
	//ft_putendl("----------avant affichage size-------------");
	//ft_putnbr(size.x);
	//ft_putnbr(size.y);
	//ft_putendl("----------apres GNL-------------");
	mlx = mlx_init();
	pnt.y = 0;
	repere = 378/18;
	size.y = 11;
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	while (size.y <= 400)
	{
		pnt.x = 0;
		size.x = 11;
		while (size.x <= 390)
		{
			mlx_pixel_put(mlx, win, size.x, size.y - tab[pnt.y][pnt.x], 0x00FFFFFF);
			if (pnt.x < 18)
				ligne(mlx, win, repere, size, pnt, tab);
			if (pnt.y < 10)
				colonne(mlx, win, repere, size, pnt, tab);
			size.x += repere;
			pnt.x++;
		}
		size.y += repere;
		pnt.y++;
	}
	mlx_loop(mlx);
	return (0);
}
