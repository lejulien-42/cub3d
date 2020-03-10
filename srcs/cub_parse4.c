/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:47:50 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/10 02:46:44 by lejulien         ###   ########.fr       */
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
	else if (currentline[0] != '\0')
		ft_wrongline(currentline);
	else
	{
		currentline[0] = 's';
		free(currentline);
	}
}

void
	check_line_start(char **currentline, int ret)
{
	int	i;

	i = 0;
	while (currentline[0][i] == ' ')
		i++;
	if (currentline[0][i] != '1' && ret == 1)
	{
		printf("-=> %c\n", currentline[0][i]);
		free(*currentline);
		ft_puterror("Error wrong map\n");
	}
}

void
	ft_encodemap(t_sort *sort)
{
	char	*tofree;
	char	*temp;
	int		i;

	i = 0;
	while (sort->previousline[i] == ' ')
		i++;
	if (sort->previousline[i] == '1')
	{
		tofree = ft_strjoin(sort->previousline, "~");
		temp = ft_strjoin(tofree, sort->currentline);
		free(sort->previousline);
		free(tofree);
		sort->previousline = ft_str_spacetoone(temp);
		free(temp);
		free(sort->currentline);
	}
	else
		sort->previousline = sort->currentline;
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
	int	i;

	ret = 1;
	isatmap = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &sort->currentline);
		i = 0;
		while (sort->currentline[i] == ' ')
			i++;
		if (sort->currentline[i] == '1')
			isatmap = 1;
		if (isatmap)
		{
			check_line_start(&sort->currentline, ret);
			ft_encodemap(sort);
			if (ret == 0)
				return (sort->previousline);
		}
		else
			ft_getline_checktype(sort, ret);
	}
	return (NULL);
}
