#pragma oncew

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Path.h>
#include <Poco/Zip/ZipStream.h>

namespace handlers
{

class GetFileHandler : public Poco::Net::HTTPRequestHandler
{
private:
    const Poco::Path m_FilesDirectory;
	inline static const std::string m_ArchExt = "zip";

private:
	std::string getJsonParam(std::istream& json_stream, const std::string& key);
	std::streamsize sendUnzippedFileToClient(Poco::Net::HTTPServerResponse& res, const Poco::Path& fileToDecompress);

	void setFileHeaders(Poco::Net::HTTPServerResponse& res, const std::string& fileName);
	void setRedirectionHeaders(Poco::Net::HTTPServerResponse& res, const std::string& uri);

public:
    GetFileHandler(Poco::Path files_dir);
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;
};

}
