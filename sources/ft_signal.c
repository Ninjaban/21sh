/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 12:00:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/01 12:00:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "shell.h"

char		ft_signal_stop(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR ||
		signal(SIGTSTP, SIG_IGN) == SIG_ERR ||
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_log(TYPE_WARNING, ERROR_SIGNAL);
		return (ft_error_int(ERROR_LAUNCH, FALSE));
	}
	return (TRUE);
}

char		ft_signal_start(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR ||
		signal(SIGTSTP, SIG_DFL) == SIG_ERR ||
		signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_log(TYPE_WARNING, ERROR_SIGNAL);
		return (FALSE);
	}
	return (TRUE);
}
