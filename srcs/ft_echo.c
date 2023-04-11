/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:31:44 by suchua            #+#    #+#             */
/*   Updated: 2023/03/15 23:48:11 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exist(char *str, char **env)
{
	int		i;
	char	*tmp;
	int		len;

	if (*str == 0)
		return (0);
	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
		++i;
	tmp = ft_strdup(str);
	tmp[i] = 0;
	len = ft_strlen(tmp);
	i = 0;
	while (ft_strncmp(tmp, env[i], len))
		++i;
	free(tmp);
	if (!env[i])
		return (0);
	ft_putstr_fd(env[i] + len + 1, 1);
	return (len + 1);
}

int	put_str_quote(char *s, char q)
{
	int		i;

	i = 0;
	ft_putchar_fd(s[i++], 1);
	while (s[i] && s[i] != q)
		ft_putchar_fd(s[i++], 1);
	if (s[i] == q)
		ft_putchar_fd(s[i++], 1);
	return (i);
}

int	print_till_quote(char *s, char quote)
{
	int		len;
	char	another;

	another = 34;
	if (quote == 34)
		another = 39;
	if (quote == 34 && another == 39)
		len = put_str_quote(s, quote);
	else
	{
		ft_putchar_fd(quote, 1);
		len = 1;
	}
	return (len);
}

static void	process_line(char *str, t_shell *info)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp("$?", &str[i], 2))
		{
			ft_putnbr_fd(info->ms_status, 1);
			i += 2;
		}
		else if (str[i] == 34 || str[i] == 39)
			i += print_till_quote(&str[i], str[i]);
		else if (str[i] == '$')
			i += var_exist(&str[i + 1], info->ms_env);
		else
			write(1, &str[i++], 1);
	}
}

void	ft_echo(t_shell *info, char **cmd)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (cmd[++i])
	{
		if (i == 1 && !ft_strncmp("-n", cmd[i], 3))
		{
			flag = 1;
			continue ;
		}
		process_line(cmd[i], info);
		if (cmd[i + 1])
			write(1, " ", 1);
	}
	if (flag)
		write(1, "%%", 1);
	write(1, "\n", 1);
	info->ms_status = 0;
}
