#include<url_decoder>
#include<http_request>
#include<mime_type>
#include<cstring>
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<utils>
using namespace std;
using namespace wss;

Request::Request()
{
this->socketDescriptor=0;
this->port=8080;
this->host="127.0.0.1";
this->method="";
this->resource="";
this->clientSideResource='\0';
this->forwardTo="";
}

Request::~Request()
{
}

void Request::setInt(string key,int value)
{
this->int_map.insert(pair<string,int>(key,value));
}

int Request::getInt(string key)
{
map<string,int>::iterator itr=this->int_map.find(key);
return itr->second;
}

void Request::setPort(int port)
{
this->port=port;
}

void Request::setSocketDescriptor(int socketDescriptor)
{
this->socketDescriptor=socketDescriptor;
}

void Request::setMimeType(const string)
{
this->mimeType=mimeType;
}
string Request::getMimeType()
{
return this->mimeType;
}

void Request::setMethod(const string method)
{
this->method=method;
}
string Request::getMethod()
{
return this->method;
}
void Request::setResource(const string resource)
{
this->resource=resource;
this->clientSideResource=isClientSideResource(resource.c_str());
}
string Request::getResource()
{
return this->resource;
}

void Request::setClientSideResource(char clientSideResource)
{
this->clientSideResource=clientSideResource;
}

char Request::getClientSideResource()
{
return this->clientSideResource;
}

void Request::add(string key,string value)
{
if(key.empty() || value.empty()) return;
this->inputData.insert(pair<string,string>(key,value));
}
string Request::get(string key)
{
if(key.empty() || this->inputData.empty()) return string("");
map<string,string>::iterator itr=this->inputData.find(key);
if(itr==this->inputData.end()) return string("");
return itr->second;
}

void Request::parseGETResource(const char *resource)
{
const char *e;
string key,value;
if(!resource) return;
e=resource;
this->resource.push_back('/');
while(*e && *e!='?')
{
this->resource.push_back(*e);
e++;
}
if(!*e) return;
e++;
if(!*e) return;
const char * decodeUrl=URLDecoder::decode(e);
e=decodeUrl;
while(*e)
{
while(*e && *e!='=')
{
key.push_back(*e);
e++;
}
e++;
while(*e && *e!='&')
{
value.push_back(*e);
e++;
}
this->add(key,value);
key.clear();
value.clear();
if(!*e) break;
e++;
}
}

Request Request::parseRequest(const char *bytes)
{
char resourceBuffer[1001];
const char *e;
char *a;
Request request;
if(bytes)
{
for(e=bytes;*e && *e!=' ';e++) request.method.push_back(*e);
e+=2;
for(a=resourceBuffer;*e && *e!=' ';e++,a++) *a=*e;
*a='\0';
if(resourceBuffer[0]=='\0')
{
request.resource="/";
request.clientSideResource='N';
request.setMimeType("");
}
else
{
if(request.method=="GET") request.parseGETResource(resourceBuffer);
request.setMimeType(MIMEType::getMIMEType(request.resource));
request.setClientSideResource(isClientSideResource(request.resource.c_str()));
}
}
return request;
}

bool Request::containsKey(string key)
{
if(key.empty() || this->inputData.empty()) return false;
map<string,string>::iterator itr=this->inputData.find(key);
if(itr==this->inputData.end()) return false;
return true;
}

void Request::forward(string _forwardTo)
{
if(_forwardTo.empty()) return;
if(_forwardTo[0]!='/') _forwardTo.insert(0,"/");
this->forwardTo=_forwardTo;
}

string Request::getRequestForwardTo()
{
return this->forwardTo;
}
