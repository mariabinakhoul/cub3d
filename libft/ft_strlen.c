/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:31:38 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:31:40 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
// #include "libft.h"
// #include <stdio.h>

// int main(void) {
//     const char *str1 = "Hello, world!";
//     const char *str2 = "";

//     printf("Length of \"%s\": %zu\n", str1, ft_strlen(str1));
//     printf("Length of \"%s\": %zu\n", str2, ft_strlen(str2));

//     return (0);
// }
