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
    cout << s.p << endl;
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

inline char& Mystring::operator[](int n){
	if(n >= len){
		return p[len-1];
	}
	else{
		return p[n];
	}
}

Mystring& Mystring::operator+(const char *s){
	char *q = p;
	len = strlen(p) + strlen(s);
	p = new char[len + 1];
	strcpy(p,q);
	strcat(p,s);
	delete[] q;
	return *this;
}

Mystring& Mystring::operator+(const Mystring &s) {
    strcat(this->p,s.p);
    return *this;
}

Mystring& Mystring::operator=(const char *s){
	if(p != NULL){
		delete[] p;
		p = NULL;
	}
	len = strlen(s);
	p = new char[len + 1];
	strcpy(p,s);
	return *this;
}

Mystring& Mystring::operator=(const Mystring &s){
    if(this == &s){
        return *this;
    }
    if(p != NULL){
        delete[] p;
        p = NULL;
    }
    len = s.len;
    p = new char[len + 1];
    strcpy(p,s.p);
    return *this;
}

Mystring& Mystring::operator+=(const char *s){
	char *q = p;
	len = strlen(p) + strlen(s);
	p = new char[len + 1];
	strcpy(p,q);
	strcat(p,s);
	delete[] q;
	return *this;
}

Mystring& Mystring::operator+=(const Mystring &s){
	*this = *this + s.p;
	return *this;
}

bool Mystring::operator==(const char *s){
	if(strcmp(p,s) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool Mystring::operator==(const Mystring &s){
	if(strcmp(p,s.p) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool Mystring::operator!=(const char *s){
	return !(*this == s);
}

bool Mystring::operator!=(const Mystring &s){
	return !(*this == s);
}

bool Mystring::operator<(const char *s){
	if(strcmp(p,s) < 0){
		return true;
	}
	return false;
}

bool Mystring::operator<(const Mystring &s){
	if(strcmp(p,s) < 0){
		return true;
	}
	return false;
}

bool Mystring::operator>(const char *s){
	if(strcmp(p,s) > 0){
		return true;
	}
	return false;
}

bool Mystring::operator>(const Mystring &s){
	if(strcmp(p,s) > 0){
		return true;
	}
	return false;
}

bool Mystring::empty(){
	bool m = false;
	if(this->size() <= 0){
		m = true;
	}
	return m;
}

char* Mystring::begin(){
	return p;
}

char* Mystring::end(){
	return p + len;
}