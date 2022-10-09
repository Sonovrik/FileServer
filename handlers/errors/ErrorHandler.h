#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Path.h>

namespace handlers
{

class ErrorHandler : public Poco::Net::HTTPRequestHandler
{
private:
    const Poco::Net::HTTPServerResponse::HTTPStatus m_Status;
    const Poco::Path m_PagePath;

public:
    ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status, Poco::Path  pathToErrorsSrc);
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;


};

}
