#include "mystring.h"
#include <iostream>

using namespace std;
typedef char* myiterator;
ostream& operator<<(ostream &out, const MyString &s)
{
    cout << s.m_p << endl;
    return out;
}

istream& operator>>(istream &in, MyString &s)
{
    if(s.m_p != NULL)
    {
        delete s.m_p;
        s.m_p = NULL;
        s.m_len = 0;
    }
    char c[1000] = {0};
    bzero(c,sizeof(c));

    cin >> c;

    s.m_p = new char[strlen(c) + 1];
    s.m_len = strlen(c);
    strcpy(s.m_p,c);
    return in;
}

MyString::MyString()
{
    m_p = NULL;
    m_len = 0;
}


MyString::MyString(const char *p)
{
    m_p = new char[strlen(p) + 1];
    m_len = strlen(p);
    strcpy(m_p,p);

}

MyString::MyString(const MyString& s)
{
    m_p = new char[strlen(s.m_p) + 1];
    m_len = strlen(s.m_p);
    strcpy(m_p,s.m_p);
}

MyString::~MyString()
{
    if(m_p != NULL)
    {   
        delete m_p;
        m_p = NULL;
        m_len = 0;
        return;
    }
    m_p = NULL;
    m_len = 0;
}


const char* MyString::c_str()
{
    return m_p;
}


MyString& MyString::operator=(const char* p)
{
    if(m_p != NULL)
    {   
        delete m_p;
        m_p = NULL;
        m_len = 0;
    } 
    m_p = new char[strlen(p) + 1];
    m_len = strlen(p);
    strcpy(m_p,p);
}


MyString& MyString::operator=(const MyString &s)
{
    if(s.m_p != NULL)
    {
        m_p = NULL;
        m_len = 0;
    }
    m_p = new char[strlen(s.m_p) + 1];
    m_len = strlen(s.m_p);
    strcpy(m_p,s.m_p);
}


bool MyString::operator==(const char* p)
{
    if(strcmp(m_p,p) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyString::operator==(const MyString &s)
{
    if(strcmp(m_p,s.m_p) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool MyString::operator!=(const char* p)
{
    if(strcmp(m_p,p) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MyString::operator!=(const MyString &s)
{
    if(strcmp(m_p,s.m_p) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

MyString MyString::operator+(const MyString& s1)
{
    char c[1000] = { 0 };
    bzero(c,sizeof(c));
    strcpy(c,m_p);
    strcpy(&c[strlen(c)],s1.m_p);
    
    MyString sss(c);
    return sss;
}

myiterator MyString::erase(int pos, int len)
{
    if(pos + len > m_len)
    {
        cout << "长度太长" << endl;
        return (myiterator)-1;
    }
    char c[1000];
    bzero(c,sizeof(c));
    for(int i = 0;i < pos;i++)
    {
        c[i] = m_p[i];
    }
    for(int i = pos;i < m_len;i++)
    {
        c[i] = m_p[i + len];
    }

    if(m_p != NULL)
    {
        delete m_p;
        m_p = NULL;
        m_len = 0;
    }

    m_p = new char[strlen(c) + 1];
    m_len = strlen(c);
    strcpy(m_p,c);
    return &m_p[pos];
}
bool MyString::operator>(const char *p)
{
   if(strcmp(temp,test) > 0 )
   {
       return true;
   }
   return false;
}
bool MyString::operator>(const String &s)
{
    if (strcmp(temp, obj.temp) > 0)
    {
        return true;
    }
    return false;
}
bool MyString::operator<(const char *p)
{
    if (strcmp(test,temp) > 0)
    {
        return true;
    }
    return false;
}
bool MyString::operator<(const String &s)
{
    if (strcmp(obj.temp, temp) > 0)
    {
        return true;
    }
    return false;
}
bool MyString::empty()
{
    if(temp == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int MyString::length()
{
    return m_temp;
}
MyString &MyString::swap(const char *p)
{
   char p_test[100];
   int size = strlen(p);
   strcpy(p_test,test);
   p_test[size] = '\0';
   strcpy(temp,p_test);
   return * this;
}
MyString & MyString::swap(const String &s)
{
    char p_test[100],g_test[100];
    int size = strlen(obj.temp);
    strcpy(p_test, obj.temp);
    strcpy(g_test,temp);
    p_test[size] = '\0';
    g_test[m_temp] ='\0';
    strcpy(temp, p_test);
    strcpy(obj.temp,g_test);
    return *this;
}

