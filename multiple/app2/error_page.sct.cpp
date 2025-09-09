#include<http_request>
#include<http_response>
void error_page_sct_cpp(wss::Request &request,wss::Response &response)
{
response.write("HTTP/1.1 200 OK\n");
response.write("Content-Type: text/html");
response.write("\n\n");
response.write("<!DOCTYPE html> ");
response.write("<html lang='en'> ");
response.write("<head> ");
response.write("<meta charset='UTF-8'> ");
response.write("<meta name='viewport' content='width=device-width,initial-scale=1.0'> ");
response.write("<title>404 Page Not Found</title> ");
response.write("</head> ");
response.write("<body> ");
response.write("<h1 style='color:Red;'>NOT FOUND 404</h1> ");
response.write("<h1 style='color:Red;'>");
response.write(request.getParameter("error"));
response.write("</h1>");
response.write("</body> ");
response.write("</html>");
}
