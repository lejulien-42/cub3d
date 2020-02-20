/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 07:39:14 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/20 07:55:09 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	sortsprite(int *spriteorder, double *spritedistance, int numsprite)
{
	int temp;
	int i;

	temp = numsprite;
	while (temp > 0)
	{
		i = 0;
		while (i < temp - 1)
		{
			if (spritedistance[spriteorder[i]]
				< spritedistance[spriteorder[i + 1]])
				ft_swap(&spriteorder[i], &spriteorder[i + 1]);
			i++;
		}
		temp--;
	}
}

void
	screenshot(t_mlx_data *data)
{
   if (data->sort->issave == 1)
   {
		ft_putstr_fd("\e[31mProcessing screenshot ...\n", 1);
		img_to_bmp(data);
		ft_putstr_fd("\e[32mScreenshot : done :)\n", 1);
		exit (0);
   }
   data->sort->issave = 2;
}

void
	ft_do_mlx(t_mlx_data *data)
{
	mlx_hook(data->data->mlx_win, 17, 0L, closeit, NULL);
	mlx_hook(data->data->mlx_win, 2, 1L<<0, key_press, data);
	mlx_key_hook(data->data->mlx_win, key_release, data);
	mlx_loop_hook(data->data->mlx_ptr, draw, data);
	mlx_loop(data->data->mlx_ptr);
}