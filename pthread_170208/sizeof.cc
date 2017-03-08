#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>
using std::cout;
using std::endl;

void func(char str[100])
{
	cout<<sizeof(str)<<endl;		
}

int main(void)
{
	char str1[]="abc";
	char str2[]="abc";
	const char str3[]="abc";
	const char str4[]="abc";
	const char *str5="abc";
	const char *str6="abc";
	//char *str7="abc";
	//char *str8="abc";
	cout<<(str1==str2)<<endl;
	cout<<(str3==str4)<<endl;
	cout<<(str5==str6)<<endl;
	//cout<<(str7==str8)<<endl;
	
	char s[]="hello";
	char *p=s;
	int n=10;
	void *q=malloc(100);
	int *pp=NULL;
	cout<<sizeof(s)<<endl;
	cout<<sizeof(p)<<endl;
	cout<<sizeof(n)<<endl;
	cout<<sizeof(q)<<endl;
	cout<<sizeof(pp)<<endl;
	func(s);
	return 0;
}
