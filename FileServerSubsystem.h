#pragma once

#include "yaml-cpp/yaml.h"

#include <Poco/Util/Subsystem.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/URI.h>

class FileServerSubsystem : public Poco::Util::Subsystem
{
private:
    Poco::URI   m_UriTarget;
    Poco::Path  m_FilesDir;
    std::size_t m_MaxFileSize;

    std::unique_ptr<Poco::Net::HTTPServer> m_Serv;

private:
    void initialize(Poco::Util::Application& app) override;
    std::size_t parse_size(const std::string& size_str) const;

public:
    ~FileServerSubsystem() override = default;

};
