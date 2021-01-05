/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:25:18 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 19:25:19 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_default_mode_on(t_cntl *cntl)
{
	cntl->mode = DEFM;
	console_msg_welcome();
}
