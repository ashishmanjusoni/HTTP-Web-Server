#include<cstring>
#include<fstream>
#include<iostream>
#include<http_request>
#include<http_response>
#include<http_linux_tcp_server>
#include<mime_type>
using namespace std;
using namespace wss;

void indexPage(Request &request,Response &response)
{
request.forward("index.html");
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

void getCityView(Request &request,Response &response)
{
request.addParameter("name","Ashish soni");
request.forward("getCityViewByCode");
}

void getCityViewByCode(Request &request,Response &response)
{
int code=atoi(request.getParameter("cityCode").c_str());
string name=request.getParameter("name");
if(code==1) request.forward("ujjain.html");
else if(code==2) request.forward("indore.html");
else if(code==3) request.forward("dewas.html");
else 
{
request.addParameter("error","Invalid city code");
request.forward("error_page.sct");
}
}

int main(void)
{
LinuxTCPServer webServer(7171);
webServer.onRequest("/",indexPage);
webServer.onRequest("/now",getDispatchTime);
webServer.onRequest("/getCity",getCityView);
webServer.onRequest("/getCityViewByCode",getCityViewByCode);
webServer.start();
return 0;
}

