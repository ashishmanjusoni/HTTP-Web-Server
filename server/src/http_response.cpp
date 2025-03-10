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

void Response::write(const string &content)
{
write(content.c_str());
}

void Response::write(const char *content)
{
if(!this->is_closed) send(this->clientSocketDescriptor,content,strlen(content),0);
}
void Response::_close()
{
if(!this->is_closed) close(this->clientSocketDescriptor);
this->is_closed=true;
}
