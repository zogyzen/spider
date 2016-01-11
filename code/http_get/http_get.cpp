#include "std.h"
#include "http_get.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	IHttpGet& GetWorkInf(const char* path)
	{
	    static CHttpGet s_Inf(GetDLLWorkInf<INetAction>("net_action", path));
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CHttpGet¿‡
CHttpGet::CHttpGet(INetAction& inet) : m_inet(inet)
{
}

// «Î«ÛÕ¯“≥
const char* CHttpGet::SyncHttpGet(int& len, const char* domain, const char* path)
{
    const char* pResult = nullptr;
    len = 0;
    stringstream request_stream;
    request_stream << "GET " << path << " HTTP/1.1" << endl;
    request_stream << "Content-Type: application/x-www-form-urlencoded" << endl;
    request_stream << "Host: " << domain << endl;
    request_stream << "Connection: Close" << endl;
    request_stream << "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, */*" << endl;
    request_stream << "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)" << endl;
    request_stream << endl;

    int iCount = 0;
    const char* p = m_inet.SyncRequest(iCount, domain, request_stream.str().c_str());
    bool bResult = iCount > 0 && nullptr != p;
    if (bResult)
    {
        stringstream respond_stream;
        respond_stream.write(p, iCount);
        string s = "";
        while (std::getline(respond_stream, s) && "\r" != s)
        {
            // cout << s << endl;
        }

        m_SyncHttpGet.clear();
        char buf[1025] = {0};
        // memset(buf, 0, sizeof(buf));
        int iSize = 0;
        while ((iSize = respond_stream.readsome(buf, sizeof(buf))) > 0)
            m_SyncHttpGet.append(buf, iSize);
        pResult = m_SyncHttpGet.c_str();
        len = m_SyncHttpGet.size();
    }
    return pResult;
}
