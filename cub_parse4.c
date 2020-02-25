/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:47:50 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 04:31:05 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_check_types(char *currentline, t_sort *sort, int ret)
{
	if (ret == 0)
		ft_puterror("\e[33mno map Error\n");
	if (currentline[0] == 'R')
		ft_checkr(currentline, sort);
	else if (currentline[0] == 'B')
		ft_checkb(currentline, sort);
	else if (currentline[0] == 'N')
		ft_checkn(currentline, sort);
	else if (currentline[0] == 'S')
		ft_checks(currentline, sort);
	else if (currentline[0] == 'E')
		ft_checke(currentline, sort);
	else if (currentline[0] == 'W')
		ft_checkw(currentline, sort);
	else if (currentline[0] == 'C')
		ft_checkc(currentline, sort);
	else if (currentline[0] == 'F')
		ft_checkf(currentline, sort);
}

void
	check_line_start(char **currentline, int ret)
{
	if (*currentline[0] != '1' && ret == 1)
	{
		free(*currentline);
		write(1, "Error map\n", 10);
		exit (0);
	}
}
