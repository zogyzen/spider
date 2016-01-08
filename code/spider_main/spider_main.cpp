#include "std.h"
#include "spider_main.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	ISpiderMain& GetWorkInf(const char* path)
	{
	    static CSpiderMain s_Inf(path);
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CSpiderMain¿‡
CSpiderMain::CSpiderMain(const char* path) : m_path(path)
{
}

// ∆Ù∂Ø
void CSpiderMain::Run(const char* domain, const char* key)
{
    try
    {
        IUrlManager& infUrl = GetDLLWorkInf<IUrlManager>("url_manager", m_path.c_str());
        IHttpGet& infHttp = GetDLLWorkInf<IHttpGet>("http_get", m_path.c_str());
        IHtmlParse& infParse = GetDLLWorkInf<IHtmlParse>("html_parse", m_path.c_str());
        IFileDown& infFDown = GetDLLWorkInf<IFileDown>("file_down", m_path.c_str());

        infUrl.SetDomain(domain);
        infFDown.SetDomain(domain);

        const char* pUrl = nullptr;
        while ((pUrl = infUrl.GetNextUrl()) != nullptr)
            try
            {
                cout << pUrl << endl;
                int iLen = 0;
                const char* pContext = infHttp.SyncHttpGet(iLen, infUrl.GetUrlSrvName(pUrl), pUrl);
                if (nullptr != pContext)
                {
                    infParse.ParseUrl(domain, pContext, iLen, infUrl);
                    string sContext(pContext, pContext + iLen);
                    if (string(pContext, pContext + iLen).find(key) != string::npos) infFDown.DownFile(pContext, iLen);
                }
            }
            catch (exception& ex)
            {
                cout << ex.what() << endl;
            }
    }
    catch (exception ex)
    {
        cout << ex.what() << endl;
    }
}
