#include "RequestFactory.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>

namespace handlers {

Poco::Net::HTTPRequestHandler* RequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
    {
        return nullptr;
    }

    return nullptr;
}


}