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


private:
    struct NumberAndDimension
    {
        std::string_view number;
        std::string_view dimension;
    };

    std::size_t getAsBytesSize(const std::string& size_str) const;
    NumberAndDimension parseDimensionFormat(std::string_view argument) const;
    std::size_t getSizeDimension(std::string_view dim_part) const;
    std::size_t getNumber(std::string_view number_part) const;
};
