#include "FileServerApplication.h"
#include "handlers/RequestFactory.h"
#include "FileServerSubsystem.h"

void FileServerApplication::initialize(Poco::Util::Application &self)
{
    Application::initialize(self);
}

int FileServerApplication::main(const std::vector<std::string> &)
{
    this->addSubsystem(new FileServerSubsystem);

    waitForTerminationRequest();
    logger().information("Stopping HTTP Server...");

    return Application::EXIT_OK;
}
