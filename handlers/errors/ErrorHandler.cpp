#include "ErrorHandler.h"

#include <Poco/Net/HTTPServerRequest.h>

namespace handlers
{

ErrorHandler::ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status
                            , Poco::Path  pathToErrorsSrc)
    : m_Status(status)
    , m_PagePath(std::move(pathToErrorsSrc)) {}

void ErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
    resp.setChunkedTransferEncoding(true);
    if (m_Status != Poco::Net::HTTPResponse::HTTP_OK)
    {
        std::string indexHtml =
                Poco::Path::current()
                + m_PagePath.toString()
                + std::to_string(m_Status)
                + "/index.html";

        resp.setStatus(m_Status);
        resp.sendFile(indexHtml,"text/html");
    }
    else
    {
        Poco::Path uri(req.getURI());
        std::string file_path =
                Poco::Path::current()
                + req.getURI();

        resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        resp.sendFile(file_path, "text");
    }

}

}