#pragma once

namespace Example
{
    class CUtilAction : public IUtilAction
    {
    public:
        CUtilAction(void) = default;

        // 创建目录
		bool CreateDir(const char*) override;
        // 修正非法文件名字符
		const char* FixFileName(const char*) override;
        // 编码转换
		const char* ConvertEncoding(const char*, const char*, const char*) override;

    private:
        string m_result;
    };
}
