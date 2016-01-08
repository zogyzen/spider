#pragma once

namespace Example
{
    class CUtilAction : public IUtilAction
    {
    public:
        CUtilAction(void) = default;

        // ����Ŀ¼
		bool CreateDir(const char*) override;
        // �����Ƿ��ļ����ַ�
		const char* FixFileName(const char*) override;
        // ����ת��
		const char* ConvertEncoding(const char*, const char*, const char*) override;

    private:
        string m_result;
    };
}
