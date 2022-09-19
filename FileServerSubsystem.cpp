#include "FileServerSubsystem.h"
#include "handlers/RequestFactory.h"

void FileServerSubsystem::initialize(Poco::Util::Application &app)
{
    auto serv_conf = YAML::LoadFile("config.yaml")["server"];

    m_UriTarget = serv_conf["uri_target"].as<std::string>();
    m_FilesDir = serv_conf["files_dir"].as<std::string>();
    m_MaxFileSize = serv_conf["max_file_size"].as<std::size_t>();

    auto port = serv_conf["port"].as<Poco::UInt16>();
    auto hostname = serv_conf["host"].as<std::string>() + ":" + serv_conf["port"].as<std::string>();

    auto* params = new Poco::Net::HTTPServerParams;
    params->setServerName(hostname);
    params->setMaxThreads(serv_conf["maxThreads"].as<int>());
    params->setMaxQueued(serv_conf["maxQueuedSize"].as<int>());

    m_Serv = std::make_unique<Poco::Net::HTTPServer>(new handlers::RequestFactory, port, params);
    m_Serv->start();
}

std::size_t FileServerSubsystem::parse_size(const std::string& size_str) const
{
    static const std::string delimiter = "_";

    auto pos = size_str.find(delimiter);

    if (pos == std::string::npos)
    {
        throw std::runtime_error("Invalid dimension format");
    }

    auto dimension = std::string_view(&delimiter[pos], delimiter.size() - pos);

    std::size_t res = std::stoi(std::string(&delimiter[pos], pos));
//    if (dimension == "GB") res *=
    return 0;
}
