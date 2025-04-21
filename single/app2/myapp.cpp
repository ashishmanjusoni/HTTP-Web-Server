#include<cstring>
#include<fstream>
#include<iostream>
#include<http_request>
#include<http_response>
#include<http_linux_tcp_server>
#include<mime_type>
using namespace std;
using namespace wss;

struct marks
{
int rollnumber;
int hindi;
int physics;
int chemistry;
int maths;
int english;
};

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
response._close();
cout<<"Send 404"<<endl;
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

void getMarksheet(Request &request,Response &response)
{
struct marks m;
FILE *file;
char found;
file=fopen("marks.data","rb");
int rollnumber=atoi(request.getParameter("rollnumber").c_str());
found=0;
while(1)
{
fread(&m,sizeof(m),1,file);
if(feof(file)) break;
if(m.rollnumber==rollnumber)
{
request.addParameter("hindi",to_string(m.hindi));
request.addParameter("english",to_string(m.english));
request.addParameter("physics",to_string(m.physics));
request.addParameter("chemistry",to_string(m.chemistry));
request.addParameter("maths",to_string(m.maths));
request.forward("marksheet.sct");
found=1;
break;
}
}
if(!found)
{

}
fclose(file);
}
/*
void getMarksheetForm(Request &request,Response &response)
{
char tmp[11];
int h=request.getParameter("hindi");
int e=request.getParameter("english");
int p=request.getParameter("physics");
int c=request.getParameter("chemistry");
int m=request.getParameter("maths");
FILE *file;
char g;
string str;
file=fopen("marksheet.sct","r");
fseek(file,0,SEEK_END);
int size=ftell(file);
fseek(file,0,SEEK_SET);
response.write("HTTP/1.1 200 OK\nContent-Type: ");
response.write(MIMEType::TEXT_HTML);
response.write("\n\n");
response.addTemplate("hindi",to_string(h));
response.addTemplate("english",to_string(e));
response.addTemplate("physics",to_string(p));
response.addTemplate("chemistry",to_string(c));
response.addTemplate("maths",to_string(m));
while(1)
{
g=fgetc(file);
if(feof(file)) 
{
if(str.empty()) break;
response.write(str);
break;
}
str.push_back(g);
if(g=='\n')
{
response.write(str);
str.clear();
}
}
response._close();
fclose(file);
}
*/
int main(void)
{
LinuxTCPServer webServer(7172);
webServer.error404(send404);
webServer.onRequest("/",indexPage);
webServer.onRequest("/getmarksheet",getMarksheet);
//webServer.onRequest("/marksheet.sct",getMarksheetForm);
webServer.start();
return 0;
}

