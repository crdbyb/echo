#include "mystring.h"
#include "string.cpp"
#include <iostream>
using namespace std;
int main(){
	Mystring s1(" sss");
	Mystring s2(" www");
	Mystring s3 = s1;
	Mystring s4 = s1 + s2;
	cout << s3;
	cout << s4;
	if(s1 > s2){
		cout << "1" << endl;
	}
	else{
		cout << "2" << endl;
	}
	cout << s2.size() << endl;
	cout << s1[1] << endl;
}
