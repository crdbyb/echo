#ifndef  MYSTRING
#define  MYSTRING
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <iterator>
using namespace std;

class MyString
{
    friend ostream& operator<<(ostream &out, const MyString &s);
    friend istream& operator>>(istream &in, MyString &s);
    
private: 
    int m_len;  //字符串长度
    char *m_p;  //字符串指针
public:
    MyString();
    MyString(const char *p);
    MyString(const MyString& s);
    ~MyString();
    typedef char* myiterator;   //定义一个char×迭代器
    const  char* c_str();  //返回c类型指针
    MyString(iterator begin, iterator end);
    MyString& operator=(const char* p); 
    MyString& operator=(const MyString &s);
    MyString& swap(const char *p);
    MyString& swap(const String &s);
    char& operator[](int index);
    bool operator==(const char* p);
    bool operator==(const MyString &s);
    bool operator!=(const char* p);
    bool operator!=(const MyString &s);
    bool operator>(const char *p) ;
    bool operator>(const MyString &sj) ;
    bool operator<(const char *p) ;
    bool operator<(const MyString &s) ;
    bool empty();
    int length();
    myiterator erase(int pos, int len);  //从pos处删除长度len的字符
    
    iterator(const char *p_test = nullptr) : test(p_test)
    {
    }
    ~iterator()
    {
    }
    char operator *()
    {
       return test[0];
    }
    iterator& operator++()
    {
         test++;
         return *this;
    }
    iterator operator++(int)
    {
         const  char * g_test = test;
         test++;
         return iterator(g_test);
    }
    iterator& operator--()
    {
         test--;
         return *this;
    }
    iterator operator--(int)
    {
          const char * g_test = test;
          test--;
          return iterator(g_test);
    }
    iterator& operator=(const iterator &arg)
    {
          test = arg.test;
          return * this;
    }
    iterator begin() const
    {
        return iterator(temp);
    }
    iterator end() const
    {
        return iterator(temp+m_temp);
    }

};
#endif