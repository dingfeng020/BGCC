bgcc编译需要依赖openssl库，为了方便在windows下编译，我们直接将openssl源代码直接引了进来，目前依赖版本是[1.0.2a](http://openssl.org/source/openssl-1.0.2a.tar.gz)。

注：
>1. 相关开源协议及版权请参考openssl[官方网站](http://openssl.org)
>2. 编译openssl需要依赖perl，请大家参考openssl的INSTALL文件，提前部署好依赖环境 
>3. 部署好openssl的依赖环境之后，不需要手工编译openssl，bgcc的编译脚本会自动编译openssl


