/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:27:26 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:27:28 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// #include "libft.h"

// int main() {
//     // Test case 1: Compare two equal strings
//     char str1[] = "Hello";
//     char str2[] = "Hello";
//     int result = ft_memcmp(str1, str2, strlen(str1));
//     printf("Test case 1: %d\n", result); // Output: 0

//     // Test case 2: Compare two different strings
//     char str3[] = "Hello";
//     char str4[] = "World";
//     result = ft_memcmp(str3, str4, strlen(str3));
//     printf("Test case 2: %d\n", result); // Output: < 0
// 	    return 0;
// }