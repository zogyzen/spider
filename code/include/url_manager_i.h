#pragma once

namespace Example
{
    // 链接管理接口
    class IUrlManager : public IAddUrl
    {
    public:
        // 设置域名
		virtual bool SetDomain(const char*) = 0;
        // 获取下条链接
		virtual const char* GetNextUrl(void) = 0;
        // 获取链接对应的服务器名
		virtual const char* GetUrlSrvName(const char*) = 0;
    };
}
