#include "GetFileHandler.h"

#include "FileServerApplication.h"

#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Zip/ZipArchive.h>
#include <Poco/Zip/ZipStream.h>
#include <Poco/StreamCopier.h>
#include <fstream>

namespace handlers
{

GetFileHandler::GetFileHandler(Poco::Path files_dir)
	: m_FilesDirectory(std::move(files_dir))
{}

// TODO manage errors redirections
void GetFileHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
								   Poco::Net::HTTPServerResponse& res)
{
	try
	{
		static const std::string jsonKeyName = "filename";
		m_FilesDirectory = m_FilesDirectory.path() + '/' + getJsonParam(req.stream(), jsonKeyName);
	}
	catch (Poco::Exception& e)
	{
		res.redirect("/errors/400");
		return;
	}

	if (!(m_FilesDirectory.exists() && m_FilesDirectory.isFile()))
	{
		res.redirect("/errors/404");
		return;
	}

	std::ostream& ostr = res.send();
	if (decompressSingleFile(ostr, m_FilesDirectory) <= 0)
	{
		res.redirect("/errors/500");
		return;
	}

	res.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	res.setChunkedTransferEncoding(true);
}

std::string GetFileHandler::getJsonParam(std::istream& json_stream, const std::string& key)
{
	Poco::JSON::Parser parser;
	std::string body(std::istreambuf_iterator<char>(json_stream), {});
	Poco::JSON::Object::Ptr object = parser.parse(body).extract<Poco::JSON::Object::Ptr>();

	return object->get(key).toString();
}

std::streamsize GetFileHandler::decompressSingleFile(std::ostream& ostr, const Poco::File& fileToDecompress)
{
	std::ifstream inp(fileToDecompress.path(), std::ios::binary);

	if (inp.bad())
	{
		return -1;
	}

	Poco::Zip::ZipArchive arch(inp);
	auto it = arch.headerBegin();

	if (it == arch.headerEnd())
	{
		return -1;
	}

	Poco::Zip::ZipInputStream zipin(inp, it->second);
	ostr.flags(std::ios::binary);

	return Poco::StreamCopier::copyStream(zipin, ostr);
}

}