COMMON_LIB_PATH="/home/ashishsoni/cpp_programming/networking/example11/common/lib/"
COMMON_INC_PATH="/home/ashishsoni/cpp_programming/networking/example11/common/include/"
SRC_LIB_PATH="/home/ashishsoni/cpp_programming/networking/example11/tmwp/lib/"
SRC_INC_PATH="/home/ashishsoni/cpp_programming/networking/example11/tmwp/include/"
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH:$COMMON_LIB_PATH:$SRC_LIB_PATH
g++ myapp.cpp -L $COMMON_LIB_PATH -L $SRC_LIB_PATH -lwebserver -lutils -I $COMMON_INC_PATH -I $SRC_INC_PATH -o myapp.out
./myapp.out
