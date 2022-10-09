#include "ErrorHandler.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Path.h>

#include <fstream>

namespace handlers
{

ErrorHandler::ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status)
    : m_Status(status) {}

void ErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
    static const std::string errorsDirectory(Poco::Path::current() + "static/html/errors/");

    resp.setStatus(m_Status);
    resp.setChunkedTransferEncoding(true);
    if (req.getURI() != "/")
    {
        Poco::Path uri(req.getURI());
        std::string_view file_name = uri.directory(uri.depth());
        resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        resp.sendFile(errorsDirectory + std::to_string(m_Status) + "/" + file_name.data(), "text");
    }
    else
    {
        std::string errorPageSrc = errorsDirectory + std::to_string(m_Status);
        resp.sendFile(errorPageSrc + "/index.html","text/html");
    }

}

}