#include "cub3d.h"

void init_ray_delta(t_game *game, t_ray *ray, int x)
{ 
    float camera_x;
    camera_x = 2.0 * x / WIN_W - 1.0;

    ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x; //Ray direction is based on current player position + plane * the camera
    ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;

    ray->map_x = (int)game->player.x; //Ray position on the GRID based on which grid the player is standing on
    ray->map_y = (int)game->player.y;

    if (ray->dir_x == 0) //If dir_x is 0 the ray will never hit the next X which causes issues with math making it impossible to calculate delta dist(distance from one X to another based on current direction,not starting position)
        ray->delta_dist_x = 1e30; // If this happens we turn delta distance into a close to infinite number, not needed in C++ but it was the simplest way to fix it for me
    else
        ray->delta_dist_x = fabs(1.0 / ray->dir_x); //If the direction is not 0 we use pythagoras, sqrt(1(one of the sides will always be 1 as it has hit the next equivalent point) + (raydirY^2  / raydirX^2))
                                        //fabs simplifies this math giving us the absolute positive of the result
    if (ray->dir_y == 0)
        ray->delta_dist_y = 1e30;  //Same deal but for Y
    else
        ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

void init_ray_step(t_game *game, t_ray *ray)
{
    if (ray->dir_x < 0) //If ray dir is negative side dist will be the distance from the starting position to the first X on the left
    {
        ray->step_x = -1; //Step will be negative to indicate we are going to the left
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x; //We will use the integer coordinate of the map and subtract with the real current position of the player
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x; //We will add +1 along with the subtraction if we're going in a positive direction, this will represent
    }  // represent the perpendicular distance to this side, which when multiplied with the respective delta dist will give us the euclidean distance, meaning the distance from the starting position until the next X position

    if (ray->dir_y < 0) //All applies to Y as well
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
}