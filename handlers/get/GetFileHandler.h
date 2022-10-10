#pragma oncew

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Path.h>

namespace handlers
{

class GetFileHandler : public Poco::Net::HTTPRequestHandler
{
private:
    Poco::Path m_FilesDirectory;

public:
    GetFileHandler(Poco::Path  files_dir);
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;
};

}
