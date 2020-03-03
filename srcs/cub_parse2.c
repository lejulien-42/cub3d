/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 02:28:33 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/03 05:04:14 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static int
	ft_checkdcc(int i)
{
	if (i <= 255 && i >= 0)
		return (i);
	ft_puterror("\e[31mError rgb not between 0 and 255\n");
	return (0);
}

static int
	next_n_check_coma(char *currentline, int i)
{
	int j;

	j = 0;
	while (ft_whitespace(currentline[j]))
		j++;
	while (ft_isdigit(currentline[j]))
		j++;
	while (ft_whitespace(currentline[j]))
		j++;
	if (!(currentline[j] == ','))
		ft_puterror("Error rgb");
	j++;
	while (ft_whitespace(currentline[j]))
		j++;
	return (i + j);
}

void
	ft_checkc(char *currentline, t_sort *sort)
{
	int i;
	int r;
	int g;
	int b;

	i = 1;
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33Ceiling color Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	if (!ft_isdigit(currentline[i]))
		ft_puterror("\e[33mCeiling color Error\n");
	r = ft_checkdcc(ft_atoi(&currentline[i]));
	i = next_n_check_coma(&currentline[i], i);
	g = ft_checkdcc(ft_atoi(&currentline[i]));
	i = next_n_check_coma(&currentline[i], i);
	b = ft_checkdcc(ft_atoi(&currentline[i]));
	sort->rgbc = rgb_int(r, g, b);
	free(currentline);
}

void
	ft_checkf(char *currentline, t_sort *sort)
{
	int i;
	int r;
	int g;
	int b;

	i = 1;
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33Ceiling color Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	if (!ft_isdigit(currentline[i]))
		ft_puterror("\e[33mCeiling color Error\n");
	r = ft_checkdcc(ft_atoi(&currentline[i]));
	i = next_n_check_coma(&currentline[i], i);
	g = ft_checkdcc(ft_atoi(&currentline[i]));
	i = next_n_check_coma(&currentline[i], i);
	b = ft_checkdcc(ft_atoi(&currentline[i]));
	sort->rgbf = rgb_int(r, g, b);
	free(currentline);
}
