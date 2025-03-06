#include<mime_type>
#include<utils>
#include<iostream>
using namespace wss;
using namespace std;

string MIMEType::TEXT_HTML="text/html";
string MIMEType::TEXT_CSS="text/css";
string MIMEType::TEXT_CSV="text/csv";
string MIMEType::TEXT_JAVASCRIPT="text/javascript";
string MIMEType::TEXT_PLAIN="text/plain";
string MIMEType::APPLICATION_PDF="application/pdf";
string MIMEType::APPLICATION_JSON="application/json";
string MIMEType::IMAGE_PNG="image/png";
string MIMEType::IMAGE_JPEG="image/jpeg";
string MIMEType::IMAGE_ICO="image/vnd.microsoft.icon";

bool MIMEType::contains(const string &extension)
{
string str=getMIMEType(extension);
return !str.empty();
}

string MIMEType::getMIMEType(const string &resourcePath)
{
const char *e,*f;
f=resourcePath.c_str();
for(e=f+resourcePath.size()-1;e>=f && *e!='.';e--);
e++;
if(extensionEquals(e,"html") || extensionEquals(e,"htm")) return MIMEType::TEXT_HTML;
if(extensionEquals(e,"css")) return MIMEType::TEXT_CSS;
if(extensionEquals(e,"csv")) return MIMEType::TEXT_CSV;
if(extensionEquals(e,"mjs")) return MIMEType::TEXT_JAVASCRIPT;
if(extensionEquals(e,"txt")) return MIMEType::TEXT_PLAIN;
if(extensionEquals(e,"pdf")) return MIMEType::APPLICATION_PDF;
if(extensionEquals(e,"json")) return MIMEType::APPLICATION_JSON;
if(extensionEquals(e,"png")) return MIMEType::IMAGE_PNG;
if(extensionEquals(e,"jpg")|| extensionEquals(e,"jpeg")) return MIMEType::IMAGE_JPEG;
if(extensionEquals(e,"ico")) return MIMEType::IMAGE_ICO;
return "";
}

