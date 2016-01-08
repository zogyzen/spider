#include "std.h"
#include "net_action.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	INetAction& GetWorkInf(const char*)
	{
	    static CNetAction s_Inf;
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CNetAction类
// 请求
const char* CNetAction::SyncRequest(int& resCount, const char* domain, const char* request, int port)
{
    const char* pResult = nullptr;
    try
    {
        // 链接到服务器
        asio::ip::tcp::resolver resolver(m_io_serv);
        asio::ip::tcp::resolver::query query(domain, lexical_cast<string>(port));
        asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        asio::ip::tcp::socket socket(m_io_serv);
        asio::connect(socket, endpoint_iterator);

        // 请求
        socket.write_some(asio::buffer(request, strlen(request)));

        // 返回
        m_SyncHttpGet.clear();
        system::error_code error;
        char buf[1025] = {0};
        memset(buf, 0, sizeof(buf));
        int iSize = 0;
        while ((iSize = socket.read_some(asio::buffer(buf, sizeof(buf) - 1), error)) > 0 && error != asio::error::eof)
            m_SyncHttpGet.append(buf, iSize);
        pResult = m_SyncHttpGet.c_str();
        resCount = m_SyncHttpGet.size();
    }
    catch (std::exception& ex)
    {
        string sErr = ex.what();
        cout << domain << ": " << sErr << endl;
        pResult = nullptr;
    }
    return pResult;
}
