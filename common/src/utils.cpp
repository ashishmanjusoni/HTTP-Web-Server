// requirement in Oct 2020
#include<iostream>
#include<utils>
#include<mime_type>
using namespace std;

bool wss::extensionEquals(const char *str1,const char *str2)
{
const char *e,*f;
char a,b;
if(!str1 || !str2) return false;
e=str1;
f=str2;
while(*e && *f)
{
a=*e;
b=*f;
if(a>=65 && a<=91) a+=32;
if(b>=65 && b<=91) b+=32;
if(a!=b) return 0;
e++;
f++;
}
return *e==*f;
}

char wss::isClientSideResource(const char *resource)
{
const char *e;
e=resource+strlen(resource)-1;
while(e>=resource && *e!='.') e--;
if(e<=resource) return 'N';
return 'Y';
/*
e++;
string str;
while(*e)
{
str.push_back(*e);
e++;
}
if(MIMEType::contains(str)) return 'Y';
return 'N';
*/
}
