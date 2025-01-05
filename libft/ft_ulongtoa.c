/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulongtoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:35:29 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/21 18:20:19 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_ulongtoa(unsigned long value)
{
	char buffer[21]; /* ulong max is 18446744073709551615 => 20 chars max*/
	char *ptr = &buffer[20];

	*ptr = '\0';

	if (value == 0)
	{
		ptr--;
		*ptr = '0';
	}
	else
	{
		while (value > 0)
		{
			ptr--;
			*ptr = '0' + (value % 10);
			value /= 10;
		}
	}

	size_t length = ft_strlen(ptr);
	char *result = ft_strnew(length);

	if (!result)
		return NULL;

	ft_strcpy(result, ptr);

	return result;
}
