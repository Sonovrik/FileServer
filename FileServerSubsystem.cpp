#include "FileServerSubsystem.h"
#include "handlers/RequestFactory.h"

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
    m_MaxFileSize = parse_size(serv_conf["max_file_size"].as<std::string>());

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
    if (dimension == "KB")
    {
        res *= 2 << 10;
    }
    else if (dimension == "MB")
    {
        res *= 2 << 20;
    }
    else if (dimension == "GB")
    {
        res *= 2 << 30;
    }
    else
    {
        throw std::runtime_error("Invalid dimension format");
    }

    return res;
}
