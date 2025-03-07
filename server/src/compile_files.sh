g++ -c -Wall -Werror -fPIC -I ../include -I ../../common/include request.cpp -o request.o
g++ -c -Wall -Werror -fPIC -I ../include -I ../../common/include response.cpp -o response.o
g++ -c -Wall -Werror -fPIC -I ../include -I ../../common/include web_server.cpp -o web_server.o
g++ -shared -o ../lib/libwebserver.so *.o
