#include "../../inc/cub3d.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *new;

    if (!ptr)
        return malloc(new_size);
    new = malloc(new_size);
    if (!new)
        return NULL;
    ft_memcpy(new, ptr, old_size);
    free(ptr);
    return new;
}
