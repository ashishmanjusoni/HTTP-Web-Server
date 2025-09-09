// requirement in Oct 2020
#include<map>
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<utils>
#include<http_request>
#include<http_response>
#include<http_linux_tcp_server>
#include<stdlib.h>
#include<thread>
#include<forward_list>
using namespace std;
using namespace wss;

LinuxTCPServer::LinuxTCPServer(int port)
{
this->port=port;
this->id=1;
this->shutdown=0;
}

LinuxTCPServer::~LinuxTCPServer()
{

}

void LinuxTCPServer::onRequest(string resource,void (*p2p)(Request &,Response &))
{
config.insert(pair<string,void (*)(Request &,Response&)>(resource,p2p));
}

void LinuxTCPServer::readClientSideResource(Request &request,Response &response)
{
FILE *file;
int size;
char responseBuffer[1025];
string resource=request.getResource();
string mimeType=MIMEType::getMIMEType(resource);
resource.erase(0,1);
file=fopen(resource.c_str(),"rb");
if(!file)
{
string error;
error.append(resource).append(" not found");
request.addParameter("error",error);
response.write("HTTP/1.1 404 NOT_FOUND\n");
response.write("Content-Type: ");
response.write(mimeType);
response.write("\n\n");
response.write("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>"); 
response.write("<title>404 Page Not Found</title></head><body><h1 style='color:Red;'>NOT FOUND 404</h1><h1 style='color:Red;'>");
response.write(error);
response.write("</h1></body></html>");
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
response.write(responseBuffer);
break;
}
else
{
fread(responseBuffer,1024,1,file);
responseBuffer[1024]='\0';
response.write(responseBuffer);
}
size-=1024;
}
response._close();
fclose(file);
}

void LinuxTCPServer::processClientRequest(int id, int clientSocketDescriptor, Request request)
{
Response response(clientSocketDescriptor);
while(1) // forward request infinite loop starts
{
if(request.getClientSideResource()=='Y')
{
cout<<"client side resource"<<endl;
////////////////
FILE *file;
int size;
char responseBuffer[1025];
string resource=request.getResource();
string mimeType=MIMEType::getMIMEType(resource);
resource.erase(0,1);
file=fopen(resource.c_str(),"rb");
if(!file)
{
string error;
error.append(resource).append(" not found");
request.addParameter("error",error);
response.write("HTTP/1.1 404 NOT_FOUND\n");
response.write("Content-Type: ");
response.write(mimeType);
response.write("\n\n");
response.write("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>"); 
response.write("<title>404 Page Not Found</title></head><body><h1 style='color:Red;'>NOT FOUND 404</h1><h1 style='color:Red;'>");
response.write(error);
response.write("</h1></body></html>");
this->completed_requests.push(id);
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
response.write(responseBuffer);
break;
}
else
{
fread(responseBuffer,1024,1,file);
responseBuffer[1024]='\0';
response.write(responseBuffer);
}
size-=1024;
}
response._close();
fclose(file);
//////////////////
//readClientSideResource(request,response);
cout<<"client side resource send"<<endl;
break;
}
else
{
map<string,void (*)(Request &,Response &)>::iterator itr=this->config.find(request.getResource());
if(itr==config.end())
{
cout<<request.getResource()<<" not found"<<endl;
cout<<"Resource not found: send 404 html"<<endl;
request.addParameter("error","The resource is not found");
request.forward("error_page.sct");
break;
}
else
{
cout<<"Server Side resource"<<endl;
void (*_resource)(Request &,Response&);
_resource=itr->second;
cout<<"call resource "<<request.getResource()<<endl;
_resource(request,response);
if(!request.getRequestForwardTo().empty())
{
cout<<"forward request "<<request.getRequestForwardTo()<<endl;
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
this->completed_requests.push(id);
}

void LinuxTCPServer::release_thread_after()
{
cout<<"release_thread_after invoked"<<endl;
int id;
map<int,thread*>::iterator itr;
thread *t;
while(!this->shutdown)
{
while(!completed_requests.empty())
{
id=this->completed_requests.front();
this->completed_requests.pop();
itr=this->thread_pool.find(id);
if(itr==this->thread_pool.end()) this->completed_requests.push(id);
else
{
t=itr->second;
if(t->joinable())
{
t->join();
delete t;
}
this->thread_pool.erase(itr);
}
}
}
cout<<"releaose_thread_after completed"<<endl;
}

void LinuxTCPServer::processShutdownTCPServerRequest()
{
int id;
thread *t;
map<int,thread*>::iterator itr;
while(!this->thread_pool.empty())
{
while(!this->completed_requests.empty())
{
id=completed_requests.front();
completed_requests.pop();
itr=this->thread_pool.find(id);
if(itr==this->thread_pool.end()) completed_requests.push(id);
else
{
t=itr->second;
if(t->joinable())
{
t->join();
delete t;
}
this->thread_pool.erase(itr);
}
}
}
}

void LinuxTCPServer::start()
{
int serverSocketDescriptor,clientSocketDescriptor;
struct sockaddr_in serverSocketInformation,clientSocketInformation;
int successCode;
unsigned int size;
thread *thread_for_process_request;
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
thread *thread_for_release_completed_requests=new thread(&LinuxTCPServer::release_thread_after,this);
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
char requestBuffer[8192];
int byteExtracted;
byteExtracted=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
requestBuffer[byteExtracted]='\0';
cout<<"************************"<<endl;
cout<<"Request: "<<endl<<requestBuffer<<endl;
cout<<"************************"<<endl;
Request request=Request::parseRequest(requestBuffer);
request.setSocketDescriptor(clientSocketDescriptor);
//request.setPort(port);
if("/shutdown"==request.getResource())
{
this->shutdown=1;
break;
}
thread_for_process_request=new thread(&LinuxTCPServer::processClientRequest,this,id,clientSocketDescriptor,request);
this->thread_pool.insert(pair<int,thread *>(this->id,thread_for_process_request));
this->id++;
//end of infinite loop
}
processShutdownTCPServerRequest();
if(thread_for_release_completed_requests->joinable())
{
thread_for_release_completed_requests->join();
delete thread_for_release_completed_requests;
}
close(serverSocketDescriptor);
cout<<" ==========================================="<<endl;
cout<<" Shuting down the application. Thank you for using this application "<<endl;
cout<<" ==========================================="<<endl;
}
