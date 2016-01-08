#pragma once

namespace Example
{
    // 基类接口
    class IBase
    {
    public:
		virtual ~IBase(void) = default;
    };

    // 添加链接接口
    class IAddUrl : public IBase
    {
    public:
        virtual bool AddUrl(const char*, int) = 0;
    };
}
