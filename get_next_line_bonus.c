/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 09:58:36 by vsavilov          #+#    #+#             */
/*   Updated: 2021/10/04 10:00:41 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	*sresult;

	if (s == NULL)
		return (NULL);
	sresult = (char *)s;
	while (*sresult != (char)c)
	{
		if (*sresult == '\0')
			return (NULL);
		sresult++;
	}
	return (sresult);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_strlen(src));
	while ((src[i]) && (i < dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*get_current_line(char **str)
{
	size_t	i;
	char	*tmp;
	char	*tmpout;

	tmpout = NULL;
	i = 0;
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	if ((*str)[i] == '\n')
	{
		tmpout = ft_substr(*str, 0, i + 1);
		tmp = ft_strdup(*str + i + 1);
		free(*str);
		*str = tmp;
		if (!**str)
		{
			free(*str);
			*str = NULL;
		}
		return (tmpout);
	}
	tmpout = ft_strdup(*str);
	free(*str);
	*str = NULL;
	return (tmpout);
}

static void	re_read(int fd, char *text, char **stext, ssize_t buff)
{
	char	*tmptext;

	tmptext = NULL;
	while (buff > 0)
	{
		text[buff] = '\0';
		if (stext[fd] == NULL)
			stext[fd] = ft_strdup("");
		tmptext = ft_strjoin(stext[fd], text);
		free(stext[fd]);
		stext[fd] = tmptext;
		if (ft_strchr(text, '\n'))
			break ;
		buff = read(fd, text, BUFFER_SIZE);
	}
	free(text);
}

char	*get_next_line(int fd)
{
	char		*text;
	static char	*stext[FDM];
	ssize_t		buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (text == NULL)
		return (NULL);
	buff = read(fd, text, BUFFER_SIZE);
	re_read(fd, text, stext, buff);
	if (buff < 0)
		return (NULL);
	if (!buff && (!stext[fd] || !*stext[fd]))
		return (NULL);
	return (get_current_line(&stext[fd]));
}
