/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 03:51:16 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/12 21:43:28 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		is_sep(char *str, char *sep, int i)
{
	int		j;

	j = 0;
	while (sep[j])
		if (sep[j++] == str[i])
			return (1);
	return (0);
}

static int		n_word(char *str, int n, char *sep)
{
	int		i;

	i = 0;
	while (n > -1 && str[i])
	{
		while (is_sep(str, sep, i))
			i++;
		if (!is_sep(str, sep, i))
		{
			if (n == 0)
				break ;
			else
				n--;
		}
		while (!is_sep(str, sep, i))
			i++;
	}
	if (n == -1)
		while (is_sep(str, sep, i))
			i++;
	return (i);
}

int				ft_count_word(char *str, char *sep)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (is_sep(str, sep, i) && str[i])
			i++;
		if (!is_sep(str, sep, i) && str[i])
			count++;
		while (!is_sep(str, sep, i) && str[i])
			i++;
	}
	return (count);
}

static char		**unloved(char *str, char *charset, int countw)
{
	int		countl;
	int		j;
	int		i;
	char	**ret;

	i = -1;
	countw = ft_count_word(str, charset);
	if (!(ret = malloc((countw + 1) * sizeof(char *))))
		return (NULL);
	while (++i < countw)
	{
		j = -1;
		countl = 0;
		while (!is_sep(str, charset, n_word(str, i, charset) + countl))
			countl++;
		if (!(ret[i] = malloc((countl + 1) * sizeof(char))))
			return (NULL);
		while (++j < countl)
			ret[i][j] = str[n_word(str, i, charset) + j];
		ret[i][j] = 0;
	}
	ret[i] = NULL;
	return (ret);
}

char			**ft_split_charset(char *str, char *charset)
{
	char	**ret;
	int		countw;
	int		i;

	i = 0;
	countw = ft_count_word(str, charset);
	if (charset[0] != 0 && charset != NULL)
		return (unloved(str, charset, countw));
	else
	{
		ret = malloc(2 * sizeof(char *));
		while (str[i])
			i++;
		ret[0] = malloc(i * sizeof(char));
		i = 0;
		while (str[i])
		{
			ret[0][i] = str[i];
			i++;
		}
		ret[0][i] = 0;
		ret[1] = NULL;
	}
	return (ret);
}
