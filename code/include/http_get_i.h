#pragma once

namespace Example
{
    // ��ҳ��ȡ�ӿ�
    class IHttpGet : public IBase
    {
    public:
        // ������ҳ
		virtual const char* SyncHttpGet(int& len, const char* domain, const char* path) = 0;
    };
}
