#include<url_formatter>
#include<iostream>
#include<forward_list>
#include<string.h>
using namespace std;
using namespace wss;
const char * URLFormatter::decode(const char *urlStr)
{
int size;
forward_list<char> list;
const char *e;
char *_urlStr,*f;
char _charactor[4];
forward_list<char>::iterator itr=list.before_begin();
if(!urlStr || strlen(urlStr)<=0) return NULL;
e=urlStr;
size=0;
while(*e)
{
if(*e=='+') itr=list.insert_after(itr,' ');
else if(*e=='%')
{
_charactor[0]=*e;
e++;
_charactor[1]=*e;
e++;
_charactor[2]=*e;
_charactor[3]='\0';
if(strcmp(_charactor,"%20")==0) itr=list.insert_after(itr,' ');
if(strcmp(_charactor,"%3A")==0) itr=list.insert_after(itr,':');
if(strcmp(_charactor,"%2F")==0) itr=list.insert_after(itr,'/');
if(strcmp(_charactor,"%3F")==0) itr=list.insert_after(itr,'?');
if(strcmp(_charactor,"%23")==0) itr=list.insert_after(itr,'#');
if(strcmp(_charactor,"%5B")==0) itr=list.insert_after(itr,'[');
if(strcmp(_charactor,"%5D")==0) itr=list.insert_after(itr,']');
if(strcmp(_charactor,"%40")==0) itr=list.insert_after(itr,'@');
if(strcmp(_charactor,"%21")==0) itr=list.insert_after(itr,'!');
if(strcmp(_charactor,"%24")==0) itr=list.insert_after(itr,'$');
if(strcmp(_charactor,"%26")==0) itr=list.insert_after(itr,'&');
if(strcmp(_charactor,"%27")==0) itr=list.insert_after(itr,'\'');
if(strcmp(_charactor,"%28")==0) itr=list.insert_after(itr,'(');
if(strcmp(_charactor,"%29")==0) itr=list.insert_after(itr,')');
if(strcmp(_charactor,"%2A")==0) itr=list.insert_after(itr,'*');
if(strcmp(_charactor,"%2B")==0) itr=list.insert_after(itr,'+');
if(strcmp(_charactor,"%2C")==0) itr=list.insert_after(itr,',');
if(strcmp(_charactor,"%3B")==0) itr=list.insert_after(itr,';');
if(strcmp(_charactor,"%3D")==0) itr=list.insert_after(itr,'=');
if(strcmp(_charactor,"%25")==0) itr=list.insert_after(itr,'%');
}
else itr=list.insert_after(itr,*e);
e++;
size++;
}
cout<<"Size: "<<size<<endl;
_urlStr=(char*)malloc(sizeof(char)*(size+1));
for(f=_urlStr,itr=list.begin();itr!=list.end();++itr,f++) *f=*itr;
*f='\0';
return (const char *)_urlStr;
}

const char * URLFormatter::encode(const char *urlStr)
{
int size;
forward_list<char *> list;
const char *e;
char *_urlStr,*f;
forward_list<char*>::iterator itr=list.before_begin();
if(!urlStr || strlen(urlStr)<=0) return NULL;
e=urlStr;
size=0;
while(*e)
{
if(*e==' ') 
{
f=(char*)malloc(sizeof(char)*2);
strcpy(f,"+");
itr=list.insert_after(itr,f);
size++;
e++;
continue;
}
if(*e==':') 
{
f=(char *)malloc(sizeof(char)*4);
strcpy(f,"%3A");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='/')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%2F");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='?')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%3F");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='#')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%23");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='[')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%5B");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e==']')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%5D");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;

}
if(*e=='@')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%40");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='!')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%21");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='$')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%24");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='&')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%26");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='\'')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%27");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='(')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%28");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e==')')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%29");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='*')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%2A");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='+')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%2B");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e==',')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%2C");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e==';')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%3B");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='=')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%3D");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
if(*e=='%')
{
f=(char*)malloc(sizeof(char)*4);
strcpy(f,"%25");
itr=list.insert_after(itr,f);
size+=3;
e++;
continue;
}
f=(char*)malloc(sizeof(char)*2);
f[0]=*e;
f[1]='\0';
itr=list.insert_after(itr,f);
e++;
size++;
}
_urlStr=(char*)malloc(sizeof(char)*(size+1));
*_urlStr='\0';
for(itr=list.begin();itr!=list.end();++itr) 
{
strcat(_urlStr,*itr);
free(*itr);
}
return (const char*) _urlStr;
}
