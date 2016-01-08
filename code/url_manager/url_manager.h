#pragma once

namespace Example
{
    class CUrlManager : public IUrlManager
    {
    public:
        CUrlManager(void) = default;

        // 设置域名
		bool SetDomain(const char*) override;
        // 添加链接
		bool AddUrl(const char*, int) override;
        // 获取下条链接
		const char* GetNextUrl(void) override;
        // 获取链接对应的服务器名
		const char* GetUrlSrvName(const char*) override;

    private:
        // 加新链接
        bool AddNewUrl(string);

    private:
        string m_domain, m_currUrl, m_currSrv;
        list<string> m_urls;
        set<string> m_urlsExists;
    };
}
