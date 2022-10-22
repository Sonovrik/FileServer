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
	Poco::Path fileName;
	try
	{
		static const std::string jsonKeyName = "filename";
		fileName = getJsonParam(req.stream(), jsonKeyName);
	}
	catch (Poco::Exception& e)
	{
		res.redirect("/errors/400");
		return;
	}

	// file name inside archive
	Poco::Path reqFile = m_FilesDirectory.getNode() + '/' + fileName.getFileName();
	fileName.setExtension(m_ArchExt);

	// archive file name
	Poco::File archFile = static_cast<Poco::Path>(m_FilesDirectory.getNode() + '/' + fileName.getBaseName())
								  .setExtension(m_ArchExt);

	if (!(archFile.exists() && archFile.isFile()))
	{
		res.redirect("/errors/404");
		return;
	}






	res.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	res.setChunkedTransferEncoding(true);
	res.setContentType("application/octet-stream");
	res.set("Content-Disposition", "attachment;filename=" + fileName.getFileName());

	std::ostream& ostr = res.send();
	if (decompressSingleFile(ostr, m_FilesDirectory) <= 0)
	{
		res.redirect("/errors/500");
		return;
	}
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
	auto it = arch.findHeader(fileToDecompress.path());
	if (it == arch.headerEnd())
	{
		return -1;
	}

	Poco::Zip::ZipInputStream zipin(inp, it->second);
	ostr.flags(std::ios::binary);

	return Poco::StreamCopier::copyStream(zipin, ostr);
}

}