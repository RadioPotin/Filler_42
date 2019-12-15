/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_info_fetcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:57:04 by dapinto           #+#    #+#             */
/*   Updated: 2019/06/14 10:23:35 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		extract_piece_size(t_filler *f, char *piecesizeline)
{
	char	*ptr;

	ptr = ft_strchr(piecesizeline, ' ') + 1;
	if (ptr)
		f->p.hei = ft_atoi(ptr);
	ptr = ft_strchr(ptr, ' ') + 1;
	if (ptr)
		f->p.wid = ft_atoi(ptr);
	if (f->p.hei <= 0 || f->p.wid <= 0)
		return (-1);
	return (0);
}

int				get_piece_size(t_filler *f)
{
	while (get_next_line(STDIN_FILENO, &f->line) > 0)
	{
		if (!ft_strstr(f->line, "Piece")
				|| ft_str_nb_of_target(f->line, " ") != 2)
		{
			ft_strdel(&f->line);
			return (-1);
		}
		else
		{
			if (extract_piece_size(f, f->line) < 0)
			{
				ft_strdel(&f->line);
				return (-1);
			}
			ft_strdel(&f->line);
			return (0);
		}
		ft_strdel(&f->line);
	}
	return (-1);
}
