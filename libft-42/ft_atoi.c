/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:28:27 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/07 21:29:42 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_isspace(char c)
{
	if ((c == '\f') || (c == '\t') || (c == '\n') || (c == '\r')
		|| (c == '\v') || (c == ' '))
	{
		return (1);
	}
	return (0);
}

int				ft_atoi(const char *str)
{
	int nbr;
	int sign;
	int index;

	nbr = 0;
	sign = 1;
	index = 0;
	while ((ft_isspace(str[index]) == 1) && str[index] != '\0')
		index++;
	if ((str[index] == '+') || (str[index] == '-'))
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while ((str[index] >= '0') && (str[index] <= '9'))
	{
		nbr = (nbr * 10) + (str[index] - '0');
		index++;
	}
	return (sign * nbr);
}
