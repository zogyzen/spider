#pragma once

namespace Example
{
    class CUrlManager : public IUrlManager
    {
    public:
        CUrlManager(void) = default;

        // ��������
		bool SetDomain(const char*) override;
        // �������
		bool AddUrl(const char*, int) override;
        // ��ȡ��������
		const char* GetNextUrl(void) override;
        // ��ȡ���Ӷ�Ӧ�ķ�������
		const char* GetUrlSrvName(const char*) override;

    private:
        // ��������
        bool AddNewUrl(string);

    private:
        string m_domain, m_currUrl, m_currSrv;
        list<string> m_urls;
        set<string> m_urlsExists;
    };
}
