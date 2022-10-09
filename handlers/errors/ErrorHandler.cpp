#include "ErrorHandler.h"

#include <Poco/Net/FilePartSource.h>
#include <Poco/Path.h>

namespace handlers
{

ErrorHandler::ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status)
    : m_Status(status) {}

void ErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &res)
{
    static const std::string errorsDirectory(Poco::Path::current() + "html/errors/");
    std::string errorPageSrc = errorsDirectory + std::to_string(m_Status);
    std::cout << errorPageSrc + "/index.html" << std::endl;

    res.setStatus(m_Status);
    res.setChunkedTransferEncoding(true);
    res.sendFile(errorPageSrc + "/index.html","text/html");
}

//Poco::Net::HTMLForm ErrorHandler::getErrorPage(Poco::Path&& path_to_error_sources)
//{
//    static const std::string errorsDirectory(Poco::Path::current() + "html/errors/");
//
//    Poco::Net::HTMLForm form;
//    form.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);
//
//    form.addPart("index.html", new Poco::Net::FilePartSource(errorsDirectory + "index.html"));
//
////    return form;
//    // open and return sources
//}

}