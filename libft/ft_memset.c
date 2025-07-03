/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:28:26 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:28:29 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c,	size_t len)
{
	char	*d;

	d = (char *)b;
	while (len > 0)
	{
		d[len -1] = c;
		len--;
	}
	return (b);
}
// #include <stdio.h>
// #include "libft.h"

// int main() {
//     char str[20] = "Hello, world!";
//     printf("Before memset: %s\n", str);
//     ft_memset(str, '$', 7);
//     printf("After memset: %s\n", str);
//     return 0;
// }