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
    m_MaxFileSize = getAsBytesSize(serv_conf["max_file_size"].as<std::string>());

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

std::size_t FileServerSubsystem::getAsBytesSize(const std::string& size_str) const
{
    auto [number_part, dim_part] = parseDimensionFormat(size_str);

    std::size_t numb = getNumber(number_part);
    std::size_t dim = getSizeDimension(dim_part);
    return numb * dim;
}

FileServerSubsystem::NumberAndDimension FileServerSubsystem::parseDimensionFormat(std::string_view argument) const
{
    static constexpr std::string_view delimiter = "_";
    auto pos = argument.find_last_of(delimiter);
    if (pos == std::string::npos)
    {
        throw std::runtime_error("YamlConfig - invalid dimension format: " + std::string(argument));
    }
    std::string_view dim_part(argument.data() + (pos + delimiter.size()), argument.size() - (pos + delimiter.size()));
    std::string_view number_part(argument.data(), pos);

    return {.number = number_part, .dimension = dim_part};
}

std::size_t FileServerSubsystem::getSizeDimension(std::string_view dim_part) const
{
    std::size_t res;

    if      (dim_part == "B")      res = 1;
    else if (dim_part == "KB")     res = 2 << 10;
    else if (dim_part == "MB")     res = 2 << 20;
    else if (dim_part == "GB")     res = 2 << 30;
    else
    {
        throw std::runtime_error("YamlConfig - invalid dimension format: " + std::string(dim_part));
    }

    return res;
}

std::size_t FileServerSubsystem::getNumber(std::string_view number_part) const
{
    if (!std::all_of(number_part.begin(), number_part.end(), ::isdigit))
    {
        throw std::runtime_error("YamlConfig - invalid number format" + std::string(number_part));
    }

    std::size_t res;
    std::stringstream ss{};
    ss.write(number_part.data(), static_cast<std::streamsize>(number_part.size()));
    ss >> res;

    return res;
}


