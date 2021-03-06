/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:16:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/10 04:08:04 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <math.h>
# include "../libft-42/libft.h"
# include "../minilibx/mlx.h"
# include "./get_next_line.h"
# define UDIV 1
# define VDUV 1
# define VMOVE 0.0
# define TEXWIDTH 512
# define TEXHEIGHT 512

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
	char		*previousline;
	char		*currentline;
	int			ir;
	int			in;
	int			iso;
	int			ie;
	int			iw;
	int			is;
	int			inf;
	int			ic;
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
	int			texxs_walltwo;
	double		steps_walltwo;
	double		texposs_walltwo;
	t_img		s_wallthree;
	t_img		s_wallfour;
	int			texxs_wallfour;
	double		steps_wallfour;
	double		texposs_wallfour;
	t_img		s_floorfour;
	t_img		s_lava;
	int			texxs_lava;
	double		steps_lava;
	double		texposs_lava;
	t_img		s_roofeleven;
	t_img		s_escalier;
	t_img		s_fl;
	int			texxs_fl;
	double		steps_fl;
	double		texposs_fl;
	t_img		s_arrowtex;
	int			texxs_arrowtex;
	double		steps_arrowtex;
	double		texposs_arrowtex;
	t_img		s_arrowtexl;
	int			texxs_arrowtexl;
	double		steps_arrowtexl;
	double		texposs_arrowtexl;
	t_img		s_lifeframe;
	int			texxs_lifeframe;
	double		steps_lifeframe;
	double		texposs_lifeframe;
	t_img		s_health;
	int			texxs_health;
	double		steps_health;
	double		texposs_health;
	t_img		s_monster;
	t_square	square;
	int			resph;
	t_sprite	*sprite;
	double		*zbuffer;
	int			*spriteorder;
	double		*spritedistance;
	int			numesprite;
	int			biggest;
	int			playercount;
	float		floorx;
	float		floory;
	float		cellx;
	float		celly;
	float		floorstepx;
	float		floorstepy;
	float		raydirxone;
	float		raydiryo;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	char		what;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	double		spritex;
	double		spritey;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	int			stripe;
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
t_mlx_data		ft_set_mlx_data(char **map, t_data *data, t_sort *sort,
	t_player *player);
void			ft_putvalues(char *desc, int value);
void			ft_debug_sort(t_sort *sort);
int				strlennspace(char *str);
int				ft_whitespace(char c);
void			ft_setplayer(double x, double y, t_mlx_data *data);
int				get_click(int buton, int x, int y, t_mlx_data *data);
void			ft_setimg(t_mlx_data *data);
void			ft_swap(int *a, int *b);
void			sortsprite(int *spriteorder, double *spritedistance,
							int numsprite);
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
void			ft_checkw(char *currentline, t_sort *sort);
char			*ft_testsrc(char *src);
void			ft_checkmap(t_mlx_data *data);
int				ft_askloading(char *txt);
void			ft_checksprite(char *currentline, t_sort *sort);
void			ft_getpath(char *currentline, t_sort *sort, int wich);
void			ft_check_types(char *currentline, t_sort *sort, int ret);
void			check_line_start(char **currentline, int ret);
void			ft_joinmap(t_sort *sort);
void			ft_load_normalsprite(t_mlx_data *data);
void			ft_askloading2(t_sort *sort);
void			ft_cub_getdata_img(t_mlx_data *data);
int				ft_loadmlx(t_mlx_data *data);
int				ft_sort_and_rend(int fd, t_sort *sort);
char			*ft_compressmap(int fd, t_sort *sort);
void			ft_checkmapborder(t_mlx_data *data);
void			ft_mlx_vertline(t_mlx_data *data, int color, t_pos *pos,
								int len);
void			ft_raycast(t_mlx_data *data);
void			ft_mlx_show_minimap(t_mlx_data *mlxdata, t_sort *sort);
void			ft_encodemap(t_sort *sort);
void			ft_getline_checktype(t_sort *sort, int ret);
void			ft_get_color_tex(t_mlx_data *data, int x, int y);
void			ft_distpoint(t_mlx_data *data, float raydirxo, int x, int y);
void			ft_floorcasting(t_mlx_data *data);
void			ft_dda(t_mlx_data *data);
void			ft_walldetection(t_mlx_data *data, int *side, int *hit);
void			ft_setcamerainfo(t_mlx_data *data, int x);
void			ft_getlinenwallx(t_mlx_data *data);
void			ft_setcamerainfo(t_mlx_data *data, int x);
void			ft_init_texx(t_mlx_data *data);
void			ft_get_texposray(t_mlx_data *data);
void			ft_reset_poss(t_mlx_data *data);
int				ft_fourtexcube(t_mlx_data *data);
int				ft_set_texture(t_mlx_data *data);
void			ft_putwall_pixel(t_mlx_data *data, int x);
void			ft_wallcasting(t_mlx_data *data);
void			ft_loadnsort_sprites(t_mlx_data *data);
void			ft_init_sprite(t_mlx_data *data, int i);
void			ft_getsprite_color(t_mlx_data *data, int i, int y, int texx);
t_mlx_data		ft_set_mlx_datathree(void);
int				ft_do_ninetext(t_mlx_data *data);
int				ft_do_ninetexttwo(t_mlx_data *data);
char			*ft_str_spacetoone(char *str);
void			ft_check_end_r(char *currentline);
void			ft_wrongline(char *currentline);
void			ft_init_instructions(t_sort *sort);
void			ft_path_selector(int wich, t_sort *sort, char *currentline);
void			ft_check_double(t_sort *sort);
#endif
