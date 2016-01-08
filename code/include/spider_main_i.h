#pragma once

namespace Example
{
    // 主程序接口
    class ISpiderMain : public IBase
    {
    public:
        // 启动
		virtual void Run(const char* domain, const char* key) = 0;
    };
}
