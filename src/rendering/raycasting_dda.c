#include "cub3d.h"

void dda(t_game *game, t_ray *ray) // With the Digital Differential Analyzer algorithm we will increment the ray with 1 square everytime until we hit a wall
{
   
    if (ray->side_dist_x < ray->side_dist_y) //Depending on the starting distance we will find if it's better to use the X distance or the Y distance
    {
        ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x; //Here the Y distance is bigger than X, meaning the ray will take longer to reach the next Y
        ray->map_x = ray->map_x + ray->step_x; //Since we will reach X first, we increment side_dist with the respective delta dist and bump our ray position on the map to the next square
        ray->side = 0; //We flag side to 0 to indicate we have hit an E/W chunk of the grid(not necessarily the wall)
    }
    else
    {
        ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
        ray->map_y = ray->map_y + ray->step_y;
        ray->side = 1;
    }
        if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x >= game->map.width)
            return;
        
}

void	set_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x; //Perp distance will be the total distance from starting point up to the wall -1 delta distance since delta distance would go beyond the wall
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
    if (ray->perp_dist < 0.001) //Never let it be 0
        ray->perp_dist = 0.001;
}

void dda_loop(t_game *game, t_ray *ray)
{
    int hit = 0;
    while (!hit)
    {
        dda(game, ray);
        if (game->map.grid[ray->map_y][ray->map_x] == '1')
            hit = 1;
    } //When the loop ends we will know which side was hit and the corresponding distance
    set_perp_dist(ray);

}