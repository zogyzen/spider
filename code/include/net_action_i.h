#pragma once

namespace Example
{
    // ���繦�ܻ�ӿ�
    class INetAction
    {
    public:
        // ����
		virtual const char* SyncRequest(int&, const char*, const char*, int = 80) = 0;
    };
}
