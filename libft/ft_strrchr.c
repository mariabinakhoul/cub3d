/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:32:11 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:32:14 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			ret = (char *)s;
		++s;
	}
	if (!c)
		ret = ((char *)s);
	return (ret);
}
// #include <stdio.h>

// int main()

// {
// 	printf("%s", ft_strrchr("hello",'e'));
// 	return (0);
// }
