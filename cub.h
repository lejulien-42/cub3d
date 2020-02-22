/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:16:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/23 00:28:15 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <mlx.h>
# define UDIV 1
# define VDUV 1
# define VMOVE 0.0

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_bmp
{
	int			file_size;
	int			pixels_address;
	int			header_size;
	int			clear_planes;
	int			bpp;
	int			raw_size;
	int			res;
}				t_bmp;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_data;

typedef struct	s_player
{
	int			x;
	int			y;
	int			o;
}				t_player;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_square
{
	t_pos		pos;
	int			w;
	int			h;
}				t_square;

typedef struct	s_sort
{
	int			issave;
	char		*northpath;
	char		*southpath;
	char		*eastpath;
	char		*westpath;
	int			resw;
	int			resh;
	char		*sprite;
	int			rgbf;
	int			rgbc;
	int			mapwidth;
	int			mapheight;
	int			isbonus;
}				t_sort;

typedef struct	s_mlx_data
{
	char		**map;
	t_data		*data;
	t_sort		*sort;
	t_player	*player;
	int			up;
	int			down;
	int			left;
	int			right;
	int			s;
	int			key_left;
	int			key_right;
	int			key_up;
	int			key_down;
	int			esc;
	int			r;
	int			isdead;
	int			shift;
	int			mkey;
	int			spritenumber;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	int			health;
	int			stamina;
	int			hasstamina;
	int			showbonus;
	double		movespeed;
	int			ord;
	double		time;
	double		oldtime;
	double		planex;
	double		planey;
	int			promton;
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
	t_square	square;
	int			resph;
	t_sprite	*sprite;
	double		*zbuffer;
	int			*spriteorder;
	double		*spritedistance;
	int			numesprite;
}				t_mlx_data;

void			ft_mlx_draw_square(t_square *square, t_data *data, int color);
void			ft_mlx_drawfilled_square(t_square *square, int color,
											t_mlx_data *mlxdata);
t_square		ft_set_square(int w, int h, int x, int y);
int				rgb_int(int red, int green, int blue);
void			ft_vertline(t_mlx_data *data, int color, t_pos *pos,
											t_pos *postwo);
int				img_to_bmp(t_mlx_data *data);
void			ft_puterror(char *text);
t_sort			ft_initialaze_sort(void);
int				ft_attrib_sprite(t_mlx_data *data);
int				rgb_int(int red, int green, int blue);
int				ft_count_sprite(t_mlx_data *date);
void			ft_putchardesc(char *desc, char *str);
char			*ft_subspace(char *str);
int				closeit(void *param);
t_pos			ft_setpoint(int x, int y);
int				key_press(int key, t_mlx_data *data);
int				key_release(int key, t_mlx_data *data);
void			screenshot(t_mlx_data *data);
int				draw(t_mlx_data *data);
t_mlx_data		ft_set_mlx_data(char **map, t_data *data, t_sort *sort, t_player *player);
void			ft_putvalues(char *desc, int value);
void			ft_debug_sort(t_sort *sort);
int				strlennspace(char *str);
int				ft_whitespace(char c);
void			ft_setplayer(double x, double y, t_mlx_data *data);
int				get_click(int buton, int x, int y, t_mlx_data *data);
void			ft_setimg(t_mlx_data *data);
void			ft_swap(int *a, int *b);
void			sortsprite(int *spriteorder, double *spritedistance, int numsprite);
void			ft_do_mlx(t_mlx_data *data);
int				ft_die(t_mlx_data *data);
int				ft_lifecheck(t_mlx_data *data);
void			ft_spookia(t_mlx_data *data);
void			ft_setplayerdir(t_mlx_data *data, int dir);
void			ft_sprint(t_mlx_data *data);
void			ft_key_event(t_mlx_data *data);
void			ft_keyr(t_mlx_data *data);
void			ft_keyl(t_mlx_data *data);
void			ft_teleport(t_mlx_data *data);
void			ft_moveleftx(t_mlx_data *data);
void			ft_movelefty(t_mlx_data *data);
void			ft_moverightx(t_mlx_data *data);
void			ft_moverighty(t_mlx_data *data);
void			ft_movedowny(t_mlx_data *data);
void			ft_handlemove(t_mlx_data *data);
void			ft_keybr_event(t_mlx_data *data);
void			ft_debugmap(char **map);
void			ft_show_enemypos(t_mlx_data *data, int resph);
void			ft_putsquare(int i, int j, t_mlx_data *data);
void			ft_showposes(t_mlx_data *data);
void			ft_checkr(char *currentline, t_sort *sort);
void			ft_checkb(char *currentline, t_sort *sort);
void			ft_checkn(char *currentline, t_sort *sort);
void			ft_checks(char *currentline, t_sort *sort);
void			ft_checke(char *currentline, t_sort *sort);
void			ft_checkc(char *currentline, t_sort *sort);
void			ft_checkf(char *currentline, t_sort *sort);
char			*ft_testsrc(char *src);
#endif
