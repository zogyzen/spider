#pragma once

#include <string>
#include <stdexcept>

#include "load_library.h"

namespace Example
{
    template<typename INF>
    INF& GetDLLWorkInf(const char* DLL, const char* path)
    {
        std::string sErr;
        static KLoadLibrary<true> lb((std::string(path) + DLL).c_str(), sErr);
        if (!sErr.empty()) throw std::runtime_error(sErr);
        typedef INF& (*FGetWorkInf)(const char*);
        FGetWorkInf getInf = lb.GetLibFunc<FGetWorkInf>("GetWorkInf", sErr);
        if (!sErr.empty()) throw std::runtime_error(sErr);
        return getInf(path);
    }
}
