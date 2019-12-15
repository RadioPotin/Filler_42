/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 11:31:54 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 13:22:29 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		set_ids(t_filler *f, int fg)
{
	if (fg == 0)
	{
		f->my_id = 'O';
		f->his_id = 'X';
	}
	else
	{
		f->my_id = 'X';
		f->his_id = 'O';
	}
}

static int		set_player(char *player, t_filler *f)
{
	char	*ptr;

	ptr = ft_strrchr(player, '/');
	if (ft_strstr(player, P1ID))
	{
		if (ft_strcmp(ptr + 1, "dapinto.filler"))
			set_ids(f, 0);
	}
	else
	{
		if (ft_strcmp(ptr + 1, "dapinto.filler"))
			set_ids(f, 1);
	}
	return (0);
}

int				get_players(t_filler *f)
{
	if (get_next_line(STDIN_FILENO, &f->line) > 0)
	{
		if (ft_strstr(f->line, P1ID) || ft_strstr(f->line, P2ID))
		{
			set_player(f->line, f);
			ft_strdel(&f->line);
			return (1);
		}
		ft_strdel(&f->line);
	}
	return (-1);
}
