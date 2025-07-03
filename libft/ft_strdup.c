/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:30:57 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:30:59 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdlib.h>

char	*ft_strdup(const char	*src)
{
	int		index;
	char	*dest;
	char	*d;

	index = 0;
	d = ((dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1)));
	if (!d)
	{
		return (0);
	}
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return ((char *)dest);
}
//  #include <stdio.h>
//  int main()
//  {
// 	printf("%s", ft_strdup("hello"));
// 	return (0);
//  }
