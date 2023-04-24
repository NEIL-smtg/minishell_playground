/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:34:16 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 23:17:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_in_order(t_shell *info, int env_size)
{
	char	**dup_env;
	int		i;
	int		j;

	dup_env = ft_2d_strdup(info->ms_env);
	i = -1;
	while (dup_env[++i])
	{
		j = env_size;
		while (--j > i)
			if (ft_strncmp(dup_env[i], dup_env[j], ft_strlen(dup_env[i])) > 0)
				swap_str(&dup_env[i], &dup_env[j]);
	}
	i = -1;
	while (dup_env[++i])
		ft_putendl_fd(dup_env[i], 1);
	ft_free2d(dup_env);
	info->ms_status = 0;
}

void	add_or_replace(char *target, char *new, t_shell *info)
{
	int		i;
	char	**new_env;
	int		len;

	i = -1;
	while (info->ms_env[++i])
	{
		if (!ft_strncmp(target, info->ms_env[i], ft_strlen(target)))
		{
			free(target);
			free(info->ms_env[i]);
			info->ms_env[i] = ft_strdup(new);
			return ;
		}
	}
	free(target);
	len = get_2d_arr_size(info->ms_env);
	new_env = ft_calloc(len + 2, sizeof(char *));
	i = -1;
	while (++i < len)
		new_env[i] = ft_strdup(info->ms_env[i]);
	new_env[i] = ft_strdup(new);
	ft_free2d(info->ms_env);
	info->ms_env = new_env;
}

void	export_to_env(char **s_cmd, t_shell *info)
{
	int		i;
	int		flag;
	int		j;

	i = 0;
	flag = 1;
	while (s_cmd[++i])
	{
		if (!ft_strchr(s_cmd[i], '='))
			continue ;
		j = 0;
		while (s_cmd[i][j] && s_cmd[i][j] != '=')
			++j;
		add_or_replace(ft_substr(s_cmd[i], 0, j), s_cmd[i], info);
		flag = 0;
	}
	info->ms_status = flag;
}

void	ft_export(char **s_cmd, t_shell *info)
{
	int	size;

	size = get_2d_arr_size(s_cmd);
	if (size == 1)
		print_env_in_order(info, get_2d_arr_size(info->ms_env));
	else
		export_to_env(s_cmd, info);
}
