/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:30:39 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:30:41 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	while ((char)i != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

// #include <stdio.h>

// int main()

// {
// 	printf("%s", ft_strchr("hello",'e'));
// 	return (0);
// }
