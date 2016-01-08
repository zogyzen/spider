#pragma once

namespace Example
{
    // ���ӹ���ӿ�
    class IUrlManager : public IAddUrl
    {
    public:
        // ��������
		virtual bool SetDomain(const char*) = 0;
        // ��ȡ��������
		virtual const char* GetNextUrl(void) = 0;
        // ��ȡ���Ӷ�Ӧ�ķ�������
		virtual const char* GetUrlSrvName(const char*) = 0;
    };
}
