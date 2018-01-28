/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

#define JOBS COLOR_BRED"jobs: "COLOR_RESET

inline int	sh_bijobs(int ac, char **av, char **env)
{
	ssize_t	i;
	t_job	*job;

	(void)env;
	i = 0;
	sh_poolnotify();
	if (ac == 1)
		while ((size_t)i < sh_poollen())
			sh_jobdebug(sh_poolget((size_t)i++));
	else
		while (*++av)
		{
			i = ft_atoi(*av);
			if (ft_strlen(*av) != ft_intlen(i, 10) ||
				!(job = sh_poolget((size_t)i)))
				ft_putf(STDERR_FILENO, JOBS"%s: job not found\n", *av);
			else
				sh_jobdebug(job);
		}
	return (EXIT_SUCCESS);
}
