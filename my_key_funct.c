/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_key_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 18:10:19 by ajubert           #+#    #+#             */
/*   Updated: 2016/03/04 18:38:20 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include <stdio.h>

int		my_key_funct(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	printf("key event -------%d", keycode);
	return (0);
}
