#pragma once

namespace Example
{
    class CHtmlParse : public IHtmlParse
    {
    public:
        CHtmlParse(void) = default;

        // 获取标题
		const char* ParseTitle(const char*, int) override;
        // 获取链接
		void ParseUrl(const char*, const char*, int, IAddUrl&) override;
        // 获取图片
		void ParseImg(const char*, const char*, int, IAddUrl&) override;

    private:
        string m_title;
    };
}
