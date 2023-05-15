/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:05:41 by suchua            #+#    #+#             */
/*   Updated: 2023/05/15 18:16:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_input(t_shell *info, t_cmdlst **node)
{
	int	last;

	if (ft_strchr((*node)->cmd, 34) || ft_strchr((*node)->cmd, 39))
	{
		generate_new_input(info, node, -1);
		last = ft_strlen((*node)->cmd) - 1;
		if ((*node)->cmd[last] == 32)
			(*node)->cmd[last] = 0;
	}
	else
		no_quote_parsing(info, node);
}
