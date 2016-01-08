#pragma once

namespace Example
{
    class CHttpGet : public IHttpGet
    {
    public:
        CHttpGet(INetAction& inet);

        // 请求网页
		const char* SyncHttpGet(int& len, const char* domain, const char* path) override;

    private:
        string m_SyncHttpGet;
        INetAction& m_inet;
    };
}
