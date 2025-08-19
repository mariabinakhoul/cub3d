/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:43:00 by raldanda          #+#    #+#             */
/*   Updated: 2025/08/19 11:51:36 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_in_charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_in_charset(*str, charset))
			str++;
		if (*str && !is_in_charset(*str, charset))
		{
			count++;
			while (*str && !is_in_charset(*str, charset))
				str++;
		}
	}
	return (count);
}

char	*word_dup(char *str, char *charset)
{
	int		len;
	char	*word;

	len = 0;
	while (str[len] && !is_in_charset(str[len], charset))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	len = 0;
	while (*str && !is_in_charset(*str, charset))
		word[len++] = *str++;
	word[len] = '\0';
	return (word);
}

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	char	**result;

	i = 0;
	if (!str)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!result)
		return (NULL);
	while (*str)
	{
		while (*str && is_in_charset(*str, charset))
			str++;
		if (*str)
		{
			result[i] = word_dup(str, charset);
			if (!result[i++])
				return (NULL);
			while (*str && !is_in_charset(*str, charset))
				str++;
		}
	}
	result[i] = NULL;
	return (result);
}

// unsigned int	clamp8(int x)
// {
// 	if (x < 0)
// 		return (0);
// 	else if (x > 255)
// 		return (255);
// 	return ((unsigned int)x);
// }
