/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:16:07 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 22:28:36 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **s_cmd, t_shell *info)
{
	char	pwd[4096];

	if (get_2d_arr_size(s_cmd) > 1)
	{
		ft_putendl_fd("minishell : too many arguments", 2);
		info->ms_status = 1;
		return ;
	}
	getcwd(pwd, sizeof(pwd));
	ft_putendl_fd(pwd, 1);
	info->ms_status = 0;
}
