/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:45:23 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/20 21:15:49 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

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

void	error_msg(const char *msg)
{
	if (msg)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putstr_fd((char *)msg, STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd("Error", STDERR_FILENO);
	}
	return ;
}
