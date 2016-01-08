#include "std.h"
#include "file_down.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	IFileDown& GetWorkInf(const char* path)
	{
	    static CFileDown s_Inf(path);
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CFileDown类
CFileDown::CFileDown(const char* path) : m_path(path)
{
}

// 设置主域名
bool CFileDown::SetDomain(const char* domain)
{
    m_domain = domain;
    return true;
}

// 下载文件
bool CFileDown::DownFile(const char* context, int len)
{
    IUtilAction& infUtil = GetDLLWorkInf<IUtilAction>("util_action", m_path.c_str());
    IHtmlParse& infParse = GetDLLWorkInf<IHtmlParse>("html_parse", m_path.c_str());

    string sTitle = infParse.ParseTitle(context, len);
    #ifndef WIN32
    sTitle = infUtil.ConvertEncoding(sTitle.c_str(), "UTF-8", "GBK");
    #endif
    sTitle = infUtil.FixFileName(sTitle.c_str());
    string sPath = m_path + "downfile/" + sTitle;
    infUtil.CreateDir(sPath.c_str());
    string sFile = sPath + "/" + sTitle + ".html";
    CFileDown::SaveDownFile(sFile.c_str(), context, len);

    class CDownPic : public IAddUrl
    {
    public:
        CDownPic(string domain, string path, string rootp) : m_domain(domain), m_path(path), m_pathroot(rootp) {}
        bool AddUrl(const char* url, int len) override
        {
            bool bResult = false;
            IHttpGet& infHttp = GetDLLWorkInf<IHttpGet>("http_get", m_pathroot.c_str());
            IUrlManager& infUrl = GetDLLWorkInf<IUrlManager>("url_manager", m_pathroot.c_str());
            const char* pSrv = infUrl.GetUrlSrvName(url);
            if (nullptr != pSrv)
            {
                string sSrv = pSrv;
                if (string::npos != sSrv.find(m_domain))
                {
                    int iLen = 0;
                    const char* pContext = infHttp.SyncHttpGet(iLen, sSrv.c_str(), url);
                    if (nullptr != pContext && iLen > 0)
                    {
                        string sUrl = url;
                        int iTail = sUrl.rfind("/") + 1;
                        if (iTail > 0)
                            sUrl = sUrl.substr(iTail, sUrl.size() - iTail);
                        string sFile = m_path + "/" + sUrl;
                        CFileDown::SaveDownFile(sFile.c_str(), pContext, iLen);
                        bResult = true;
                    }
                }
            }
            return bResult;
        }

    private:
        string m_domain, m_path, m_pathroot;
    } dPic(m_domain, sPath, m_path);
    infParse.ParseImg(m_domain.c_str(), context, len, dPic);
    return true;
}

// 保存文件
bool CFileDown::SaveDownFile(const char* file, const char* context, int len)
{
    bool bResult = false;
    try
    {
        if (nullptr != context && len > 0)
        {
            ofstream f_ofsSave(file, ios_base::out | ios_base::binary | ios_base::trunc);
            f_ofsSave.write(context, len);
            f_ofsSave.close();
            bResult = true;
        }
    }
    catch (std::exception& ex)
    {
    }
    return bResult;
}
