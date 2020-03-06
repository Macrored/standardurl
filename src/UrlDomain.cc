/*

*/
#include "UrlDomain.h"

#include <string.h>

inline const char * RevMatch(const char * str, int len, const char *pattern)
{
	while(len > 0 && *pattern != 0)
	{
		len--;
		if(str[len] != *pattern)
		{
			break;
		}
		pattern++;
	}
	if(*pattern == 0)
	{
		return str + len;
	}
	else
	{
		return 0;
	}
}

inline const char * RevDot(const char * str, const char * dot)
{
	dot--;
	while(dot > str)
	{
		if(*dot == '.')
		{
			return dot + 1;
		}
		dot--;
	}
	return 0;
}

static const char* GetLastTwoParts(const char* url)
{
	if(url == 0)
	{
		return url;
	}
	int urllen = strlen(url);
	int dotcount = 0;
	for(int i=urllen - 1;i>=0;--i)
	{
		if(*(url + i) == '.')
		{
			dotcount++;
		}
		if(dotcount == 2)
		{
			return (url + i + 1);
		}
	}

	return url;
}

const char * GetDomainFromHost(const char * url)
{
	const char *result = NULL;
	if(url == 0)
		return 0;
	int urllen = strlen(url);
	if(urllen == 0)
	{
		return 0;
	}
	for(int i = 0; top_domain[i] != 0; i++)
	{
		const char * match;
		match = RevMatch(url, urllen, top_domain[i]);
		if(match != 0)
		{
			// �Զ���ͨ��������β���������ڶ��ڿ�ʼ�Ĳ�����Ϊ����
			result = RevDot(url, match);
			// ����������ڣ�����������������Ϊ������
			if(result == 0)
			{
				return url;
			}
			else
			{
				return result;
			}
		}
	}
	for(int i = 0; domain_map[i].top_domain != 0; i++)
	{
		// ������ļ�������������β������cn,tw,hk,uk,jp,il,nz,kr
		const char * match;
		match = RevMatch(url, urllen, domain_map[i].top_domain);
		if(match != 0)
		{
			for(int s = 0; domain_map[i].second_domain[s] != 0; s++)
			{
				const char * match2;
				match2 = RevMatch(url, urllen, domain_map[i].second_domain[s]);
				if(match2 != 0)
				{
					// λ���ڶ��������б��У����Ե��������ڿ�ʼ�Ĳ�����Ϊ����
					result = RevDot(url, match2);
					if(result == 0)
					{
						// ��������򷵻�����url
						return url;
					}
					else
					{
						return result;
					}
				}
			}
			// ���ڶ��������б��У�����������Ϊ����
			result = RevDot(url, match);
			// ����������ڣ�����������������Ϊ������
			if(result == 0)
			{
				return url;
			}
			else
			{
				return result;
			}
		}
	}
	for(int i = 0; top_country[i] != 0; i++)
	{
		// �Թ���������β
		const char * match;
		match = RevMatch(url, urllen, top_country[i]);
		if(match != 0)
		{
			for(int s = 0; general_2nd_domain[s] != 0; s++)
			{
				const char * match2;
				match2 = RevMatch(url, match - url, general_2nd_domain[s]);
				if(match2 != 0)
				{
					// �����ڶ���λ��general_2nd_domain�У�����������Ϊ����
					result = RevDot(url, match2);
					if(result == 0)
					{
						// ��������򷵻�����url
						return url;
					}
					else
					{
						return result;
					}
				}
			}
			// ���ڶ��������б��У�����������Ϊ����
			result = RevDot(url, match);
			// ����������ڣ�����������������Ϊ������
			if(result == 0)
			{
				return url;
			}
			else
			{
				return result;
			}
		}
	}
	// �Ȳ���ͨ��������β��Ҳ���Թ���������β��ȡ��������Ϊ���������������ڣ�������������Ϊ����
	return GetLastTwoParts(url);
}

/*
**test
int main()
{
  const char * url = "www.panguso.com";
  const char * re_url = GetDomainFromHost(url);
  printf("domain:%s\n",re_url);
  return 0;
}
*/
