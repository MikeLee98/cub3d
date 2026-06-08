#include "../../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (parse(&game, argv[1]))
        return (1);
	printf("map is valid\n");
	return (0);
}
