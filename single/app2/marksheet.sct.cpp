#include<http_request>
#include<http_response>
void marksheet_sct_cpp(wss::Request &request,wss::Response &response)
{
response.write("HTTP/1.1 200 OK\n");
response.write("Content-Type: text/html");
response.write("\n\n");
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<meta charset='utf-8'>");
response.write("<head>");
response.write("<title>Student Marksheet</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>Physics: ");
response.write(request.getParameter("physics"));
response.write("</h1><br>");
response.write("<h1>Chemistry: ");
response.write(request.getParameter("chemistry"));
response.write("</h1><br>");
response.write("<h1>Maths: ");
response.write(request.getParameter("maths"));
response.write("</h1><br>");
response.write("<h1>English: ");
response.write(request.getParameter("english"));
response.write("<h1><br>");
response.write("<h1>Hindi: ");
response.write(request.getParameter("hindi"));
response.write("</h1><br>");
response.write("</body>");
response.write("</html>");
}
