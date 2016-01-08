#pragma once

namespace Example
{
    class CFileDown : public IFileDown
    {
    public:
        CFileDown(const char*);

        // ����������
		bool SetDomain(const char*) override;
        // �����ļ�
		bool DownFile(const char*, int) override;

    public:
        static bool SaveDownFile(const char* file, const char* context, int len);

    private:
        string m_domain, m_path;
    };
}
