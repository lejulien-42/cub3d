/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_askloading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 23:00:43 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/10 04:16:35 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int
	ft_askloading(char *txt)
{
	char	*line;
	int		ret;

	line = NULL;
	ft_putstr_fd("\e[39m", 1);
	ft_putstr_fd(txt, 1);
	ft_putstr_fd("\e[33mcub\e[36m3D \e[96m>> \e[95m", 1);
	while ((ret = get_next_line(0, &line)) == 1)
	{
		if (line[0] == 'y' && line[1] == '\0')
		{
			free(line);
			return (1);
		}
		else if (line[0] == 'n' && line[1] == '\0')
		{
			free(line);
			return (0);
		}
		ft_putstr_fd("\e[91mPlease answer y or n :", 1);
		free(line);
		ft_putstr_fd("\n\e[33mcub\e[36m3D \e[96m>> \e[95m", 1);
	}
	ft_puterror("\nError texture file missing");
	return (0);
}

static void
	ft_init_mlxdata(t_data *data)
{
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
}

int
	ft_sort_and_rend(int fd, t_sort *sort)
{
	char		*compressedmap;
	t_data		data;
	t_mlx_data	mlx_data;
	t_player	player;
	char		**map;

	compressedmap = ft_compressmap(fd, sort);
	map = ft_split(compressedmap, '~');
	free(compressedmap);
	ft_init_mlxdata(&data);
	mlx_data = ft_set_mlx_data(map, &data, sort, &player);
	ft_checkmap(&mlx_data);
	if (!(ft_count_sprite(&mlx_data)))
		return (EXIT_FAILURE);
	if (!(ft_attrib_sprite(&mlx_data)))
		return (EXIT_FAILURE);
	if (sort->isbonus)
		ft_debugmap(map);
	ft_check_double(sort);
	ft_loadmlx(&mlx_data);
	return (1);
}
