#include "FileServerApplication.h"
#include "handlers/RequestFactory.h"
#include "FileServerSubsystem.h"

void FileServerApplication::initialize(Poco::Util::Application &self)
{
    auto sub = new FileServerSubsystem;
    this->addSubsystem(sub);

    try
    {
        Application::initialize(self);
    }
    catch (std::exception &e)
    {
        logger().fatal("Can't start FileServer: %s", static_cast<std::string>(e.what()));
        return;
    }
}

int FileServerApplication::main(const std::vector<std::string> &)
{
    logger().information("Start FileServer on port %i", static_cast<int>(this->getFileServerSubsystem().getPort()));
    waitForTerminationRequest();
    logger().information("Stopping FileServer...");

    return Application::EXIT_OK;
}

const FileServerSubsystem &FileServerApplication::getFileServerSubsystem() const
{
    return this->getSubsystem<FileServerSubsystem>();
}
