#pragma once

namespace Example
{
    class CNetAction : public INetAction
    {
    public:
        CNetAction(void) = default;

        // 请求
		virtual const char* SyncRequest(int&, const char*, const char*, int = 80);

    private:
        asio::io_service m_io_serv;
        string m_SyncHttpGet;
    };
}
