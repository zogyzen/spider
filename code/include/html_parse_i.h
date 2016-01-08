#pragma once

namespace Example
{
    // ��ҳ�ı�����
    class IHtmlParse : public IBase
    {
    public:
        // ��ȡ����
		virtual const char* ParseTitle(const char*, int) = 0;
        // ��ȡ����
		virtual void ParseUrl(const char*, const char*, int, IAddUrl&) = 0;
        // ��ȡͼƬ
		virtual void ParseImg(const char*, const char*, int, IAddUrl&) = 0;
    };
}
