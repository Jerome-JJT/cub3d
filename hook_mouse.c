/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaqueme <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:49:16 by jjaqueme          #+#    #+#             */
/*   Updated: 2022/04/26 18:17:15 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_click_interact(t_vars *vars, t_ray *cast);

int	ft_click_hook(int button, int x, int y, t_vars *vars)
{
	t_ray		*cast;
	t_wall		w;

	if (vars->game_state == 1 && button == M_CLK_L
		&& x >= 720 && x <= 770 && y >= 30 && y <= 80)
		vars->player.has_sound = !vars->player.has_sound;
	else if (vars->game_state == 2 && button == M_CLK_L)
	{
		cast = ft_cast_rays_inv(vars, (t_point){.x = vars->player.pos.x
				+ cos(vars->player.angle), .y = vars->player.pos.y
				+ sin(vars->player.angle)});
		if (cast != NULL)
		{
			w = vars->map.walls[cast->wall];
			if (ft_pyta(w.pos.y - vars->player.pos.y,
					w.pos.x - vars->player.pos.x) < 2.2)
				ft_click_interact(vars, cast);
			else
				vars->pistol.frame = 0;
			free(cast);
		}
		else
			vars->pistol.frame = 0;
	}
	return (0);
}

static void	ft_click_interact(t_vars *vars, t_ray *cast)
{
	t_wall	w;

	w = vars->map.walls[cast->wall];
	if (w.type == W_DOOR)
	{
		vars->map.walls[cast->wall].type = W_DOOR_OPEN;
		vars->map.raw[(int)w.pos.y][(int)w.pos.x] = '0';
		sound_music(vars, "door");
	}
	else if (w.type == W_DOOR_OPEN && ((int)vars->player.pos.x != (int)w.pos.x
			|| (int)vars->player.pos.y != (int)w.pos.y))
	{
		vars->map.walls[cast->wall].type = W_DOOR;
		vars->map.raw[(int)w.pos.y][(int)w.pos.x] = 'D';
		sound_music(vars, "door");
	}
	else if (w.type == W_FINISH)
	{
		ft_next_level(vars);
	}
	else
		vars->pistol.frame = 0;
}

void	ft_next_level(t_vars *vars)
{
	ft_free_map(vars);
	vars->level++;
	sound_kill();
	if (vars->level > 2 || vars->level < 0)
	{
		if (vars->level > 0)
			sound_music(vars, "victory");
		vars->game_state = 3;
		ft_tfree((void **)&vars->map.next);
	}
	else
	{
		sound_music(vars, "map_victory");
		vars->player.pos.x = 0;
		if (vars->map.next == NULL)
			vars->map.next = ft_itoa(rand());
		ft_open_map(vars, &vars->map.next);
		ft_process_map(vars);
		ft_register_walls(vars);
		play_sound(vars, vars->map.music);
	}
}

int	ft_mouse_hook(int x, int y, t_vars *vars)
{
	if (vars->game_state == 2)
	{
		vars->player.angle += radians(x - vars->screen.w / 2) / 10;
		if (vars->player.angle > M_PI)
			vars->player.angle -= 2 * M_PI;
		if (vars->player.angle < -M_PI)
			vars->player.angle += 2 * M_PI;
		vars->player.hori += (vars->screen.h / 2 - y) / 1;
		vars->player.hori = fmax(0, fmin(vars->screen.h, vars->player.hori));
		mlx_mouse_move(vars->win, vars->screen.w / 2, vars->screen.h / 2);
	}
	return (0);
}
