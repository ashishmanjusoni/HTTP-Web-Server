#include<cstring>
#include<fstream>
#include<iostream>
#include<http_request>
#include<http_response>
#include<http_linux_tcp_server>
#include<mime_type>
using namespace std;
using namespace wss;

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
response.write("HTTP/1.1 200 OK\nContent-Type: ");
response.write(MIMEType::TEXT_HTML);
response.write("\n\n");
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
cout<<"Send 404"<<endl;
response._close();
fclose(file);
}

void indexPage(Request &request,Response &response)
{
char responseBuffer[1026];
int size,e,len;
FILE *file;
size=0;
file=fopen("index.html","rb");
fseek(file,0,SEEK_END);
size=ftell(file);
fseek(file,0,SEEK_SET);
response.write("HTTP/1.1 200 OK\nContent-Type: ");
response.write(MIMEType::TEXT_HTML);
response.write("\n\n");
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

void getDispatchTime(Request &request, Response &response)
{
time_t now;
time(&now);
char *t=ctime(&now);
response.write("HTTP/1.1 200 OK\nContent-Type: ");
response.write(MIMEType::TEXT_PLAIN);
response.write("\n\n");
response.write(t);
response._close();
}

/*
void getCityView(Request &request,Response &response)
{
int cityCode=atoi(request.get("cityCode").c_str());
if(cityCode==1) request.forward("ujjain.html");
else if(cityCode==2) request.forward("indore.html");
else if(cityCode==3) request.forward("dewas.html");
else request.forward("index.html");
}
*/
void getCityView(Request &request,Response &response)
{
//int cityCode=atoi(request.get("cityCode").c_str());
//request.setInt("code",cityCode);
request.add("name","Ashish soni");
request.forward("getCityViewByCode");
}

void getCityViewByCode(Request &request,Response &response)
{
int code=atoi(request.get("cityCode").c_str());
string name=request.get("name");
cout<<"Request Parameter [name] has value: "<<name<<endl;
if(code==1) request.forward("ujjain.html");
else if(code==2) request.forward("indore.html");
else if(code==3) request.forward("dewas.html");
else request.forward("index.html");
}

int main(void)
{
LinuxTCPServer webServer(7171);
webServer.error404(send404);
webServer.onRequest("/",indexPage);
webServer.onRequest("/now",getDispatchTime);
webServer.onRequest("/getCity",getCityView);
webServer.onRequest("/getCityViewByCode",getCityViewByCode);
webServer.start();
return 0;
}

