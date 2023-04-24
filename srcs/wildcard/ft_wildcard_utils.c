/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:36:13 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 18:36:46 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_curr_dir(char *cmd, int i)
{
	int	j;

	if (i == 0 || ft_isspace(cmd[i - 1]))
		return (1);
	j = i;
	while (cmd[j] && !ft_isspace(cmd[j]))
		--j;
	return (ft_strncmp("./*", &cmd[j], 3) == 0);
}

char	*get_target(char *cmd, int i)
{
	int		j;

	j = i;
	while (cmd[j] && !ft_isspace(cmd[j]))
		++j;
	if (j == i)
		return (NULL);
	return (ft_substr(cmd, i, j - i));
}

int	target_found(char *file, char *target)
{
	size_t	target_len;
	size_t	file_len;
	size_t	file_start;

	if (!ft_strncmp("..", file, 2) || !ft_strncmp(".", file, 1))
		return (0);
	if (!target)
		return (1);
	target_len = ft_strlen(target);
	file_len = ft_strlen(file);
	if (target_len > file_len)
		return (0);
	file_start = file_len - target_len;
	return (ft_strncmp(&file[file_start], target, target_len) == 0);
}

void	files_addback(t_files **files, char *file)
{
	t_files	*new;
	t_files	*last;

	new = ft_calloc(1, sizeof(t_files));
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!files || !*files)
		*files = new;
	else
	{
		last = *files;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
