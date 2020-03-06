/**
* Copyright (c) 2011-2012
* @version 1.0.0
* @author Zhai Zhouwei
* @email nuoline@gmail.com
* @date 2012-5-29
* @description URL归一化测试
*/
#include <iostream>
#include <string>
#include <string.h>

#include "Url.h"
using namespace std;

struct UrlCase {
	const char* input;
	const char* output;
	const char* expected;
} cases[] = {
  {"        www.panguso.cOM/", "","http://www.panguso.com/"},
  {"			www.PANGUSO.cn", "","http://www.panguso.com"},
  {"http:////////www.panguso.com", "","http://www.panguso.com"},
  {"http://WWW.pANGUSO.cOM","","http://www.panguso.com"},
  {"http://%62%61%6f%62%61%6f%31%37%38.com/","","http://baobao178.com/"},
  {"http://192.0x00A80001", "","192.168.0.1"},
  {"0.0.0xFFFF","","0.0.255.255"},
  {"http:\\\\www.panguso.com\\nuoline", ""},
  {"http://www.baidu.com/index.php?a=中国","",""},
  {"http://www.www.baidu.com","",""},
};

int main()
{
	cout << "wchar_t size:" << sizeof(wchar_t) << endl;
	for (size_t i = 0; i < sizeof(cases) / sizeof(UrlCase); i++) {

		string url = cases[i].input;
		//const char* url = cases[i].input;
		oneurl curl;
		//curl.Parse(url);
		url = PreProcess(url.c_str(), url.length());
		string str_test = curl.CNormalize(url);
		//string str_test = Normalize(url.c_str(),url.length());
		cout << url << " -> " << str_test << endl;
	}
	return 0;
}
