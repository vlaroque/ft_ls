/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:40:19 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/21 18:19:29 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool ft_ispunct(int c)
{
	return (c >= 33 && c <= 47) || // !"#$%&'()*+,-./
		   (c >= 58 && c <= 64) || // :;<=>?@
		   (c >= 91 && c <= 96) || // [\]^_`
		   (c >= 123 && c <= 126); // {|}~
}