#include <curl/curl.h>
#include <iostream>
#include "nlohmann/json.hpp"

#define HTTPSTATUS int
class Request
{
private:
    std::string content;
    std::string response_header;
    std::string response_cookie;
    std::string response_history;
    CURL *curl;
    HTTPSTATUS http_status;

public:
    Request();
    ~Request();

    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
    std::string Get(const std::string &URL);
    std::string Post(const std::string &URL, const nlohmann::json &jsonData);

    HTTPSTATUS get_status();
    std::string get_content();
    std::string get_response_header() const { return response_header; }
    std::string get_response_cookie() const { return response_cookie; }
    std::string get_response_history() const { return response_history; }
};
