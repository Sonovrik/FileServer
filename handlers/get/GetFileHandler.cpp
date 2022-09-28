#include "GetFileHandler.h"

#include <Poco/Net/HTTPServerRequest.h>

void GetFileHandler::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res)
{
    std::istream &ss = req.stream();

    std::string body;
    body.reserve(req.getContentLength());
    ss.read(body.data(), req.getContentLength());

    std::cout << body << std::endl;

    res.send();
}
