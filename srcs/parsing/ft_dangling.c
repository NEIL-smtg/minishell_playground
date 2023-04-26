/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dangling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 00:22:02 by suchua            #+#    #+#             */
/*   Updated: 2023/04/26 20:03:36 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dangling_squote(char *str)
{
	int	squote;
	int	i;

	squote = 0;
	i = 0;
	while (ft_strchr(&str[i], 39))
	{
		squote = !squote;
		while (str[i] && str[i] != 39)
			++i;
		if (!str[i])
			break ;
		++i;
	}
	return (squote);
}

int	dangling_dquote(char *str)
{
	int	dquote;
	int	i;

	dquote = 0;
	i = 0;
	while (ft_strchr(&str[i], 34))
	{
		dquote = !dquote;
		while (str[i] && str[i] != 34)
			++i;
		if (!str[i])
			break ;
		++i;
	}
	return (dquote);
}

int	dangling_bracket(char *str, int dq, int sq, int echo)
{
	int	len;
	int	count;
	int	i;

	i = 0;
	len = ft_strlen(str);
	count = 0;
	while (i < len)
	{
		if (!ft_strncmp("echo", &str[i], 4))
			echo = 1;
		if (str[i] == 34)
			dq = !dq;
		if (str[i] == 39)
			sq = !sq;
		if (!echo && !dq && !sq && str[i] == '(')
			++count;
		else if (!echo && !dq && !sq && str[i] == ')')
			--count;
		if (echo && !dq && !sq && instr_split(&str[i]))
			echo = 0;
		++i;
	}
	return (count == 0);
}

int	ft_dangling(char *str, int print)
{
	if (dangling_dquote(str) || dangling_squote(str)
		|| !dangling_bracket(str, 0, 0, 0))
	{
		if (print)
		{
			add_history(str);
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		}
		return (0);
	}
	if (dangling_redir(str))
	{
		add_history(str);
		return (0);
	}
	return (1);
}
