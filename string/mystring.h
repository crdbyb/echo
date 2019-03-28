#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <iostream>
#include <cstdio>
#include <cstring>
#include <malloc.h>
using namespace std;
class Mystring{
    private:
            char *p;    //字符串
            size_t len; //长度
    public:
            Mystring(); //默认构造函数
            Mystring(const char *s = NULL); //通用构造函数
            Mystring(const Mystring &s);    //拷贝构造函数
            ~Mystring();    //析构函数
            friend ostream& operator<<(ostream &os, Mystring &s);       //友元，重载输出
            friend istream& operator>>(istream &is, Mystring &s);       //友元，重载输入
            const char* cstr() const;   //获取c字符串
            size_t size() const;        //获取长度
            Mystring operator+(const Mystring &s);
};


#endif