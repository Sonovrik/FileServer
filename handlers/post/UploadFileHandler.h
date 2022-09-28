#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/File.h>

namespace handler
{

class UploadFileHandler : public Poco::Net::HTTPRequestHandler
{
private:
    Poco::File m_FilesDirectory;

public:
    explicit UploadFileHandler(const Poco::File& files_dir);
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;
};

}