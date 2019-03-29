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
    public:
            friend ostream& operator<<(ostream &os, Mystring &s);       //友元，重载输出
            friend istream& operator>>(istream &is, Mystring &s);       //友元，重载输入
    public:
            const char* cstr() const;   //获取c字符串
            size_t size() const;        //获取长度
            char &operator[] (int index); //重载[]
            bool empty();               //判断是否为空
    public:
            Mystring& operator+(const char *s);         //重载+ 普通字符串
            Mystring& operator+(const Mystring &s);     //重载+ 类对象          下同
    public:
            Mystring& operator=(const char *s);         //重载=
            Mystring& operator=(const Mystring &s);     //重载=
    public:
            Mystring& operator+=(const char *s);        //重载+=
            Mystring& operator+=(const Mystring &s);    //重载+=
    public:
            bool operator==(const char *s);             //重载==
            bool operator==(const Mystring &s);         //重载==
            bool operator!=(const char *s);             //重载!=
            bool operator!=(const Mystring &s);         //重载!=
    public:
            bool operator<(const char *s);              //重载<
            bool operator<(const Mystring &s);          //重载<
            bool operator>(const char *s);              //重载>
            bool operator>(const Mystring &s);          //重载>
    public:
            char* begin();
            char* end();
};


#endif