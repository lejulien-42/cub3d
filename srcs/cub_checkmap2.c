/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_checkmap2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 22:27:21 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/05 03:59:29 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static int
	ft_checkfullone(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void
	ft_checkone(t_mlx_data *data, int i)
{
	int j;

	j = ft_strlen(data->map[i]) - 1;
	while (j < ft_strlen(data->map[i + 1]))
	{
		if (data->map[i + 1][j] != '1')
			ft_puterror("\e[33mError wall not closed\n");
		j++;
	}
}

static void
	ft_checktwo(t_mlx_data *data, int i)
{
	int j;

	j = ft_strlen(data->map[i + 1]) - 1;
	while (j < ft_strlen(data->map[i]))
	{
		if (data->map[i][j] != '1')
			ft_puterror("\e[33mError wall not closed\n");
		j++;
	}
}

static void
	ft_checklines(t_mlx_data *data)
{
	int i;
	int lena;
	int lenb;

	i = 0;
	while (ft_strlen(data->map[i + 1]) != 0)
	{
		lena = ft_strlen(data->map[i]);
		lenb = ft_strlen(data->map[i + 1]);
		if (lena < lenb)
			ft_checkone(data, i);
		if (lenb < lena)
			ft_checktwo(data, i);
		i++;
	}
}

void
	ft_checkmapborder(t_mlx_data *data)
{
	int i;

	i = 0;
	if ((ft_checkfullone(data->map[0]) == 0))
		ft_puterror("First or last line not closed\n");
	if (ft_strlen(data->map[1]) == 0)
		ft_puterror("make a map not a line !!!!\n");
	while (ft_strlen(data->map[i + 1]) != 0)
	{
		if (data->map[i][ft_strlen(data->map[i]) - 1] != '1')
			ft_puterror("Erreur map pas fermee a droite\n");
		i++;
	}
	ft_checklines(data);
}
