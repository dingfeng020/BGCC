#简介
BGCC（百度通用通信组件）是一个跨语言、跨平台、面向对象的高性能轻量级RPC框架。

>1. 具有自定义的接口描述语言和代码生成引擎
>2. 支持事务级别的服务端消息主动推送
>3. 消息流监控
>4. 变态的效率

#使用产品
>1. [百度开源呼叫中心套件](https://github.com/Baidu-ecom/CC)

#依赖库
>1. [openssl](http://openssl.org)库，目前依赖的版本是[1.0.2](http://openssl.org/source/openssl-1.0.2.tar.gz)，详细情况请参考[这里](https://github.com/BaiduCC/BGCC/tree/master/deps)

#联系我们
>1. QQ群：425351662
>2. [在线咨询](http://qiao.baidu.com/v3/?module=default&controller=im&action=index&ucid=7880242&type=n&siteid=6001152)

#源码目录结构

<table>
    <tr>
        <td>文件/目录名</td>
        <td>作用</td>
    </tr>
    <tr>
        <td>adapter</td>
        <td>存放生成bgcc.jar及libbgcc4j.so的源码</td>
    </tr>
    <tr>
        <td>bgcc</td>
        <td>存放生成libbgcc.so和libbgcc.a的源码</td>
    </tr>
    <tr>
        <td>build.bat</td>
        <td>BGCC在Windows平台上的自动编译脚本</td>
    </tr>
    <tr>
        <td>bgcc.sln</td>
        <td>BGCC在Windows平台上的解决方案文件</td>
    </tr>
    <tr>
        <td>bidl2sl</td>
        <td>用于存入生成工具bidl2sl的源码</td>
    </tr>
    <tr>
        <td>build.py</td>
        <td>BGCC跨平台编译统一入口文件</td>
    </tr>
    <tr>
        <td>doc</td>
        <td>参考文档目录</td>
    </tr>
    <tr>
        <td>license.txt</td>
        <td>license文件</td>
    </tr>
    <tr>
        <td>Makefile</td>
        <td>BGCC在Linux平台下自动编译脚本</td>
    </tr>
    <tr>
        <td>sample</td>
        <td>代码使用示例</td>
    </tr>
    <tr>
        <td>vimplugin</td>
        <td>vim bidl插件目录</td>
    </tr>
</table>

#代码示例
请参见源码sample目录。

#安装
请参见bgcc manual文档。文档下载网址：http://bgcc.baidu.com


