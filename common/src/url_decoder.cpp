#include<url_decoder>
#include<iostream>
#include<forward_list>
#include<string.h>
using namespace std;
using namespace wss;

const char * URLDecoder::decode(const char *urlStr)
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

