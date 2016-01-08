#pragma once

namespace Example
{
    // 网页文本解析
    class IHtmlParse : public IBase
    {
    public:
        // 获取标题
		virtual const char* ParseTitle(const char*, int) = 0;
        // 获取链接
		virtual void ParseUrl(const char*, const char*, int, IAddUrl&) = 0;
        // 获取图片
		virtual void ParseImg(const char*, const char*, int, IAddUrl&) = 0;
    };
}
