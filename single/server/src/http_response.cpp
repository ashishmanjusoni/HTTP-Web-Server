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

void Response::addParameters(string key,string value)
{
if(key.size()==0 || value.size()==0) return;
this->parameters.insert(pair<string,string>(key,value));
}
string Response::getParameters(string key)
{
if(key.size()==0) return string("");
map<string,string>::iterator itr=this->parameters.find(key);
if(itr==this->parameters.end()) return string("");
return itr->second;
}

void Response::write(string content)
{
if(this->is_closed) return;
if(content.size()==0) return;
string replace_with;
size_t pos;
for(map<string,string>::iterator itr=this->parameters.begin();itr!=this->parameters.end();++itr)
{
replace_with.append("${").append(itr->first).append("}");
pos=content.find(replace_with);
if(pos!=string::npos) content.replace(pos,replace_with.size(),itr->second);
replace_with.clear();
}
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
