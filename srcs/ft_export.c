/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:42:03 by suchua            #+#    #+#             */
/*   Updated: 2023/03/16 21:17:30 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_new_env(char **env, char *var)
{
	int		row;
	char	**new;
	int		i;

	row = 0;
	while (env[row])
		++row;
	new = malloc(sizeof(char *) * (row + 2));
	i = -1;
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	new[i++] = ft_strdup(var);
	new[i] = 0;
	return (new);
}

void	export_to_env(t_shell *info, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	if (info->input_size > 1)
		exit(EXIT_SUCCESS);
	i = 0;
	while (var[i] && var[i] != '=')
		++i;
	if (!var[i] || !var[i + 1])
		return ;
	j = 0;
	while (info->ms_env[j] && ft_strncmp(var, info->ms_env[j], i))
		++j;
	if (!info->ms_env[j])
	{
		new_env = create_new_env(info->ms_env, var);
		ft_free2d(info->ms_env);
		info->ms_env = new_env;
	}
	else
	{
		free(info->ms_env[j]);
		info->ms_env[j] = ft_strdup(var);
	}
}

void	sort_env(char **dup_env, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = size;
		while (--j > i)
			if (ft_strncmp(dup_env[i], dup_env[j], ft_strlen(dup_env[i])) > 0)
				swap_str(&dup_env[i], &dup_env[j]);
	}
}

static void	print_export(char **env)
{
	char	**dup_env;
	int		i;
	int		size;

	dup_env = ft_2d_strdup(env);
	size = 0;
	while (dup_env[size])
		++size;
	sort_env(dup_env, size);
	i = -1;
	while (++i < size)
		ft_putendl_fd(dup_env[i], 1);
	ft_free2d(dup_env);
}

void	ft_export(t_shell *info, char **cmd)
{
	if (info->input_size != 1)
		exit(EXIT_SUCCESS);
	if (get_2d_arr_size(cmd) == 1)
		print_export(info->ms_env);
	else if (get_2d_arr_size(cmd) > 2)
	{
		perror(cmd[2]);
		exit(EXIT_FAILURE);
	}
	else
		export_to_env(info, cmd[1]);
	info->ms_status = 0;
}
