#include "std.h"
#include "util_action.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	IUtilAction& GetWorkInf(const char* path)
	{
	    static CUtilAction s_Inf;
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CUtilAction��
// ����Ŀ¼
bool CUtilAction::CreateDir(const char* dir)
{
    bool bResult = false;
    if (nullptr != dir)
    {
        try
        {
            if (!filesystem::exists(dir))
                filesystem::create_directories(dir);
            bResult = true;
        }
        catch (std::exception& ex)
        {
            cout << ex.what() << endl;
        }
    }
    return bResult;
}

// �����Ƿ��ļ����ַ�
const char* CUtilAction::FixFileName(const char* fn)
{
    const char* pResult = nullptr;
    if (nullptr != fn)
    {
        m_result = fn;
        replace_all(m_result, "\"", "_");
        replace_all(m_result, "\\", "_");
        replace_all(m_result, "/", "_");
        replace_all(m_result, ":", "_");
        replace_all(m_result, "*", "_");
        replace_all(m_result, "?", "_");
        replace_all(m_result, "|", "_");
        replace_all(m_result, "<", "_");
        replace_all(m_result, ">", "_");
        pResult = m_result.c_str();
    }
    return pResult;
}

// ����ת��
const char* CUtilAction::ConvertEncoding(const char* srcStr, const char* dstEncd, const char* srcEncd)
{
    m_result = srcStr;
    m_result = locale::conv::between(m_result, dstEncd, srcEncd);
    return m_result.c_str();
}
