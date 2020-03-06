/*
* Copyright (c) 2011-2012
* @version 1.0.0
* @author Zhai Zhouwei
* @email nuoline@gmail.com
* @date 2012-5-29
* @description URL�����Լ���һ������ӿ�ͷ�ļ�
*/
#ifndef _ONE_URL_H_
#define _ONE_URL_H_

#include "UrlParse.h"

#include <string>
#include <vector>
using namespace std;

extern bool IsIp;

//��ӿڣ���һ����ͬʱ������URL�������
class oneurl {
  public:
    //���캯��
    oneurl();
  
    //��������
    ~oneurl();
    
    //URL��һ������ӿ�
    string CNormalize(const string str_in, const int codetype = 0);
    
    //URL��һ��uniq
    //string CNormalizeUniq(const string str_in, const int codetype = 0);
    
    //URL�����ӿ�
    bool ParseUrl(const string str_in);
    
    bool Parse(const string &str_in);
    
    //scheme
    string GetScheme() const {
      return ComponentString(parsed_.scheme);
    }
    
    //username
    string GetUsername()const {
      return ComponentString(parsed_.username);
    }
      
    //password
    string GetPassword() const {
      return ComponentString(parsed_.password);
    }
    
    //host
    string GetHost() const {
      string strhost = ComponentString(parsed_.host);
      while(strhost.compare(0,8,"www.www.") == 0)
         strhost = strhost.substr(4);
      return strhost;
    }
    
    //port
    string GetPort() const {
      return ComponentString(parsed_.port);
    }
    
    //path
    string GetPath() const {
      return ComponentString(parsed_.path);
    }
    
    //query
    string GetQuery() const {
      return ComponentString(parsed_.query);
    }
    
    //ref
    string GetRef() const {
      return ComponentString(parsed_.ref);
    }
    
    //�Ƿ�̬ҳ��
    bool IsDynamic();
    
    //��ȡ����
    string GetDomain() const;
    
    //·�����
    int PathDepth();
    
    //

  private:
    // ��һ����ĵ�url
    string spec_;
    //������Ľ��
    Parsed parsed_;
    //
    string ComponentString(const Component& comp) const 
     {    
         if (comp.len <= 0)      
            return string();
        return string(spec_, comp.begin, comp.len);
     }
     
};

//�з��ַ�������
void Split(const string str_value,const string str_spliter,vector<string>& v_str_list);

//Ԥ����URL,����scheme,���http://
std::string PreProcess(const char* url,int url_len);
//
void RemoveSurplusSlash(const char* path,char* pc_path,int len);

//�����ӿڣ�Ч�ʸ�
string Normalize(const char* spec,int spec_len,int codetype = 0);
#endif
