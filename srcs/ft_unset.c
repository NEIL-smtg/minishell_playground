/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 23:03:21 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 23:14:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reconstruct_env(t_shell *info, int deleted)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = ft_calloc(get_2d_arr_size(info->ms_env), sizeof(char *));
	i = -1;
	j = 0;
	while (info->ms_env[++i])
		if (i != deleted)
			new_env[j++] = ft_strdup(info->ms_env[i]);
	ft_free2d(info->ms_env);
	info->ms_env = new_env;
}

static void	search_and_replace(char *target, t_shell *info)
{
	int	i;

	i = -1;
	while (info->ms_env[++i])
	{
		if (!ft_strncmp(target, info->ms_env[i], ft_strlen(target)))
		{
			reconstruct_env(info, i);
			return ;			
		}
	}
}

void	ft_unset(char **s_cmd, t_shell *info)
{
	int	i;

	if (get_2d_arr_size(s_cmd) < 2)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		info->ms_status = 1;
		return ;
	}
	i = 0;
	while (s_cmd[++i])
		search_and_replace(s_cmd[i], info);
	info->ms_status = 0;
}
