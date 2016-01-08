#include "std.h"

int main(int argc, char *argv[])
{
    try
    {
        string path = argv[0];
        int iTailDir = path.rfind('/');
        if ((int)string::npos == iTailDir) iTailDir = path.rfind('\\');
        path = path.substr(0, iTailDir + 1);
        string domain = "sohu.com";
        if (argc > 1) domain = argv[1];
        string key = GetDLLWorkInf<IUtilAction>("util_action", path.c_str()).ConvertEncoding("SUV");
        if (argc > 2) key = argv[2];
        cout << domain << " " << key  << " " << path << endl;
        GetDLLWorkInf<ISpiderMain>("spider_main", path.c_str()).Run(domain.c_str(), key.c_str());
    }
    catch (exception ex)
    {
        cout << ex.what() << endl;
    }
    return 0;
}
