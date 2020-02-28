/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:44:56 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 21:55:13 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void
	bh_init(t_bmp *bh, int size)
{
	bh->file_size = size + 54;
	bh->pixels_address = 54;
	bh->header_size = 40;
	bh->clear_planes = 1;
	bh->raw_size = size;
	bh->res = 2835;
}

static void
	write_bmp_header(char *header, t_mlx_data *data, int size)
{
	t_bmp bh;

	bh_init(&bh, size);
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	ft_memcpy(&header[2], &(bh.file_size), sizeof(int));
	ft_memcpy(&header[10], &(bh.pixels_address), sizeof(int));
	ft_memcpy(&header[14], &(bh.header_size), sizeof(int));
	ft_memcpy(&header[18], &(data->sort->resw), sizeof(int));
	ft_memcpy(&header[22], &(data->sort->resh), sizeof(int));
	ft_memcpy(&header[26], &(bh.clear_planes), sizeof(short));
	ft_memcpy(&header[28], &(data->img.bpp), sizeof(short));
	ft_memcpy(&header[34], &(bh.raw_size), sizeof(int));
	ft_memcpy(&header[38], &(bh.res), sizeof(int));
	ft_memcpy(&header[42], &(bh.res), sizeof(int));
}

static int
	get_color(t_mlx_data *data, int x, int y)
{
	return (data->img.data[y * data->sort->resw + x]);
}

static char
	*write_pixel(t_mlx_data *data, int size)
{
	int *pixels;
	int y;
	int x;
	int c;
	int pix;

	if (!(pixels = malloc(sizeof(int) * size)))
		return (NULL);
	ft_bzero(pixels, size);
	y = 0;
	while (y < data->sort->resh)
	{
		x = 0;
		while (x < data->sort->resw)
		{
			pix = (data->sort->resh - 1 - y) * data->img.size_l / 4 + x;
			c = get_color(data, x, y);
			pixels[pix] = c;
			x++;
		}
		y++;
	}
	return ((char *)pixels);
}

int
	img_to_bmp(t_mlx_data *data)
{
	int		fd;
	int		size;
	char	header[54];
	char	*pixeldata;

	fd = open("screenshot.bmp", O_RDWR | O_CREAT, 77777);
	if (fd != -1)
	{
		size = (data->sort->resw * data->sort->resh * 4);
		write_bmp_header(header, data, size);
		pixeldata = write_pixel(data, size);
		if (pixeldata != NULL)
		{
			write(fd, header, 54);
			write(fd, pixeldata, size);
			free(pixeldata);
		}
	}
	return (1);
}
