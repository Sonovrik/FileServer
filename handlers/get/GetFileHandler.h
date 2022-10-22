#pragma oncew

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Path.h>
#include <Poco/File.h>

namespace handlers
{

class GetFileHandler : public Poco::Net::HTTPRequestHandler
{
private:
    const Poco::Path m_FilesDirectory;
	inline static const std::string m_ArchExt = "zip";

private:
	std::string getJsonParam(std::istream& json_stream, const std::string& key);
	std::streamsize decompressSingleFile(std::ostream& ostr, const Poco::File& fileToDecompress);

public:
    GetFileHandler(Poco::Path files_dir);
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) override;
};

}
