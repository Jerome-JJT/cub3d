#include <cub3d.h>

static void	ft_check_case(t_vars *vars, int x, int y, int *n_walls);
static void	ft_check_case_sides(t_vars *vars, int x, int y);

int	ft_count_walls(t_vars *vars)
{
	int	n_walls;
	int	i;
	int	j;

	n_walls = 0;
	i = 0;
	while (vars->map.raw[i] != NULL)
	{
		j = 0;
		while (vars->map.raw[i][j] != '\0')
		{
			ft_check_case(vars, j, i, &n_walls);
			j++;
		}
		i++;
	}
	return (n_walls);
}

static void	ft_check_case(t_vars *vars, int x, int y, int *n_walls)
{
	if (vars->map.raw[y][x] == '0')
	{
		ft_check_case_sides(vars, x, y);
		if (ft_strchr("1", ft_get_case(vars, x, y - 1)) != NULL)
			(*n_walls)++;
		if (ft_strchr("1", ft_get_case(vars, x, y + 1)) != NULL)
			(*n_walls)++;
		if (ft_strchr("1", ft_get_case(vars, x - 1, y)) != NULL)
			(*n_walls)++;
		if (ft_strchr("1", ft_get_case(vars, x + 1, y)) != NULL)
			(*n_walls)++;
	}
}

static void	ft_check_case_sides(t_vars *vars, int x, int y)
{
	if (y <= 0 || vars->map.raw[y - 1][x] == ' ')
		ft_exit(vars, "Error map borders");
	else if (vars->map.raw[y + 1] == NULL || vars->map.raw[y + 1][x] == ' ')
		ft_exit(vars, "Error map borders");
	else if (x <= 0 || vars->map.raw[y][x - 1] == ' ')
		ft_exit(vars, "Error map borders");
	else if (vars->map.raw[y][x + 1] == '\0' || vars->map.raw[y][x + 1] == ' ')
		ft_exit(vars, "Error map borders");
}
