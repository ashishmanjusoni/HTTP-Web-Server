#ifndef __$__TPL__2025_
#define __$__TPL__2025_
#include<http_request>
#include<http_response>
#include<http_linux_tcp_server>
using namespace wss;
void marksheet_sct_cpp(wss::Request &request,wss::Response &response);
void error_page_sct_cpp(wss::Request &request,wss::Response &response);
void register_template_files(LinuxTCPServer *webServer){
webServer->onRequest("/marksheet.sct",marksheet_sct_cpp);
webServer->onRequest("/error_page.sct",error_page_sct_cpp);
}
#endif