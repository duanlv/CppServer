/*!
    \file http_server.cpp
    \brief HTTP server implementation
    \author Ivan Shynkarenka
    \date 30.04.2019
    \copyright MIT License
*/

#include "server/http/http_server.h"

#include "string/format.h"

namespace CppServer {
namespace HTTP {

void HTTPServer::AddStaticContent(const CppCommon::Path& path, const CppCommon::Timespan& timeout)
{
    auto hanlder = [](CppCommon::FileCache & cache, const std::string& key, const std::string& value, const CppCommon::Timespan& timespan)
    {
        auto header = HTTPResponse();
        header.SetBegin(200);
        header.SetContentType(CppCommon::Path(key).extension().string());
        header.SetHeader("cache-control", "max-age={}"_format(timespan.seconds()));
        header.SetBody(value);
        return cache.insert(key, header.cache(), timespan);
    };

    cache().insert_path(path, "/", timeout, hanlder);
}

} // namespace HTTP
} // namespace CppServer