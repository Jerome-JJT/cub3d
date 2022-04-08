#include <cub3d.h>

void	ft_clear_walls(t_vars *vars);


int	ft_loop_hook(t_vars *vars)
{
//	ft_draw_background(vars);

	ft_clear_walls(vars);
	ft_draw_walls(vars);


//	char	*time = ft_itoa(ft_time());

//	ft_write_text(vars, time, (t_point){.x = 50, .y = 100}, n_vect(10, ft_color(0, 255, 0, 0)));
//	free(time);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->background.img, 0, vars->player.hori - vars->screen.h);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->screen.img, 0, 0);
	minimap(vars);
	return (0);
}

int	ft_key_hook(int keycode, t_vars *vars)
{
	float	step = 0.1;


	printf("KEY %d\n", keycode);
	if (keycode == K_ESCAPE)
		ft_free(vars);
	else
		ft_move(vars, keycode, step);
	return (0);
}

int	ft_click_hook(int button, int x, int y, t_vars *vars)
{
	printf("CLICK %d %d %d\n", x, y, button);
	(void)vars;
	return (0);
}

int	ft_mouse_hook(int x, int y, t_vars *vars)
{
//	if (x < 0 || y < 0 || x >= vars->screen.w || y >= vars->screen.h)
//		return (0);
//	printf("MOVE %d %d\n", x, y);
	(void)vars;
	(void)x;
	(void)y;
	return (0);
}
