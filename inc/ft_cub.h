/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleilani <hleilani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:01:11 by hleilani          #+#    #+#             */
/*   Updated: 2020/12/01 17:00:08 by hleilani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB_H
# define FT_CUB_H

# include <fcntl.h>
# include "../mlx/mlx.h"
# include <math.h>
# include "libft.h"
# include <stdio.h>
# include <time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netdb.h>

# define SA struct sockaddr
# define SI struct sockaddr_in

typedef struct	s_raycast{
	int			drmax;
	int			drmin;
	int			x;
	float		rdx;
	float		rdy;
	int			mx;
	int			my;
	float		deltadisty;
	float		deltadistx;
	float		pwl;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	float		sidedistx;
	float		sidedisty;
	int			texi;
}				t_raycast;

typedef	struct	s_texture
{
	void		*img;
	void		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
	int			texx;
	int			texy;
	float		wallx;
	float		step;
	float		texpos;
	char		*texfilename;
	int			valide;
}				t_texture;

typedef struct	s_sprite
{
	int			ishp;
	int			unicid;
	float		x;
	float		y;
	float		dist;
	int			seepl;
	int			shootcd;
	int			spritestate;
	int			alive;
	int			deadsended;
	int			angle;
	t_texture	tex;
	t_raycast	r;
	int			cantshoot;
	int			candie;
}				t_sprite;

typedef struct	s_pl {
	int			score;
	float		psx;
	float		psy;
	float		rdx;
	float		rdy;
	float		dy;
	float		dx;
	double		dvy;
	float		camerax;
	float		planex;
	float		planey;
	int			health;
	int			shootcd;
	int			angle;
}				t_pl;

typedef struct	s_draw {
	int			x;
	int			drawstart;
	int			drawend;
	int			color;
	int			lineheight;
	int			drstt;
}				t_draw;

typedef struct	s_floor
{
	float		rdx0;
	float		rdy0;
	float		rdx1;
	float		rdy1;
	int			p;
	float		pz;
	float		rd;
	float		fstx;
	float		fsty;
	float		fx;
	float		fy;
	int			cx;
	int			cy;
	float		ty;
	int			color;
}				t_floor;

typedef struct	s_huddraw
{
	float		x;
	float		step;
	int			color;
	float		tx;
	float		ty;
	int			xstart;
	int			xend;
	float		ystart;
	int			yend;
}				t_huddraw;

typedef struct	s_control
{
	int			side_pressed[4];
	int			rotatex;
	int			rotatey;
	int			lastx;
	int			lasty;
	int			firsty;
	int			usedy;
}				t_control;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	unsigned	floor;
	unsigned	cell;
}				t_data;

typedef struct	s_hud
{
	int			texid;
	float		x;
	float		y;
	float		percent;
	int			dontdraw;
}				t_hud;

typedef struct	s_sprtedraw
{
	int		i;
	float	spx;
	float	spy;
	float	tsx;
	float	tsy;
	int		scx;
	int		sch;
	int		dwy;
	int		dwey;
	int		sw;
	int		dwsx;
	int		dwex;
	int		x;
}				t_sprtedraw;

typedef struct	s_all
{
	int			screen;
	t_sprtedraw	s;
	int			nextlvltriger;
	int			ismultiplayer;
	int			calc;
	float		*distbuff;
	size_t		resolution_width;
	size_t		resolution_height;
	size_t		resolution_scalepixel;
	int			maxresy;
	int			maxresx;
	size_t		mapheight;
	size_t		mapwidth;
	char		**map;
	t_data		data;
	int			h;
	int			w;
	t_floor		fl;
	t_control	ctrl;
	t_pl		pl;
	t_raycast	r;
	t_raycast	pr;
	t_draw		dpr;
	t_draw		dr;
	t_texture	tex[60];
	t_texture	ct;
	t_sprite	*sprites;
	t_hud		hudpart[4];
	t_hud		score[10];
	t_huddraw	hdr;
	int			numsprites;
	int			calculating;
	char		*nextmap;
	time_t		prev;
	int			sockfd;
	SI			sock;
	t_sprite	mp;
	int			enemydied;
	int			port;
	int			sended;
	int			alivesended;
	char		*ip;
	int			healtheated;
	int			lasthealtheatedx;
	int			lasthealtheatedy;
}				t_all;

int				get_next_line(int fd, char **l);
int				get_map(t_all *all, char *map);
void			verline(t_all *a, int x);
void			castraycasts(t_all *a);
int				key_hook(int keycode, t_all *a);
int				unkey_hook(int keycode, t_all *a);
int				ft_inserttextdata(t_all *a);
void			ft_throwerror(char *message);
void			ft_fillpngdraw(t_all *a);
int				ft_parse_texture(t_all *a, char *l);
int				parse_resolution(t_all *all, char *line);
int				ft_parse_color(char *l, t_all *all);
void			find_maxwidthmap(t_all *all);
int				is_map(char *line);
void			parse_final_map(t_all *all);
int				is_part_ofmap(char c);
int				ft_is_map(char c);
int				hook(t_all *a);
void			ft_getdataaddr(t_all *a);
unsigned		ft_getcolor(int ty, t_texture t);
void			ft_putpixel(float x, float y, t_all *a, int color);
void			processmoblogic(t_all *a);
int				mouseclickhook(int but, int x, int y, t_all *a);
void			checkwhocandie(t_all *a);
void			drawhud(t_all *a);
void			getnextlevel(t_all *a, int send);
void			createserver(t_all *a);
void			connectserver(t_all *a);
void			sendpacket(t_all *a);
void			postmultiplayer(t_all *a);
void			recievepacket(t_all *a);
void			gethp(t_all *a);
void			killhealth(t_all *a, int x, int y);
int				check(void);
void			set_default(t_all *a);
void			ft_throwerror(char *message);
void			ft_movechar(t_all *a, int keycode, float ms);
void			checkmoveside(t_all *a, float ms, float mult);
void			checkmoveface(t_all *a, float ms, float mult);
void			settexture(t_all *a);
void			checkwhocandie(t_all *a);
void			checkplhp(t_all *a);
void			ft_fillmap(t_all *all, char *line, int fd);
void			intializehud(t_all *a);
void			checkcooldown(t_all *a, int i);
int				ft_parse_texture(t_all *a, char *l);
void			setupspritecycle(t_all *a, t_sprite sprite);
void			spritecyclesec(t_all *a, int i);
void			drawspritecycle(t_all *a, int i);
void			calculatesprites(t_all *a);
int				throwspriteraycast(t_all *a, t_sprite *spr);
void			ft_setdefault(t_all *a, int x);
void			ft_intializedirview(t_all *a);
void			ft_findrange(t_all *a);
void			ft_fill_drawparametrs(t_all *a);
void			sortsprites(t_all *a);
void			updatedefaulttextures(t_all *a);
void			takescreenshot(t_all *a);
void			playsound(t_all *a, char *command);

#endif
