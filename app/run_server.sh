COMMON_LIB_PATH="/home/ashishsoni/repository/HTTP-Web-Server/common/lib"
COMMON_INC_PATH="/home/ashishsoni/repository/HTTP-Web-Server/common/include"
SRC_LIB_PATH="/home/ashishsoni/repository/HTTP-Web-Server/server/lib/"
SRC_INC_PATH="/home/ashishsoni/repository/HTTP-Web-Server/server/include"
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH:$COMMON_LIB_PATH:$SRC_LIB_PATH
g++ myapp.cpp -L $COMMON_LIB_PATH -L $SRC_LIB_PATH -lhttplinuxtcpserver -lutils -I $COMMON_INC_PATH -I $SRC_INC_PATH -o myapp.out
./myapp.out
