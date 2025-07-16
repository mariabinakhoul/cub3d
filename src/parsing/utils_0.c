/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:43:00 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/15 11:21:44 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_in_charset(char c, char *charset)
{
	int	i = 0;

	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	count = 0;

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

// Allocates and copies a word
char	*word_dup(char *str, char *charset)
{
	int		len = 0;
	char	*word;

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

// Splits the string by the characters in charset
char	**ft_split_charset(char *str, char *charset)
{
	int		i = 0;
	char	**result;

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
