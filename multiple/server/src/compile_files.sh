# compile .cpp file and generates the .o (object file) in same working directory
g++ -c -Wall -Werror -fPIC -I ../include -I ../../../common/include http_request.cpp -o http_request.o
g++ -c -Wall -Werror -fPIC -I ../include -I ../../../common/include http_response.cpp -o http_response.o
g++ -c -Wall -Werror -fPIC -I ../include -I ../../../common/include http_linux_tcp_server.cpp -o http_linux_tcp_server.o
# Using those object files will create a shared library (.so)
g++ -shared -o ../lib/libhttplinuxtcpserver.so *.o
