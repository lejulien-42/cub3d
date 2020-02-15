/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:16:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/14 23:59:54 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <mlx.h>
# define uDiv 1
# define vDiv 1
# define vMove 0.0

typedef struct			s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}						t_img;

typedef struct          s_bmp
{
    int     file_size;
    int     pixels_address;
    int     header_size;
    int     clear_planes;
    int     bpp;
    int     raw_size;
    int     res;
}                       t_bmp;

typedef struct			s_sprite
{
	double	x;
	double	y;
	int		texture;
}						t_sprite;

typedef struct          data_s
{
        void                    *mlx_ptr;
        void                    *mlx_win;
}                                       data_t;

typedef struct          player_s
{
        int                             x;
        int                             y;
        int                             o;
}                                       player_t;

typedef struct          pos_s
{
        int                             x;
        int                             y;
}                                       pos_t;

typedef struct          square_s
{
        pos_t                   pos;
        int                             w;
        int                             h;
}                                       square_t;

typedef struct	sort_s
{
	int		issave;
	char	*northpath;
	char	*southpath;
	char	*eastpath;
	char	*westpath;
	int		resw;
	int		resh;
	char	*sprite;
	int		rgbf;
	int		rgbc;
	int		mapwidth;
	int		mapheight;
}				sort_t;

typedef struct  mlx_data_s
{
    char        **map;
    data_t      *data;
    sort_t      *sort;
    player_t    *player;
    int         up;
    int         down;
    int         left;
    int         right;
	int			key_left;
	int			key_right;
	int			key_up;
	int			key_down;
    int         esc;
    int         r;
    int         shift;
    int         mkey;
    int         spritenumber;
    double      posx;
    double      posy;
    double      dirx;
    double      diry;
    int         health;
	int			stamina;
	int			hasstamina;
    int         showbonus;
    double      time;
    double      oldtime;
    double      planeX;
    double      planeY;
    int         promton;
	t_img		img;
	t_img		s_wall;
	t_img		s_walltwo;
	t_img		s_wallthree;
	t_img		s_wallfour;
	t_img		s_floorfour;
	t_img		s_lava;
	t_img		s_roofeleven;
	t_img		s_escalier;
	t_img		s_fl;
	t_img		s_arrowtex;
	t_img		s_arrowtexl;
	t_img		s_lifeframe;
	t_img		s_health;
	t_img		s_monster;
    int         numSprite;
    t_sprite    *sprite;
    double      *zBuffer;
    int         *spriteOrder;
    double      *spriteDistance;
    int         numsprite;
}               mlx_data_t;

void		ft_mlx_draw_square(square_t *square, data_t *data, int color);
void		ft_mlx_drawfilled_square(square_t *square, int color, mlx_data_t *mlxData);
square_t	ft_set_square(int w, int h, int x, int y);
int			rgb_int(int red, int green, int blue);
void	    ft_vertline(mlx_data_t *data, int color, pos_t *pos, pos_t *postwo);
int         img_to_bmp(mlx_data_t * data);
#endif
