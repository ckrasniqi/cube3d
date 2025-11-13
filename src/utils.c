/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:39:41 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 21:06:21 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

char *ft_skip_whitespace(const char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (char *)str;
}

void	error_msg(char *msg)
{
	if (msg)
	{
		ft_putendl_fd((char *)msg, STDERR_FILENO);
		ft_putendl_fd((char *)msg, STDOUT_FILENO);
	}
}

void	ft_error(char *error)
{
	const char	*msg;

	if (error)
	{
		ft_putendl_fd(error, STDERR_FILENO);
		ft_putstr_fd(error, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	msg = mlx_strerror(mlx_errno);
	if (!msg)
		msg = "Unknown MLX error";
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
