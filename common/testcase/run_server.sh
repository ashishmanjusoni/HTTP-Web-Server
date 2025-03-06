COMMON_LIB_PATH="/home/ashishsoni/repository/HTTP-Web-Server/common/lib"
COMMON_INC_PATH="/home/ashishsoni/repository/HTTP-Web-Server/common/include"
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH:$COMMON_LIB_PATH
g++ url_codec.cpp -L $COMMON_LIB_PATH -lutils -I $COMMON_INC_PATH -o url_codec.out
./url_codec.out
