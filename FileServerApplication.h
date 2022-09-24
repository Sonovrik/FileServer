#pragma once

#include "yaml-cpp/yaml.h"

#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPServer.h"

class FileServerApplication : public Poco::Util::ServerApplication
{
private:
    void initialize(Application& self) override;
    int main(const std::vector<std::string>&) override;

public:
    ~FileServerApplication() override = default;
};