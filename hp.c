/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaqueme <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:49:16 by jjaqueme          #+#    #+#             */
/*   Updated: 2022/04/26 18:31:14 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_fire(t_vars *vars);

void	ft_damage(t_vars *vars)
{
	if (vars->map.raw != NULL
		&& ft_get_case(vars, vars->player.pos.x, vars->player.pos.y) == '^')
		vars->player.on_fire++;
	if (vars->player.on_fire > 0)
	{
		vars->player.hp = fmax(vars->player.hp - 1, -1);
		if ((int)vars->player.hp % 40 == 0)
			sound_music(vars, "hurt");
		if (vars->map.raw != NULL
			&& ft_get_case(vars, vars->player.pos.x, vars->player.pos.y) != '^')
			vars->player.on_fire = fmax(vars->player.on_fire - 2, 0);
		else if (vars->map.raw == NULL)
			vars->player.on_fire = fmax(vars->player.on_fire - 0.5, 0);
	}
	if (vars->player.hp == 0)
	{
		sound_music(vars, "wilheim");
		vars->player.hp = -1;
		vars->level = -5;
		vars->game_state = 3;
		ft_next_level(vars);
	}
	ft_fire(vars);
}

static void	ft_fire(t_vars *vars)
{
	if (vars->player.on_fire > 0)
	{
		ft_put_image(vars, &vars->fire[(int)(vars->frame / 6) % 10],
			(t_point){0, vars->screen.h * 0.5},
			(t_point){vars->screen.w, vars->screen.h * 1.2});
	}
}

void	ft_hp_draw(t_vars *vars)
{
	int		i;
	t_point	start;
	int		nb_hearts;

	nb_hearts = floor(vars->player.hp_start / 200);
	if (vars->player.hp > 0)
	{
		start.x = vars->screen.w / 2 - (40 * nb_hearts / 2);
		start.y = vars->screen.h - 50;
		i = 0;
		while (i < nb_hearts)
		{
			if (vars->player.hp / vars->player.hp_start
				> (1.0 / (nb_hearts * 2.0)) * (i * 2.0 + 1))
				ft_put_image(vars, &vars->heart, start,
					(t_point){start.x + 40, start.y + 37});
			else if (vars->player.hp / vars->player.hp_start
				> (1.0 / (nb_hearts * 2.0)) * (i * 2.0))
				ft_put_image(vars, &vars->heart_half, start,
					(t_point){start.x + 20, start.y + 37});
			start.x += 40;
			i++;
		}
	}
}
