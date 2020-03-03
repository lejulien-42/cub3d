/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loadimg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 05:24:58 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/03 09:41:14 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_load_normalsprite2(t_mlx_data *data)
{
	data->s_escalier.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/hadhio.xpm", &data->s_escalier.width,
		&data->s_escalier.height);
	data->s_fl.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/spookyfl.xpm", &data->s_fl.width, &data->s_fl.height);
	data->s_floorfour.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/FLOOR_04.xpm", &data->s_floorfour.width,
		&data->s_floorfour.height);
	data->s_roofeleven.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/ROOF_11.xpm", &data->s_roofeleven.width,
		&data->s_roofeleven.height);
	data->s_arrowtex.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/right.xpm", &data->s_arrowtex.width,
		&data->s_arrowtex.height);
	data->s_arrowtexl.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/left.xpm", &data->s_arrowtexl.width,
		&data->s_arrowtexl.height);
	data->s_lifeframe.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/frame.xpm", &data->s_lifeframe.width,
		&data->s_lifeframe.height);
}

void
	ft_load_normalsprite(t_mlx_data *data)
{
	data->img.img_ptr = mlx_new_image(data->data->mlx_win,
		data->sort->resw, data->sort->resh);
	data->s_walltwo.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		ft_testsrc(data->sort->northpath), &data->s_walltwo.width,
		&data->s_walltwo.height);
	data->s_wallfour.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		ft_testsrc(data->sort->southpath), &data->s_wallfour.width,
		&data->s_wallfour.height);
	data->s_lava.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		ft_testsrc(data->sort->eastpath), &data->s_lava.width,
		&data->s_lava.height);
	data->s_health.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		ft_testsrc(data->sort->westpath), &data->s_health.width,
		&data->s_health.height);
	data->s_monster.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		ft_testsrc(data->sort->sprite), &data->s_monster.width,
		&data->s_monster.height);
	data->s_wall.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/WALL_01.xpm", &data->s_wall.width, &data->s_wall.height);
	data->s_wallthree.img_ptr = mlx_xpm_file_to_image(data->data->mlx_ptr,
		"./textures/WALL_03.xpm", &data->s_wallthree.width,
		&data->s_wallthree.height);
	ft_load_normalsprite2(data);
}

static void
	ft_askloading3(t_sort *sort)
{
	if (!sort->eastpath)
	{
		if (ft_askloading("Missing east texture load ? [y|n]\n") == 1)
			sort->eastpath = "./textures/Error.xpm";
		else
			ft_puterror("Error missing testure\n");
	}
	if (!sort->westpath)
	{
		if (ft_askloading("Missing west texture load ? [y|n]\n") == 1)
			sort->westpath = "./textures/Error.xpm";
		else
			ft_puterror("Error missing texture\n");
	}
}

void
	ft_askloading2(t_sort *sort)
{
	if (!sort->sprite)
	{
		if (ft_askloading("Missing sprite texture load ? [y|n]\n") == 1)
			sort->sprite = "./textures/Error.xpm";
		else
			ft_puterror("Error missing texture\n");
	}
	if (!sort->northpath)
	{
		if (ft_askloading("Missing north texture load ? [y|n]\n") == 1)
			sort->northpath = "./textures/Error.xpm";
		else
			ft_puterror("Error missing texture\n");
	}
	if (!sort->southpath)
	{
		if (ft_askloading("Missing south texture load ? [y|n]\n") == 1)
			sort->southpath = "./textures/Error.xpm";
		else
			ft_puterror("Error missing texture\n");
	}
	ft_askloading3(sort);
}
