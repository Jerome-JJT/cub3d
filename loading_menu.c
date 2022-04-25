#include <cub3d.h>

void	load_pistol(t_vars *vars)
{
	ft_load_image(vars, "./assets/gun_1.xpm", &vars->pistol.pistol1);
	ft_load_image(vars, "./assets/gun_2.xpm", &vars->pistol.pistol2);
	ft_load_image(vars, "./assets/gun_3.xpm", &vars->pistol.pistol3);
	ft_load_image(vars, "./assets/gun_4.xpm", &vars->pistol.pistol4);
	ft_load_image(vars, "./assets/gun_5.xpm", &vars->pistol.pistol5);
	ft_load_image(vars, "./assets/heart_full.xpm", &vars->loading.heart);
	ft_load_image(vars, "./assets/heart_left.xpm", &vars->loading.heart_half);
}

void	menu_load_image(t_vars *vars)
{	
	ft_load_image(vars, "./assets/menu_1.xpm", &vars->loading.menu_1);
	ft_load_image(vars, "./assets/menu_2.xpm", &vars->loading.menu_2);
	ft_load_image(vars, "./assets/menu_3.xpm", &vars->loading.menu_3);
	ft_load_image(vars, "./assets/menu_4.xpm", &vars->loading.menu_4);
	ft_load_image(vars, "./assets/char_ghost.xpm", &vars->loading.ghost);
	ft_load_image(vars, "./assets/char_ninja.xpm", &vars->loading.ninja);
	ft_load_image(vars, "./assets/char_pirate.xpm", &vars->loading.pirate);
	ft_load_image(vars, "./assets/char_franken.xpm", &vars->loading.franken);
	ft_load_image(vars, "./assets/sound_on.xpm", &vars->loading.sound_on);
	ft_load_image(vars, "./assets/sound_off.xpm", &vars->loading.sound_off);
	load_pistol(vars);
}

void	set_char_stats(t_vars *vars)
{
	if (vars->loading.pos == 1)
		vars->player.has_collisions = 0;
	else if (vars->loading.pos == 2)
		vars->player.speed *= 2;
	else if (vars->loading.pos == 3)
		vars->player.fov = radians(170);
	else if (vars->loading.pos == 4)
		vars->player.hp = 2000;
}

#define LOADING_LEN 100
void	loading_screen(t_vars *vars)
{
	if (vars->frame % LOADING_LEN < ((LOADING_LEN / 6) * 1))
		ft_put_image_full(vars, &vars->loading.menu_1);
	else if (vars->frame % LOADING_LEN < ((LOADING_LEN / 6) * 2))
		ft_put_image_full(vars, &vars->loading.menu_2);
	else if (vars->frame % LOADING_LEN < ((LOADING_LEN / 6) * 3))
		ft_put_image_full(vars, &vars->loading.menu_3);
	else if (vars->frame % LOADING_LEN < ((LOADING_LEN / 6) * 4))
		ft_put_image_full(vars, &vars->loading.menu_4);
	else if (vars->frame % LOADING_LEN < ((LOADING_LEN / 6) * 5))
		ft_put_image_full(vars, &vars->loading.menu_3);
	else
		ft_put_image_full(vars, &vars->loading.menu_2);
}


void	menu_screen(t_vars *vars)
{
	if (vars->loading.pos == 1)
		ft_put_image_full(vars, &vars->loading.ghost);
	else if (vars->loading.pos == 2)
		ft_put_image_full(vars, &vars->loading.ninja);
	else if (vars->loading.pos == 3)
		ft_put_image_full(vars, &vars->loading.pirate);
	else if (vars->loading.pos == 4)
		ft_put_image_full(vars, &vars->loading.franken);

	if (vars->player.has_sound == 0 && vars->game_state == 1)
		ft_put_image(vars, &vars->loading.sound_off,
		(t_point){720, 30}, (t_point){770, 80});
	else if (vars->player.has_sound == 1 && vars->game_state == 1)
		ft_put_image(vars, &vars->loading.sound_on,
		(t_point){720, 30}, (t_point){770, 80});
}

