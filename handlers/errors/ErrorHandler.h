#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/File.h>

namespace handlers
{

class ErrorHandler : public Poco::Net::HTTPRequestHandler
{
private:
    const Poco::Net::HTTPServerResponse::HTTPStatus m_Status;

public:
    explicit ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status);
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;


};

}
