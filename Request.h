#include <curl/curl.h>
#include <iostream>
class Request
{
private:
    /* data */
public:
    Request();
    ~Request();
    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
    std::string Get(const std::string &URL);
};
