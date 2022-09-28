#pragma oncew

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

class GetFileHandler : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;
};
