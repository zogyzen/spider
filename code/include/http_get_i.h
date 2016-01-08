#pragma once

namespace Example
{
    // 网页提取接口
    class IHttpGet : public IBase
    {
    public:
        // 请求网页
		virtual const char* SyncHttpGet(int& len, const char* domain, const char* path) = 0;
    };
}
