#include "GetFileHandler.h"

#include "FileServerApplication.h"

#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>

#include <Poco/Zip/ZipArchive.h>
#include <Poco/StreamCopier.h>

#include <fstream>
#include <optional>

namespace handlers
{

GetFileHandler::GetFileHandler(Poco::Path files_dir)
	: m_FilesDirectory(std::move(files_dir))
{}

// TODO manage errors redirections
void GetFileHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
								   Poco::Net::HTTPServerResponse& res)
{
	std::string fileName = getJsonParam(req.stream(), "filename");
	if (fileName.empty())
	{
		setRedirectionHeaders(res, "/errors/400");
		return;
	}

	// file name inside archive
	Poco::Path reqFile = m_FilesDirectory.toString() + '/' + fileName;
	if (sendUnzippedFileToClient(res, reqFile) == -1)
	{
		setRedirectionHeaders(res, "/errors/404");
		return;
	}
}

std::streamsize GetFileHandler::sendUnzippedFileToClient(Poco::Net::HTTPServerResponse& res, const Poco::Path& fileToDecompress)
{
	Poco::Path archivePath = fileToDecompress;
	archivePath.setExtension(m_ArchExt);

	std::ifstream inp(archivePath.toString(), std::ios::binary);
	if (inp.bad())
	{
		return -1;
	}

	Poco::Zip::ZipArchive archivePtr(inp);
	auto it = archivePtr.findHeader(fileToDecompress.getFileName());
	if (it == archivePtr.headerEnd())
	{
		return -1;
	}

	Poco::Zip::ZipInputStream zipStream(inp, it->second);
	setFileHeaders(res, fileToDecompress.getFileName());

	std::ostream& ostr = res.send();
	ostr.flags(std::ios::binary);
	return Poco::StreamCopier::copyStream(zipStream, ostr);
}


std::string GetFileHandler::getJsonParam(std::istream& json_stream, const std::string& key)
{
	std::string filename;
	try
	{
		Poco::JSON::Parser parser;
		std::string body(std::istreambuf_iterator<char>(json_stream), {});
		Poco::JSON::Object::Ptr object = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
		filename = object->get(key).toString();
	}
	catch(std::exception &e)
	{
		return "";
	}

	return filename;
}

void GetFileHandler::setFileHeaders(Poco::Net::HTTPServerResponse& res, const std::string& fileName)
{
	res.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	res.setChunkedTransferEncoding(true);
	res.setContentType("application/octet-stream");
	res.set("Content-Disposition", "attachment;filename=" + fileName);
}

void GetFileHandler::setRedirectionHeaders(Poco::Net::HTTPServerResponse& res, const std::string& uri)
{}

}