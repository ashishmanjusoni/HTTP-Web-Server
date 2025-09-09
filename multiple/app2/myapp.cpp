#include<cstring>
#include<fstream>
#include<iostream>
#include<http_request>
#include<http_response>
#include<http_linux_tcp_server>
#include<mime_type>
#include "tpl.h"
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

void indexPage(Request &request,Response &response)
{
request.forward("index.html");
}

void getMarksheet(Request &request,Response &response)
{
struct marks m;
FILE *file;
char found;
file=fopen("marks.data","rb");
if(!file)
{
request.addParameter("error","Resource not found");
request.forward("error_page.sct");
return;
}
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
request.addParameter("error","Student not found");
request.forward("error_page.sct");
}
fclose(file);
}
int main(void)
{
LinuxTCPServer webServer(7172);
webServer.onRequest("/",indexPage);
webServer.onRequest("/getmarksheet",getMarksheet);
register_template_files(&webServer);
webServer.start();
return 0;
}

