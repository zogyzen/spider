#pragma once

namespace Example
{
    class CSpiderMain : public ISpiderMain
    {
    public:
        CSpiderMain(const char*);

        // ����
		void Run(const char* domain, const char* key) override;

    private:
        string m_path;
    };
}
