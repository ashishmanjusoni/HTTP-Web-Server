// requirement in Oct 2020
#include<map>
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#include<utils>
#include<http_request>
#include<http_response>
#include<expression_parser>
#include<http_linux_tcp_server>

using namespace std;
using namespace wss;
LinuxTCPServer::LinuxTCPServer(int port)
{
this->port=port;
}
LinuxTCPServer::~LinuxTCPServer()
{
}

void LinuxTCPServer::error404(void (*_error404)(Request &,Response &))
{
if(!_error404) return;
this->error_config.insert(pair<int,void(*)(Request &,Response &)>(404,_error404));
}
void LinuxTCPServer::error500(void (*_error500)(Request &,Response &))
{
if(!_error500) return;
this->error_config.insert(pair<int,void(*)(Request &,Response &)>(500,_error500));
}
void LinuxTCPServer::onRequest(string resource,void (*p2p)(Request &,Response &))
{
config.insert(pair<string,void (*)(Request &,Response&)>(resource,p2p));
}
void LinuxTCPServer::sendNotFound(Request &request, Response &response)
{
map<int,void(*)(Request &,Response &)>::iterator itr=this->error_config.find(404);
if(itr!=this->error_config.end()) 
{
void (*_error404)(Request &,Response &)=itr->second;
_error404(request,response);
}
}

void LinuxTCPServer::readClientSideResource(Request &request,Response &response)
{
FILE *file;
int size;
const char *e;
char responseBuffer[1025];
ExpressionParser *expressionParser;
string resource=request.getResource();
string mimeType=MIMEType::getMIMEType(resource);
resource.erase(0,1);
expressionParser=NULL;
const char *f=resource.c_str();
e=f+strlen(f);
e--;
while(e>f && *e!='.') e--;
if(e>f) if(strcmp(e,".sct")==0) expressionParser=new ExpressionParser;
file=fopen(resource.c_str(),"rb");
if(!file)
{
string error;
error.append(resource).append(" not found");
request.addParameter("error",error);
sendNotFound(request,response);
return;
}
fseek(file,0,SEEK_SET);
fseek(file,0,SEEK_END);
size=ftell(file);
fseek(file,0,SEEK_SET);
response.write("HTTP/1.1 200 OK\n");
response.write("Content-Type: ");
response.write(mimeType);
response.write("\n\n");
map<string,string> requestParameters=request.getRequestParameters();
while(1)
{
if(size<1024)
{
fread(responseBuffer,size,1,file);
responseBuffer[size]='\0';
if(expressionParser) response.write(expressionParser->parse(responseBuffer,&requestParameters,true));
else response.write(responseBuffer);
break;
}
else
{
fread(responseBuffer,1024,1,file);
responseBuffer[1024]='\0';
if(expressionParser) response.write(expressionParser->parse(responseBuffer,&requestParameters,false));
else response.write(responseBuffer);
}
size-=1024;
}
response._close();
fclose(file);
}

void LinuxTCPServer::start()
{
int serverSocketDescriptor,clientSocketDescriptor;
struct sockaddr_in serverSocketInformation,clientSocketInformation;
int byteExtracted,successCode;
unsigned int size;
char requestBuffer[8192];
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
cout<<"Failed to connect : socket not created"<<endl;
return;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->port);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
cout<<"Failed to connect : cannot bind socket to port "<<this->port<<endl;
close(serverSocketDescriptor);
return;
}
listen(serverSocketDescriptor,100);
size=(unsigned int)sizeof(clientSocketInformation);
while(1)
{
// start of infinite loop
cout<<" ==========================================="<<endl;
cout<<" Server is ready to accept request on port "<<this->port<<endl;
cout<<" ==========================================="<<endl;
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&size);
if(clientSocketDescriptor<0)
{
cout<<"Failed to process request"<<endl;
return;
}
byteExtracted=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
requestBuffer[byteExtracted]='\0';
cout<<"************************"<<endl;
cout<<"Request: "<<endl<<requestBuffer<<endl;
cout<<"************************"<<endl;
Request request=Request::parseRequest(requestBuffer);
request.setSocketDescriptor(clientSocketDescriptor);
request.setPort(this->port);
if(string("/shutdown")==request.getResource())
{
close(clientSocketDescriptor);
break;
}
Response response(clientSocketDescriptor);
while(1) // forward request infinite loop starts
{
if(request.getClientSideResource()=='Y')
{
cout<<"client side resource"<<endl;
readClientSideResource(request,response);
cout<<"client side resource send"<<endl;
break;
}
else
{
map<string,void (*)(Request &,Response &)>::iterator itr=this->config.find(request.getResource());
if(itr==config.end())
{
cout<<"Resource not found: send 404 html"<<endl;
sendNotFound(request,response);
break;
}
else
{
cout<<"Server Side resource"<<endl;
void (*_resource)(Request &,Response&);
_resource=itr->second;
_resource(request,response);
if(!request.getRequestForwardTo().empty())
{
request.setResource(request.getRequestForwardTo());
continue;
}
else break;
cout<<"Server Side resource send"<<endl;
}
}
}// forward request infinite loop ends
response._close();
cout<<"Close connection"<<endl;
//end of infinite loop
}
close(serverSocketDescriptor);
cout<<" ==========================================="<<endl;
cout<<" Shuting down the application. Thank you for using this application "<<endl;
cout<<" ==========================================="<<endl;
}

