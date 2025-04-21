#include<http_response>
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

void Response::write(string content)
{
if(this->is_closed) return;
if(content.size()==0) return;
send(this->clientSocketDescriptor,content.c_str(),content.size(),0);
}

void Response::write(const char *content)
{
write(string(content));
}

void Response::_close()
{
if(!this->is_closed) close(this->clientSocketDescriptor);
this->is_closed=true;
}
