#include<response>
#include<string.h>
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
using namespace std;
using namespace wss;

Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->is_closed=false;
}

Response::~Response()
{
if(!this->is_closed) close(this->clientSocketDescriptor);
}

void Response::write(const string &content)
{
write(content.c_str());
}

void Response::write(const char *content)
{
if(!this->is_closed) send(this->clientSocketDescriptor,content,strlen(content),0);
//char *c=(char *)malloc(sizeof(char)*(strlen(content)+1));
//strcpy(c,content);
//this->itr=this->content_list.insert_after(this->itr,c);
}

/*
forward_list<const char *> Response::getContent()
{
forward_list<const char *> content_list;
forward_list<const char *>::iterator _itr=content_list.before_begin();
for(this->itr=this->content_list.begin();this->itr!=this->content_list.end();++this->itr)
{
char * _data=(char*)malloc(sizeof(char)*(strlen(*(this->itr))+1));
strcpy(_data,*(this->itr));
_itr=content_list.insert_after(_itr,_data);
}
return content_list;
}
*/
void Response::_close()
{
if(!this->is_closed) close(this->clientSocketDescriptor);
this->is_closed=true;
}
