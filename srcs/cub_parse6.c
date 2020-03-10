/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 01:56:58 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/10 04:27:27 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_check_end_r(char *currentline)
{
	int	i;

	i = 0;
	while (ft_isdigit(currentline[i]) == 1)
		i++;
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	if (currentline[i] != '\0')
		ft_puterror("Error bad argument\n");
}

void
	ft_wrongline(char *currentline)
{
	free(currentline);
	ft_puterror("Error wrong line\n");
}

void
	ft_init_instructions(t_sort *sort)
{
	sort->ir = 0;
	sort->in = 0;
	sort->iso = 0;
	sort->ie = 0;
	sort->iw = 0;
	sort->is = 0;
	sort->inf = 0;
	sort->ic = 0;
}

void
	ft_path_selector(int wich, t_sort *sort, char *currentline)
{
	if (wich == 0)
	{
		sort->northpath = currentline;
		sort->in++;
	}
	else if (wich == 1)
	{
		sort->southpath = currentline;
		sort->iso++;
	}
	else if (wich == 2)
	{
		sort->eastpath = currentline;
		sort->ie++;
	}
	else if (wich == 3)
	{
		sort->westpath = currentline;
		sort->iw++;
	}
	else if (wich == 4)
	{
		sort->sprite = currentline;
		sort->is++;
	}
}

void
	ft_check_double(t_sort *sort)
{
	if (sort->ir != 1)
		ft_puterror("Error resolution missing or in double\n");
	if (sort->in != 1)
		ft_puterror("Error north path missing or in double\n");
	if (sort->iso != 1)
		ft_puterror("Error south path missing or in double\n");
	if (sort->ie != 1)
		ft_puterror("Error east path missing or in double\n");
	if (sort->iw != 1)
		ft_puterror("Error west path missing or in double\n");
	if (sort->is != 1)
		ft_puterror("Error sprite path missing or in double\n");
	if (sort->inf != 1)
		ft_puterror("Error floor color missing or in double\n");
	if (sort->ic != 1)
		ft_puterror("Error ceiling color missing or in double\n");
}
