#include "../../inc/cub3d.h"

int check_file(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (error("cannot open file"));
    close(fd);
    return (0);
}

int check_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}
