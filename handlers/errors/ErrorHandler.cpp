#include "ErrorHandler.h"

#include <Poco/Path.h>

namespace handlers
{

ErrorHandler::ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status)
    : m_Status(status) {}

void ErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &res)
{
    static const std::string errorsDirectory = "pages/errors/";
    switch (m_Status) {
        case Poco::Net::HTTPResponse::HTTP_NOT_FOUND:
            getErrorPage(Poco::Path::current() + errorsDirectory);
            break;
        case Poco::Net::HTTPResponse::HTTP_CONTINUE:
            break;
        case Poco::Net::HTTPResponse::HTTP_SWITCHING_PROTOCOLS:
            break;
        case Poco::Net::HTTPResponse::HTTP_PROCESSING:
            break;
        case Poco::Net::HTTPResponse::HTTP_OK:
            break;
        case Poco::Net::HTTPResponse::HTTP_CREATED:
            break;
        case Poco::Net::HTTPResponse::HTTP_ACCEPTED:
            break;
        case Poco::Net::HTTPResponse::HTTP_NONAUTHORITATIVE:
            break;
        case Poco::Net::HTTPResponse::HTTP_NO_CONTENT:
            break;
        case Poco::Net::HTTPResponse::HTTP_RESET_CONTENT:
            break;
        case Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT:
            break;
        case Poco::Net::HTTPResponse::HTTP_MULTI_STATUS:
            break;
        case Poco::Net::HTTPResponse::HTTP_ALREADY_REPORTED:
            break;
        case Poco::Net::HTTPResponse::HTTP_IM_USED:
            break;
        case Poco::Net::HTTPResponse::HTTP_MULTIPLE_CHOICES:
            break;
        case Poco::Net::HTTPResponse::HTTP_MOVED_PERMANENTLY:
            break;
        case Poco::Net::HTTPResponse::HTTP_FOUND:
            break;
        case Poco::Net::HTTPResponse::HTTP_SEE_OTHER:
            break;
        case Poco::Net::HTTPResponse::HTTP_NOT_MODIFIED:
            break;
        case Poco::Net::HTTPResponse::HTTP_USE_PROXY:
            break;
        case Poco::Net::HTTPResponse::HTTP_TEMPORARY_REDIRECT:
            break;
        case Poco::Net::HTTPResponse::HTTP_PERMANENT_REDIRECT:
            break;
        case Poco::Net::HTTPResponse::HTTP_BAD_REQUEST:
            break;
        case Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED:
            break;
        case Poco::Net::HTTPResponse::HTTP_PAYMENT_REQUIRED:
            break;
        case Poco::Net::HTTPResponse::HTTP_FORBIDDEN:
            break;
        case Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED:
            break;
        case Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE:
            break;
        case Poco::Net::HTTPResponse::HTTP_PROXY_AUTHENTICATION_REQUIRED:
            break;
        case Poco::Net::HTTPResponse::HTTP_REQUEST_TIMEOUT:
            break;
        case Poco::Net::HTTPResponse::HTTP_CONFLICT:
            break;
        case Poco::Net::HTTPResponse::HTTP_GONE:
            break;
        case Poco::Net::HTTPResponse::HTTP_LENGTH_REQUIRED:
            break;
        case Poco::Net::HTTPResponse::HTTP_PRECONDITION_FAILED:
            break;
        case Poco::Net::HTTPResponse::HTTP_REQUEST_ENTITY_TOO_LARGE:
            break;
        case Poco::Net::HTTPResponse::HTTP_REQUEST_URI_TOO_LONG:
            break;
        case Poco::Net::HTTPResponse::HTTP_UNSUPPORTED_MEDIA_TYPE:
            break;
        case Poco::Net::HTTPResponse::HTTP_REQUESTED_RANGE_NOT_SATISFIABLE:
            break;
        case Poco::Net::HTTPResponse::HTTP_EXPECTATION_FAILED:
            break;
        case Poco::Net::HTTPResponse::HTTP_IM_A_TEAPOT:
            break;
        case Poco::Net::HTTPResponse::HTTP_ENCHANCE_YOUR_CALM:
            break;
        case Poco::Net::HTTPResponse::HTTP_MISDIRECTED_REQUEST:
            break;
        case Poco::Net::HTTPResponse::HTTP_UNPROCESSABLE_ENTITY:
            break;
        case Poco::Net::HTTPResponse::HTTP_LOCKED:
            break;
        case Poco::Net::HTTPResponse::HTTP_FAILED_DEPENDENCY:
            break;
        case Poco::Net::HTTPResponse::HTTP_TOO_EARLY:
            break;
        case Poco::Net::HTTPResponse::HTTP_UPGRADE_REQUIRED:
            break;
        case Poco::Net::HTTPResponse::HTTP_PRECONDITION_REQUIRED:
            break;
        case Poco::Net::HTTPResponse::HTTP_TOO_MANY_REQUESTS:
            break;
        case Poco::Net::HTTPResponse::HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE:
            break;
        case Poco::Net::HTTPResponse::HTTP_UNAVAILABLE_FOR_LEGAL_REASONS:
            break;
        case Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR:
            break;
        case Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED:
            break;
        case Poco::Net::HTTPResponse::HTTP_BAD_GATEWAY:
            break;
        case Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE:
            break;
        case Poco::Net::HTTPResponse::HTTP_GATEWAY_TIMEOUT:
            break;
        case Poco::Net::HTTPResponse::HTTP_VERSION_NOT_SUPPORTED:
            break;
        case Poco::Net::HTTPResponse::HTTP_VARIANT_ALSO_NEGOTIATES:
            break;
        case Poco::Net::HTTPResponse::HTTP_INSUFFICIENT_STORAGE:
            break;
        case Poco::Net::HTTPResponse::HTTP_LOOP_DETECTED:
            break;
        case Poco::Net::HTTPResponse::HTTP_NOT_EXTENDED:
            break;
        case Poco::Net::HTTPResponse::HTTP_NETWORK_AUTHENTICATION_REQUIRED:
            break;
        default: return;
    }
}

void ErrorHandler::getErrorPage(Poco::Path&& path_to_error_sources)
{
    // open and return sources
}

}