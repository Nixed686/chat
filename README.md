# chat
使用了nginx作为tcp负载均衡器的聊天服务器和客户端的源码 使用到了muduo库，redis， MySQL等

编译时需先清理build目录下的文件
cd build   //进入build目录
rm -rf *   //删除build下的文件
cmake ..   //再进行编译
make
