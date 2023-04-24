/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:10:52 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 23:20:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **s_cmd, t_shell *info)
{
	int	i;

	i = -1;
	if (get_2d_arr_size(s_cmd) > 1)
	{
		ft_putendl_fd("minishell : too many arguments", 2);
		info->ms_status = 1;
		return ;
	}
	while (info->ms_env[++i])
		ft_putendl_fd(info->ms_env[i], 1);
	info->ms_status = 0;
}
