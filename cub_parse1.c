/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 02:43:48 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/24 02:35:53 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_checkr(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (!ft_whitespace(currentline[i]))
		ft_puterror("\e[33mres Error\n");
	while (ft_whitespace(currentline[i]))
		i++;
	sort->resw = ft_atoi(&currentline[i]);
	if (!sort->resw)
		ft_puterror("\e[33mres Error\n");
	while (ft_isdigit(currentline[i]) == 1)
		i++;
	if (!ft_whitespace(currentline[i]))
		ft_puterror("\e[33mres Error\n");
	sort->resh = ft_atoi(&currentline[i]);
	if (!sort->resh)
		ft_puterror("\e[33mres Error\n");
}

void
	ft_checkb(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	if (currentline[i] == '1')
		sort->isbonus = 1;
}

void
	ft_getpath(char *currentline, t_sort *sort, int wich)
{
	char	*bsptr;
	int		i;

	currentline++;
	if (ft_whitespace(*currentline) != 1)
		ft_puterror("textureError\n");
	while (ft_whitespace(*currentline) == 1)
		currentline++;
	bsptr = currentline;
	while (ft_whitespace(*bsptr) != 1 && *bsptr != '\0')
		bsptr++;
	*bsptr = '\0';
	if (wich == 0)
		sort->northpath = currentline;
	else if (wich == 1)
		sort->southpath = currentline;
	else if (wich == 2)
		sort->eastpath = currentline;
	else if (wich == 3)
		sort->westpath = currentline;
	else if (wich == 4)
		sort->sprite = currentline;
}

void
	ft_checkn(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (currentline[1] == 'O')
		currentline++;
	else
		ft_puterror("Error north texture\n");
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	ft_getpath(currentline, sort, 0);
}
