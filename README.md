## What is an HTTP-Web-Server?
`HTTP Protocol` Hypertext Transfer Protocol (HTTP) is an protocol for transmitting hypermedia documents. It was designed for communication between web browser and web server.

`HTTP Web Server` whenever a browser needs a file that is hosted on a web server, the browser requests the file via HTTP. When the request reaches the correct (hardware)web server, the (software) HTTP server accepts the request, finds the requested document, and sends it back to the browser, also through HTTP. (If the server doesn't find the requested document, it returns a 404 response instead.) 

<img src="https://github.com/user-attachments/assets/bcbfe6c9-7777-43ab-8820-f39ef14d638f" alt="HTTP Web Server" width="300" height="120">


A web client, for example, a web browser, sends an HTTP request to a web server via a network. The web server which is powered by an HTTP server:
* receives this request and processes it
* determines the appropriate response after doing certain checks
* sends this response to the web client.

The response sent by the HTTP server may also include data from files (for example, HTML documents) stored on the webserver.

## About Project

This is mini project which shows one of the ways in which the HTTP servers are implemented. It uses TCP socket to listen the incomming request and 
sends back the basic HTTP Response. 

## Programming Languages
* C
* C++
* HTML

## Project Directory

* **common/include** : contains header files of the utilities

        * mime_type
        * url_encoder
        * url_decoder
        * utils.cpp
      
* **common/src** : contains implementation of the above header files

        * mime_type.cpp
        * url_encoder.cpp
        * url_decoder.cpp
        * utils.cpp

* **server/include** : this directory contains three major header files
  
        * http_linux_tcp_server
        * http_request
        * http_response

* **server/src** : this directory contains implementation part of the above head file

        * http_linux_tcp_server.cpp
        * http_request.cpp
        * http_response.cpp

## Compilation

`compile all (.cpp) files and generates the .o (object file) files in same working directory i.e (/src)`

g++ -c -Wall -Werror -fPIC -I ../include -I ../../common/include http_request.cpp -o http_request.o

g++ -c -Wall -Werror -fPIC -I ../include -I ../../common/include http_response.cpp -o http_response.o

g++ -c -Wall -Werror -fPIC -I ../include -I ../../common/include http_linux_tcp_server.cpp -o http_linux_tcp_server.o

`Using those object files will create a shared library (.so) in (/lib) directory`

g++ -shared -o ../lib/libhttplinuxtcpserver.so *.o

