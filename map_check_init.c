/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:33:04 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/18 13:27:50 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		make_map(t_filler *f, int i)
{
	if (i == 0)
	{
		if (!(f->map = malloc(sizeof(char *) * f->hmap + 1)))
			return (-1);
		f->map[f->hmap] = NULL;
	}
	else if (!(f->map[i - 1] = ft_strsub(f->line, 4, f->wmap)))
		return (-1);
	return (0);
}

static int		verify_map_body(t_filler *f, int i)
{
	char	*ptr;
	int		j;

	j = 0;
	ptr = f->line;
	if (ft_nchrchck(f->line, " .0123456789oOxX", f->wmap + 4) != -1
			&& ft_strlen(f->line) == (size_t)f->wmap + 4)
	{
		if (ft_isdigit(ptr[j]))
		{
			if (ft_atoi(&ptr[j]) == i - 1 && ptr[j + 3] == ' ')
				j += 4;
			else
				return (-1);
			if (ft_nchrchck(&ptr[j], ".oOxX", f->wmap) != -1)
				return (0);
		}
		return (-1);
	}
	return (-1);
}

static int		verify_map_head(t_filler *f)
{
	char	*ptr;
	int		i;

	i = 0;
	if (ft_str_nb_of_target(f->line, " ") == 4
			&& ft_strlen(f->line) == (size_t)f->wmap + 4)
	{
		if (!(ptr = ft_strchr(f->line, '0')) || ft_strchr(ptr, '\t'))
			return (-1);
		else
			while (i + 1 < f->wmap)
			{
				if (ptr[i] < ptr[i + 1] && ptr[i] != '9')
					i++;
				else if (ptr[i] == '9' && ptr[i + 1] == '0')
					i++;
				else
					return (-1);
			}
		return (0);
	}
	return (-1);
}

static int		checker(t_filler *f, int i)
{
	int err;

	if (i == 0)
		err = verify_map_head(f);
	else
		err = verify_map_body(f, i);
	return ((err < 0) ? -1 : 1);
}

int				check_and_store_map(t_filler *f)
{
	int i;
	int err;

	i = 0;
	while (i < f->hmap + 1 && get_next_line(STDIN_FILENO, &f->line) > 0
			&& (err = checker(f, i)) > 0)
	{
		if (make_map(f, i) == -1)
		{
			ft_tabdel(i - 1, &f->map);
			ft_strdel(&f->line);
			return (-1);
		}
		ft_strdel(&f->line);
		i++;
	}
	if (err < 0)
	{
		ft_tabdel(i - 1, &f->map);
		ft_strdel(&f->line);
		return (-1);
	}
	ft_strdel(&f->line);
	return (0);
}
