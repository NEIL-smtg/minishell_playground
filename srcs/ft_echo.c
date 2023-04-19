/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:12:19 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 23:17:58 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **s_cmd, t_shell *info)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (!ft_strncmp(s_cmd[1], "-n", 3))
	{
		flag = 1;
		++i;
	}
	while (s_cmd[++i])
		ft_putstr_fd(s_cmd[i], 1);
	if (flag)
		ft_putstr_fd("%", 1);
	ft_putchar_fd('\n', 1);
	info->ms_status = 0;
}
