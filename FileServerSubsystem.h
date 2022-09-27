#pragma once

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
    void uninitialize() override;

public:
    const char* name() const override;
    ~FileServerSubsystem() override = default;

    Poco::UInt16 getPort() const;
};
