#include "mystring.h"
Mystring::Mystring(){
    this->p = new char[1];
    *(this->p) = '\0';
    len = 0;
}

Mystring::Mystring(const char *s){
    if(!s){
        this->p = new char[1];
        *(this->p) = '\0';
        len = 0;
    }
    else{
        len = strlen(s);
        p = new char[len + 1];
        strcpy(p,s);
    }
}

Mystring::Mystring(const Mystring &s){
    len = strlen(s.p);
    p = new char[len + 1];
    strcpy(p,s.p);
}

Mystring::~Mystring(){
    delete[] this->p;
    len = 0;
}

ostream& operator<<(ostream &os, Mystring &s){
    os << s.p;
    return os;
}

istream& operator>>(istream &is, Mystring &s){
    char n[1000] = {0};
    bzero(n,sizeof(n));
    is >> n;
    s.len = strlen(n);
    s.p = new char[s.len + 1];
    strcpy(s.p,n);
}

inline const char* Mystring::cstr() const{
    return p;
}

inline size_t Mystring::size() const{
    return len;
}

Mystring Mystring::operator+(const Mystring &s){
    Mystring a;
    a.p = new char[strlen(this->p) + strlen(s.p) + 1];
    strcpy(a.p, this->p);
    strcat(a.p, s.p);
    return a;
}