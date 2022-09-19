#include "FileServerApplication.h"
#include "handlers/RequestFactory.h"

void FileServerApplication::initServer(const YAML::Node& config)
{
    auto port = config["port"].as<Poco::UInt16>();
    auto hostname = config["host"].as<std::string>() + ":" + config["port"].as<std::string>();

    m_Some = hostname;
    auto* params = new Poco::Net::HTTPServerParams;
    params->setServerName(hostname);
    params->setMaxThreads(config["maxThreads"].as<int>());
    params->setMaxQueued(config["maxQueuedSize"].as<int>());

    m_Serv = std::make_unique<Poco::Net::HTTPServer>(new handlers::RequestFactory, port, params);
}

void FileServerApplication::initialize(Poco::Util::Application &self)
{
    initServer(YAML::LoadFile("config.yaml")["server"]);

    Application::initialize(self);
}

int FileServerApplication::main(const std::vector<std::string> &)
{
    this->addSubsystem(this);
    m_Serv->start();
    logger().information("HTTP Server started on port %hu.", m_Serv->port());
    waitForTerminationRequest();
    logger().information("Stopping HTTP Server...");
    m_Serv->stop();

    return Application::EXIT_OK;
}
