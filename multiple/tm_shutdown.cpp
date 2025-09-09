#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
using namespace std;
int main()
{
int clientSocketDescriptor;
struct sockaddr_in clientSocketInformation;
string request;
int successCode,byteReceived;
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
cout<<"Unable to create socket"<<endl;
return 0;
}
clientSocketInformation.sin_family=AF_INET;
clientSocketInformation.sin_port=htons(7172);
clientSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
successCode=connect(clientSocketDescriptor,(struct sockaddr*)&clientSocketInformation,sizeof(clientSocketInformation));
if(successCode<0)
{
cout<<"Unable to connect, couldn't found 127.0.0.1:7172"<<endl;
return 0;
}
request="GET /shutdown HTTP/1.1";
successCode=send(clientSocketDescriptor,request.c_str(),request.size()+1,0);
if(successCode<0)
{
cout<<"Unable to send request to 127.0.0.1:7172"<<endl;
return 0;
}
return 0;
}
