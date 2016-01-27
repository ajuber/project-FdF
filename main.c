#include "mlx.h"
#include "FdF.h"
#include <fcntl.h>

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
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	char	**str;
	t_pnt	size;

	str = recup_file(argv[1]);
	size = count(str);
	ft_putendl("----------avant affichage size-------------");
	ft_putnbr(size.x);
	ft_putnbr(size.y);
	ft_putendl("----------apres GNL-------------");
	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
	mlx_loop(mlx);
	return (0);
}
