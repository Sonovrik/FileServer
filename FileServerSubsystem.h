#pragma once

#include <Poco/Util/Subsystem.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/File.h>

class FileServerSubsystem : public Poco::Util::Subsystem
{
private:
    std::string m_UriTarget;
    Poco::File  m_FilesDir;
    std::size_t m_MaxFileSize;

    std::unique_ptr<Poco::Net::HTTPServer> m_Serv;

private:
    void initialize(Poco::Util::Application& app) override;
    void uninitialize() override;

public:
    const char* name() const override;
    ~FileServerSubsystem() override = default;

    Poco::UInt16 getPort() const;
    const Poco::File& getFilesDirectory() const;
    const std::string& getUriTarget() const;
    std::size_t getMaxFileSize() const;
};
