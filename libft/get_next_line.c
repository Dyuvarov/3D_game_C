/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:53:49 by ugreyiro          #+#    #+#             */
/*   Updated: 2020/12/20 11:57:37 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define BUFFER_SIZE 32

static int		error_exit(char **tmp, char **line, char **buf)
{
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	return (-1);
}

static char		*empty_line(void)
{
	char	*result;

	if ((result = (char *)malloc(sizeof(char))))
		result[0] = '\0';
	return (result);
}

static char		*work_on_tmp(char **line, char **tmp, int *err_flag)
{
	char *p_nl;
	char *tmp_to_free;

	p_nl = NULL;
	if (*tmp)
	{
		if ((p_nl = ft_strchr(*tmp, '\n')))
		{
			*p_nl = '\0';
			*line = ft_strdup(*tmp);
			tmp_to_free = *tmp;
			if (!(*tmp = ft_strdup(++p_nl)))
				*err_flag = 1;
			free(tmp_to_free);
		}
		else
		{
			*line = ft_strdup(*tmp);
			free(*tmp);
			*tmp = NULL;
		}
	}
	else
		*line = empty_line();
	return (p_nl);
}

static int		check_buf(char **p_nl, char *buf, char **line, char **tmp)
{
	if ((*p_nl = ft_strchr(buf, '\n')))
	{
		**p_nl = '\0';
		if (!(*line = ft_strjoin(*line, buf)))
			return (0);
		if (!(*tmp = ft_strdup(++(*p_nl))))
			return (0);
	}
	else if (!(*line = ft_strjoin(*line, buf)))
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*tmp;
	char		*buf;
	int			read_res;
	char		*p_nl;
	int			err_flag;

	err_flag = 0;
	read_res = 1;
	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	p_nl = work_on_tmp(line, &tmp, &err_flag);
	if (err_flag || !(*line))
		return (error_exit(&tmp, line, &buf));
	while ((!p_nl) && ((read_res = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[read_res] = '\0';
		if (!(check_buf(&p_nl, buf, line, &tmp)))
			return (error_exit(&tmp, line, &buf));
	}
	free(buf);
	return ((read_res > 0) ? 1 : read_res);
}
