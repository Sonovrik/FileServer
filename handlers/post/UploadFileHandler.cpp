#include "UploadFileHandler.h"

namespace handlers
{

UploadFileHandler::UploadFileHandler(const Poco::File &files_dir)
    : m_FilesDirectory(files_dir) {}

void UploadFileHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &res)
{
    // upload logic


}

}
