#include "FileServerSubsystem.h"
#include "handlers/RequestFactory.h"

#include "utils/utils.h"

#include "yaml-cpp/yaml.h"

const char* FileServerSubsystem::name() const
{
    return "HttpFileServer";
}

void FileServerSubsystem::initialize(Poco::Util::Application &app)
{
    auto serv_conf = YAML::LoadFile("config.yaml")["server"];

    m_UriTarget = serv_conf["uri_target"].as<std::string>();
    m_FilesDir = serv_conf["files_dir"].as<std::string>();
    m_MaxFileSize = parsing::getAsBytesSize(serv_conf["max_file_size"].as<std::string>());

    auto port = serv_conf["port"].as<Poco::UInt16>();
    auto hostname = serv_conf["host"].as<std::string>() + ":" + serv_conf["port"].as<std::string>();

    auto* params = new Poco::Net::HTTPServerParams;
    params->setServerName(hostname);
    params->setMaxThreads(serv_conf["maxThreads"].as<int>());
    params->setMaxQueued(serv_conf["maxQueuedSize"].as<int>());

    m_Serv = std::make_unique<Poco::Net::HTTPServer>(new handlers::RequestFactory, port, params);
    m_Serv->start();
}

void FileServerSubsystem::uninitialize()
{
    this->m_Serv->stop();
}

Poco::UInt16 FileServerSubsystem::getPort() const
{
    return m_Serv->port();
}
