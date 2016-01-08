#pragma once

namespace Example
{
    // 通用功能活动接口
    class IUtilAction
    {
    public:
        // 创建目录
		virtual bool CreateDir(const char*) = 0;
        // 修正非法文件名字符
		virtual const char* FixFileName(const char*) = 0;
        // 编码转换
		virtual const char* ConvertEncoding(const char*, const char* = "GBK", const char* = "UTF-8") = 0;
    };
}
