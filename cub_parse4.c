/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:47:50 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 20:48:54 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"
#include "./get_next_line.h"

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

void
	ft_encodemap(t_sort *sort)
{
	char *tofree;
	char *temp;

	if (sort->previousline)
	{
		tofree = ft_strjoin(sort->previousline, "~");
		temp = ft_strjoin(tofree, sort->currentline);
		ft_subspace(temp);
		free(tofree);
		free(sort->previousline);
		sort->previousline = ft_subspace(temp);
		free(temp);
		free(sort->currentline);
	}
}

void
	ft_getline_checktype(t_sort *sort, int ret)
{
	sort->previousline = sort->currentline;
	ft_check_types(sort->currentline, sort, ret);
}

char
	*ft_compressmap(int fd, t_sort *sort)
{
	int	ret;
	int	isatmap;

	ret = 1;
	isatmap = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &sort->currentline);
		if (sort->currentline[0] == '1')
			isatmap = 1;
		if (isatmap)
		{
			if (ret == 0)
			{
				free(sort->currentline);
				return (sort->previousline);
			}
			check_line_start(&sort->currentline, ret);
			ft_encodemap(sort);
		}
		else
			ft_getline_checktype(sort, ret);
	}
	return (NULL);
}

