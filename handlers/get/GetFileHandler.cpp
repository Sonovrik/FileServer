#include "GetFileHandler.h"

#include "FileServerApplication.h"

#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <utility>

namespace handlers
{

GetFileHandler::GetFileHandler(Poco::Path files_dir)
	: m_FilesDirectory(std::move(files_dir))
{}

void GetFileHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
								   Poco::Net::HTTPServerResponse& res)
{
	std::string filename;
	Poco::JSON::Parser parser;

	try
	{
		std::string body(std::istreambuf_iterator<char>(req.stream()), {});
		Poco::JSON::Object::Ptr object = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
		m_FilesDirectory = m_FilesDirectory.path() + object->get("filename").toString());
	}
	catch (Poco::Exception& e)
	{
		return;	   // set 400
	}

	if (!(m_FilesDirectory.exists() && m_FilesDirectory.isFile()))
	{
		return;	   // set 404
	}

	//	Poco::File file = m_FilesDirectory.path() + filename;
	//	if (file.exists())
	//	{
	//		// unzip file
	//		// send file
	//	}
	//	else
	//	{
	//		return;	   // set 404
	//	}
}

}