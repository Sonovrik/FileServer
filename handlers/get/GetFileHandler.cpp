#include "GetFileHandler.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/JSON/Parser.h>


void GetFileHandler::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res)
{
    std::string filename;
    Poco::JSON::Parser parser;

    try
    {
        std::string body(std::istreambuf_iterator<char>(req.stream()), {});
        Poco::JSON::Object::Ptr object = parser.parse(body).extract<Poco::JSON::Object::Ptr>();
        filename = object->get("filename").toString();
    }
    catch (Poco::Exception &e)
    {
        return; // set 400
    }

    std::cout << filename << std::endl;

    res.send();
}
