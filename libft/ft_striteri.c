/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:31:03 by raldanda          #+#    #+#             */
/*   Updated: 2024/08/27 13:31:08 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int,
char*))
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}

// #include "libft.h"
// #include<stdio.h>

// void print_index_char(unsigned int index, char *c)
// {
// 	printf("Character at index %d: %c\n", index, *c);
// 	*c = 'X'; 
// }

// int main(void)
// {
// 	char str[] = "Hello, World!";
// 	printf("Original string: %s\n", str);
// 	ft_striteri(str, print_index_char);
// 	printf("Modified string: %s\n", str);

// 	return 0;
// }