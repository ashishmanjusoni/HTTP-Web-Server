// requirement in Oct 2020
#include<forward_list>
#include<iostream>
#include<tm_request>
#include<tm_response>
#include<tm_websocket>
using namespace std;
using namespace wss;

void welcomePage(Request &request,Response &response)
{
char responseBuffer[1026],headerBuffer[8192];
int size,e,len;
FILE *file;
size=0;
file=fopen("welcome.html","rb");
fseek(file,0,SEEK_END);
size=ftell(file);
fseek(file,0,SEEK_SET);
sprintf(headerBuffer,"HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %d\nConnection: Keep-Alive\nKeep-Alive: timeout=5, max=1000\n\n",request.getMimeType().c_str(),size);
response.setHeader(string(headerBuffer));
response.setContentLength(size);
string content="";
while(1)
{
if(size<1024)
{
fread(responseBuffer,size,1,file);
content.append(responseBuffer);
break;
}
else
{
fread(responseBuffer,1024,1,file);
content.append(responseBuffer);
}
size-=1024;
}
response.setContent(content);
cout<<"Welcome page"<<endl;
fclose(file);
}

forward_list<string> * findAllStudentsName()
{
string name;
char c;
forward_list<string> * list = new forward_list<string>;
forward_list<string>::iterator itr=list->before_begin();
FILE * file;
file=fopen("student.data","r");
if(!file) return list;
while(1)
{
c=fgetc(file);
if(feof(file)) break;
if(c=='\n')
{
itr=list->insert_after(itr,name);
name.clear();
}
else name.push_back(c);
}
fclose(file);
return list;
}

void getStudentList(Request &request, Response &response)
{
char headerBuffer[8192];
forward_list<string>* allName=findAllStudentsName();
string value="<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><title>Thinkingmachines</title></head><body><ol>";
for(forward_list<string>::iterator itr=allName->begin();itr!=allName->end();++itr) value.append("<li>").append(*itr).append("</li>");
value.append("</ol></body></html>");
sprintf(headerBuffer,"HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %ld\nConnection: Keep-Alive\nKeep-Alive: timeout=5, max=1000\n\n",request.getMimeType().c_str(),value.size());
response.setHeader(string(headerBuffer));
response.setContentLength(value.size());
response.setContent(value);
}

void send404(Request &request,Response &response)
{
char responseBuffer[1026],headerBuffer[8192];
int size,e,len;
FILE *file;
char g;
size=0;
file=fopen("404.html","rb");
fseek(file,0,SEEK_END);
size=ftell(file);
fseek(file,0,SEEK_SET);
sprintf(headerBuffer,"HTTP/1.1 404 NOT FOUND\nContent-Type: %s\nContent-Length: %d\nConnection: Keep-Alive\nKeep-Alive: timeout=5, max=1000\n\n",request.getMimeType().c_str(),size);
response.setHeader(headerBuffer);
response.setContentLength(size);
string content="";
while(1)
{
if(size<1024)
{
fread(responseBuffer,size,1,file);
content.append(responseBuffer);
break;
}
else
{
fread(responseBuffer,1024,1,file);
content.append(responseBuffer);
}
size-=1024;
}
response.setContent(content);
cout<<"Send 404"<<endl;
fclose(file);
}


// written by Amit in jan 2024
int main()
{
WebSocketServer webServer(5050);
webServer.error404(send404);
webServer.onRequest("/",welcomePage);
webServer.onRequest("student/list",getStudentList);
webServer.start();
return 0;
}

