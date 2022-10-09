#include "RequestFactory.h"
#include "FileServerApplication.h"

#include "get/GetFileHandler.h"
#include "post/UploadFileHandler.h"
#include "errors/ErrorHandler.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>

namespace handlers
{

Poco::Net::HTTPRequestHandler* GetHandler(const Poco::Net::HTTPServerRequest& request, const FileServerSubsystem& serv)
{
    Poco::Path uri(request.getURI());
    if (uri.toString().find(serv.getErrorsUri()) == 0)
    {
        return new ErrorHandler(Poco::Net::HTTPResponse::HTTP_OK,
                                serv.getErrorsUri());
    }
    else
    {
        return nullptr;
    }
}

Poco::Net::HTTPRequestHandler* PostHandler(const Poco::Net::HTTPServerRequest& request, const FileServerSubsystem& serv)
{
    if (request.getURI() == serv.getUriTarget())
    {
        return new UploadFileHandler(serv.getFilesDirectory());
    }

    return nullptr;
}

Poco::Net::HTTPRequestHandler* RequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
    Poco::Util::Application& app = FileServerApplication::instance();
    auto& serv = app.getSubsystem<FileServerSubsystem>();

    app.logger().information("Request from %s", request.clientAddress().toString());

    Poco::Net::HTTPRequestHandler *handler = nullptr;
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
    {
        handler = PostHandler(request, serv);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
    {
        handler = GetHandler(request, serv);
    }

    return  handler != nullptr
            ?   handler
            :   new ErrorHandler(Poco::Net::HTTPResponse::HTTP_NOT_FOUND,
                                serv.getErrorsUri());
}

}