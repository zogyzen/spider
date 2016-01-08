#include "std.h"
#include "html_parse.h"

////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	IHtmlParse& GetWorkInf(const char*)
	{
	    static CHtmlParse s_Inf;
	    return s_Inf;
	}
}

////////////////////////////////////////////////////////////////////////////////
// CHtmlParse类
// 获取标题
const char* CHtmlParse::ParseTitle(const char* context, int len)
{
    const char* pResult = nullptr;
    string str;
    str.append(context, len);
    string::const_iterator start = str.begin();
    string::const_iterator end = str.end();
    regex pattern("<title>.*</title>");
    smatch mat;
    if (regex_search(start, end, mat, pattern))
    {
        string msg(mat[0].first, mat[0].second);
        if (msg.size() >= 15) msg = msg.substr(7, msg.size() - 15);
        m_title = msg;
        pResult = m_title.c_str();
    }
    else pResult = nullptr;
    return pResult;
}

// 获取链接
void CHtmlParse::ParseUrl(const char* domain, const char* context, int len, IAddUrl& aurl)
{
    string str(context, context + len);
    // fstream logfile("d:\\log.txt", ios::app);
    // logfile << endl << "***********************************************************************************" << endl << str << endl;
    regex pattern("href=('|\")(http://)?(\\w+\\.)*(\\w*/)*(\\w+(\\.\\w+)?)?(\\?(\\w+\\=\\w+\\&?)+)?('|\")", regex::icase);
    for (sregex_iterator it(str.cbegin(), str.cend(), pattern), end_it; end_it != it; ++it)
    {
        string msg = it->str();
        if (msg.size() > 6) msg = msg.substr(6, msg.size() - 7);
        if (msg.size() > 3 && ".css" != msg.substr(msg.size() - 4, 4))
        {
            aurl.AddUrl(msg.c_str(), msg.size());
            // logfile << msg << endl;
            // logfile.flush();
        }
    }
}

// 获取图片
void CHtmlParse::ParseImg(const char* domain, const char* context, int len, IAddUrl& aurl)
{
    string str(context, context + len);
    regex pattern("src=('|\")(http://)?(\\w+\\.)*(\\w*/)*\\w+\\.(jpeg|jpg|png|gif|tiff)('|\")", regex::icase);
    for (sregex_iterator it(str.cbegin(), str.cend(), pattern), end_it; end_it != it; ++it)
    {
        string msg = it->str();
        msg = msg.substr(5, msg.size() - 6);
        aurl.AddUrl(msg.c_str(), msg.size());
    }
}
