/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:15:46 by vsavilov          #+#    #+#             */
/*   Updated: 2021/09/30 17:52:43 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			j;
	char			*sresult;
	unsigned int	k;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sresult = (char *)malloc(sizeof(char) * (len + 1));
	if (sresult == NULL)
		return (NULL);
	k = ft_strlen(s);
	j = 0;
	if (start >= k)
	{
		*sresult = '\0';
		return (sresult);
	}
	while (j < len)
		sresult [j++] = s [start++];
	sresult[j] = '\0';
	return (sresult);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;
	size_t	lstr;

	i = -1;
	lstr = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (lstr + 1));
	if (s2 == NULL)
		return (NULL);
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*sresult;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	sresult = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (sresult == NULL)
		return (NULL);
	ft_strlcpy (sresult, s1, ft_strlen(s1) + 1);
	ft_strlcat (sresult, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (sresult);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	else
		while (src[j] && (dst_len + j) < dstsize)
			dst[i++] = src[j++];
	if ((dst_len + j) == dstsize && dst_len < dstsize)
		dst[--i] = '\0';
	else
		dst[i] = '\0';
	return (src_len + dst_len);
}
