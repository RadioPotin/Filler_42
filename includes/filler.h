/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:09:46 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 13:21:19 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include "ft_printf.h"
# define P1ID "$$$ exec p1 : "
# define P2ID "$$$ exec p2 : "
# define MYHEAT -1
# define ENNEMYHEAT -2

typedef struct	s_anchor
{
	int		px;
	int		py;
	int		heat;
	int		star;
}				t_anchor;

typedef struct	s_piece
{
	int			wid;
	int			hei;
	int			stars;
	int			pj;
	int			pi;
	int			**relat_coor;
	t_anchor	anchor;
	t_anchor	tmpsave;
}				t_piece;

typedef struct	s_filler
{
	int			**heatmap;
	char		**piece;
	char		**map;
	char		*line;
	int			wmap;
	int			hmap;
	char		my_id;
	char		his_id;
	int			mapy;
	int			mapx;
	int			final_y;
	int			final_x;
	t_piece		p;
}				t_filler;

int				get_players(t_filler *f);
int				get_map_size(t_filler *f);
int				check_and_store_map(t_filler *f);
int				get_piece_size(t_filler *f);
int				check_and_store_piece(t_filler *f);
int				free_filler(t_filler *f);
int				make_heatmap(t_filler *f);
int				solver(t_filler *f);
void			set_init_anchors(t_filler *f, int turn);
void			print_turn_data(t_filler f, int flag);
#endif
