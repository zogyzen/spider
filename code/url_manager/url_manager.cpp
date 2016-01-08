#include "std.h"
#include "url_manager.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	IUrlManager& GetWorkInf(const char*)
	{
	    static CUrlManager s_Inf;
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CUrlManager类
// 设置域名
bool CUrlManager::SetDomain(const char* domain)
{
    m_domain = domain;
    return this->AddNewUrl("http://www." + m_domain + "/");
}

// 添加链接
bool CUrlManager::AddUrl(const char* url, int len)
{
    bool bResult = false;
    string sSrv = url;
    if ("http://" == sSrv.substr(0, 7))
    {
        sSrv = sSrv.substr(7, sSrv.size() - 7);
        int iTail = sSrv.find("/");
        if (iTail > 0) sSrv = sSrv.substr(0, iTail);
        if (sSrv.find(m_domain) != string::npos) this->AddNewUrl(url);
    }
    else if ('/' == sSrv[0])
        bResult = this->AddNewUrl("http://" + m_currSrv + url);
    else
    {
        int iTail = m_currUrl.rfind("/");
        string sUrlPath = m_currUrl.substr(0, iTail);
        bResult = this->AddNewUrl(sUrlPath + url);
    }
    return bResult;
}

// 获取下条链接
const char* CUrlManager::GetNextUrl(void)
{
    const char* pResult = nullptr;
    if (m_urls.begin() != m_urls.end())
    {
        m_currUrl = m_urls.front();
        pResult = m_currUrl.c_str();
        m_urls.pop_front();
    }
    return pResult;
}

// 获取链接对应的服务器名
const char* CUrlManager::GetUrlSrvName(const char* url)
{
    const char* pSrv = nullptr;
    if (nullptr != url)
    {
        m_currSrv = url;
        if ("http://" == m_currSrv.substr(0, 7))
        {
            m_currSrv = m_currSrv.substr(7, m_currSrv.size() - 7);
            int iTail = m_currSrv.find("/");
            if ((int)string::npos == iTail) iTail = m_currSrv.find("?");
            if (iTail > 0) m_currSrv = m_currSrv.substr(0, iTail);
            pSrv = m_currSrv.c_str();
        }
    }
    return pSrv;
}

// 加新链接
bool CUrlManager::AddNewUrl(string url)
{
    bool bResult = false;
    if (m_urlsExists.find(url) == m_urlsExists.end())
    {
        m_urls.push_back(url);
        m_urlsExists.insert(url);
        bResult = true;
    }
    return bResult;
}
