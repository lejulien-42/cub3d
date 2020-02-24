/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 02:31:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/24 02:33:52 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
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
		return (ft_checksprite(currentline, sort));
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
	if (src[i] != '.')
		ft_puterror("east res src Error\n");
	return (src);
}
