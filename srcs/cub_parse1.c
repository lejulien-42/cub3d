/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 02:43:48 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/10 03:58:32 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static int
	ft_checkwidth(int i)
{
	if (i > 2560)
		i = 2560;
	if (i < 100)
		i = 0;
	return (i);
}

static int
	ft_checkheight(int i)
{
	if (i > 1440)
		i = 1440;
	if (i < 100)
		i = 100;
	return (i);
}

void
	ft_checkr(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (!ft_whitespace(currentline[i]))
		ft_puterror("\e[33mres Error\n");
	while (ft_whitespace(currentline[i]))
		i++;
	sort->resw = ft_checkwidth(ft_atoi(&currentline[i]));
	if (!sort->resw)
		ft_puterror("\e[33mres Error\n");
	while (ft_isdigit(currentline[i]) == 1)
		i++;
	if (!ft_whitespace(currentline[i]))
		ft_puterror("\e[33mres Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	sort->resh = ft_checkheight(ft_atoi(&currentline[i]));
	if (!sort->resh)
		ft_puterror("\e[33mres Error\n");
	ft_check_end_r(&currentline[i]);
	sort->ir++;
	free(currentline);
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
	ft_check_end_r(&currentline[i]);
	free(currentline);
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
	ft_path_selector(wich, sort, currentline);
}
