#include "RequestFactory.h"
#include "FileServerApplication.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>

#include "get/GetFileHandler.h"

namespace handlers {

Poco::Net::HTTPRequestHandler* RequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
    Poco::Util::Application& app = FileServerApplication::instance();
    auto& serv = app.getSubsystem<FileServerSubsystem>();
    app.logger().information("Request from %s", request.clientAddress().toString());

    if (request.getURI() == serv.getUriTarget())
    {
        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
        {
            return nullptr;
        }

        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
        {
            return new GetFileHandler;
        }

    }

    return nullptr; // 404
}


}