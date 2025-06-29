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
sends back the basic HTTP Response. In this project we also provide support for the template file. We have support for only the template file which have `.sct` extention.

## Programming Languages
* C
* C++
* HTML

## Project Directory
* **/tool** : contains only one file `tpl2c.c` template source code generator which take template and creates appropriate `.cpp` file.
* **/single** : http server can handle only one request at a time (single thread)
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

## Project Description

* The `server/include/http_linux_tcp_server.h` and `server/src/http_linux_tcp_server.cpp` will hold the actual implementation of the server via `LinuxTCPServer` class. 

## How to use

* Instantiate the server through a constructor call `LinuxTCPServer server(8181)` and start the server using the function `server.start()` on the instantiated object. At this point the server will be started and ready to listen the  request on port 8181. The port is any number available on the running operating system.
* Please note the server will validate the availability of the port only when start the server using `server.start()` function. If port is already in use then server will not be start.
* Through `server.onRequest(string,void(*)(Request &,Response &)` one can provide one or many server side resource. The server resource function should have two parameter `Request &` and `Response &` and should have return type `void`.
	`void (function_name)(Request &request,Response &response)`
* To foward request to another resource on same http server then call `request.forward()` function and in argument give name of the resoruce without '/' character at the beginning. 
* Through `request.forward()` function call one can also forward the input parameter, for that one has to invoke the `request.addParameter(key,value)` and on another side call `request.getParameter(key)` to get parameter value.
* Write response to client, invoke `response.write("{content}")`, pass the content followed by response header which follow the TCP protocols.
* To register the template into your server you need to invoke `register_template_files(LinuxTCPServer *)` which is declared in `tpl.h` header file, which takes address of an object of type `LinuxTCPServer`. This method will register all the template files (.sct.cpp) into your server. These template file should be kept in the same directory where entry point function is written.
* `tpl.h` will also gets generated along with other template files.

## Compilation

Please go through the script file `server/src/compile_files.sh` and make changes according to your working directory

## Run Server

Please go through the script file `app/run_server.sh` and make changes according to your working directory

