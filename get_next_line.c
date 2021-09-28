#include "get_next_line.h"

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

char *get_current_line(char **str, size_t buff)
{
	size_t i;

	i = 0;
	if (!*str)
		return (NULL);
	while ((*str)[i] == '\0' || (*str)[i] != '\n')
	{
		*str[i] = '\0';
		*str = ft_strdup(*str);
		i++;
	}
	printf("a%s", *str);
	if (i < buff)
		(*str)[i] = '\n';
	else
		(*str)[i] = '\0';
	return (*str);
}

static void re_read(int fd, char *text, char **stext, ssize_t buff)
{
	char *tmptext;

	tmptext = NULL;
	while (buff > 0)
	{
		if (*stext == NULL)
			*stext = ft_strdup("");
		tmptext = ft_strjoin(*stext, text);
		free (*stext);
		*stext = tmptext;
		if (ft_strchr(*stext, '\n'))
			break ;
		buff = read(fd, text, BUFFER_SIZE);
		text[buff] = '\0';
	}
	free (text);
}

char *get_next_line(int fd)
{
	char *text;
	static char *stext;
	ssize_t buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (text == NULL)
		return (NULL);	
	buff = read(fd, text, BUFFER_SIZE);
	text[buff] = '\0';
	re_read(fd, text, &stext, buff);
	if (buff < 0)
		return (0);
	return (get_current_line(&stext, buff));
}
