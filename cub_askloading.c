/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_askloading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 23:00:43 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 07:14:27 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"
#include "./get_next_line.h"
#include "./libft-42/libft.h"

int
	ft_askloading(char *txt)
{
	char	*line;
	int		ret;

	line = NULL;
	ft_putstr_fd("\e[39m", 1);
	ft_putstr_fd(txt, 1);
	ft_putstr_fd("\e[33mcub\e[36m3D \e[96m>> \e[95m", 1);
	while ((ret = get_next_line(0, &line)) == 1)
	{
		if (line[0] == 'y' && line[1] == '\0')
		{
			free(line);
			return (1);
		}
		else if (line[0] == 'n' && line[1] == '\0')
		{
			free(line);
			return (0);
		}
		ft_putstr_fd("\e[91mPlease answer y or n :", 1);
		free(line);
		ft_putstr_fd("\n\e[33mcub\e[36m3D \e[96m>> \e[95m", 1);
	}
	ft_puterror("\nError texture file missing");
	return (0);
}
