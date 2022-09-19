#pragma once

#include "yaml-cpp/yaml.h"

#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPServer.h"

class FileServerApplication : public Poco::Util::ServerApplication
{
private:
    std::unique_ptr<Poco::Net::HTTPServer> m_Serv;
    std::string m_Some;
private:
    void initServer(const YAML::Node& config);
    void initialize(Application& self) override;
    int main(const std::vector<std::string>&) override;

public:
    ~FileServerApplication() override = default;
};