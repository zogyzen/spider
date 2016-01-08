#pragma once

namespace Example
{
    // 网络功能活动接口
    class INetAction
    {
    public:
        // 请求
		virtual const char* SyncRequest(int&, const char*, const char*, int = 80) = 0;
    };
}
