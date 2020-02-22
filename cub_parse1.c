/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 02:43:48 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/22 06:39:16 by lejulien         ###   ########.fr       */
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

static void
	ft_getpath(char *currentline, t_sort *sort, int wich)
{
	char *bsptr;
	int i;

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

static void
	ft_checksprite(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	ft_getpath(currentline, sort, 4);
}

void
	ft_checks(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (currentline[1] == 'O')
		currentline++;
	else
		return(ft_checksprite(currentline, sort));
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	ft_getpath(currentline, sort, 1);
}

void
	ft_checke(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (currentline[1] == 'A')
		currentline++;
	else
		ft_puterror("Error east texture\n");
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	ft_getpath(currentline, sort, 2);
}

void
	ft_checkw(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (currentline[1] == 'E')
		currentline++;
	else
		ft_puterror("Error west texture\n");
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	ft_getpath(currentline, sort, 3);
}

char
	*ft_testsrc(char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
		i++;
	i--;
	if (src[i] != 'm' && src[i] != 'M')
		ft_puterror("east res src Error\n");
	i--;
	if (src[i] != 'p' && src[i] != 'P')
		ft_puterror("east res src Error\n");
	i--;
	if (src[i] != 'x' && src[i] != 'X')
		ft_puterror("east res src Error\n");
	i--;
	if (src[i] != '.' && src[i] != '.')
		ft_puterror("east res src Error\n");
	return (src);
}
