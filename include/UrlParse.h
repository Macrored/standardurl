/**
* Copyright (c) 2011-2012
* @version 1.0.0
* @author Zhai Zhouwei
* @email nuoline@gmail.com
* @date 2012-4-26
* @description URL��������ͷ�ļ�
*/
#ifndef _PANGU_URL_PARSE_H_
#define _PANGU_URL_PARSE_H_

#include <string>
#include "string16.h"

/*���ڷ���URL���Ӳ��ֵĽṹ��*/
struct Component{
  Component() : begin(0), len(-1) {}
  // ���ι��캯��: offset �� length.
  Component(int b, int l) : begin(b), len(l) {}
  int end() const {
    return begin + len;
  }
  // �Ƿ���Ч
  bool is_valid() const {
    return (len != -1);
  }
  // empty or invalid.
  bool is_nonempty() const {
    return (len > 0);
  }
  //���ù���
  void reset() {
    begin = 0;
    len = -1;
  }
  bool operator==(const Component& other) const {
    return begin == other.begin && len == other.len;
  }
  int begin;  // ��¼�Ӳ��ֵ�ƫ����
  int len;    // ���ȣ���ʼ��Ϊ-1
};
// Helper that returns a Component created with the given begin and ending
// points. The ending point is non-inclusive.
inline Component MakeRange(int begin, int end) {
  return Component(begin, end - begin);
}

/*����URL�Ľṹ��*/
struct Parsed {
  // ʶ��ͬ��URL�Ӳ���
  enum ComponentType {
    SCHEME,
    USERNAME,
    PASSWORD,
    HOST,
    PORT,
    PATH,
    QUERY,
    REF,
  };
  //���캯��
  Parsed();
  Parsed(const Parsed&);
  ~Parsed();

  // Returns the length of the URL (the end of the last Component).
  int Length() const;

  //�����Ӳ���ǰ����ַ�����include_delimiterΪ1ʱ������delimiter
  int CountCharactersBefore(ComponentType type,bool include_delimiter) const;

  Component scheme;

  Component username;

  Component password;

  Component host;

  Component port;

  Component path;

  Component query;

  Component ref;
};

inline bool IsPortDigit(char16 ch) {  return ch >= '0' && ch <= '9';}

inline bool IsURLSlash(char16 ch) {
  return ch == '/' || ch == '\\';
}

// Returns true if we should trim this character from the URL because it is a
// space or a control character.
inline bool ShouldTrimFromURL(char16 ch) {
  return ch <= ' ';
}

bool IsAuthorityTerminator(char16 ch);

inline void TrimURL(const char* spec, int* begin, int* len) {
  // Strip leading whitespace and control characters.
  while (*begin < *len && ShouldTrimFromURL(spec[*begin]))
    (*begin)++;
  // Strip trailing whitespace and control characters.
  while (*len > *begin && ShouldTrimFromURL(spec[*len - 1]))
    (*len)--;
}

// Counts the number of consecutive slashes starting at the given offset
// in the given string of the given length.
inline int CountConsecutiveSlashes(const char *str,int begin_offset, int str_len) {
  int count = 0;
  while (begin_offset + count < str_len &&
         IsURLSlash(str[begin_offset + count]))
    ++count;
  return count;
}

//Helper functions -----------------------------------------------------------
//The 8-bit version requires UTF-8 encoding.
bool ExtractScheme(const char* url, int url_len, Component* scheme);

void ParseAuthority(const char* spec,
                             const Component& auth,
                             Component* username,
                             Component* password,
                             Component* hostname,
                             Component* port_num);

// The return value will be a positive integer between 0 and 64K, or one of
// the two special values below.
enum SpecialPort { PORT_UNSPECIFIED = -1, PORT_INVALID = -2 };
int ParsePort(const char* url, const Component& port);

// Extracts the range of the file name in the given url. The path must
// The 8-bit version requires UTF-8 encoding.
void ExtractFileName(const char* url,
                              const Component& path,
                              Component* file_name);
// Extract the first key/value from the range defined by |*query|. Updates
// |*query| to start at the end of the extracted key/value pair. This is
// designed for use in a loop: you can keep calling it with the same query
// object and it will iterate over all items in the query.
// If no key/value are found |*key| and |*value| will be unchanged and it will
// return false.
bool ExtractQueryKeyValue(const char* url,Component* query,Component* key,Component* value);

//����URL����ں���
void ParseStandardURL(const char* url, int url_len, Parsed* parsed);

#endif
