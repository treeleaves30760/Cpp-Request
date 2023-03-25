#include "Request.h"
Request::Request(/* args */)
{
}

Request::~Request()
{
}

size_t Request::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string *str = (std::string *)userdata;
    str->append(ptr, size * nmemb);
    return size * nmemb;
}

std::string Request::Get(const std::string &URL)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Error initializing libcurl" << std::endl;
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK)
    {
        std::cerr << "Error performing HTTP request: " << curl_easy_strerror(result) << std::endl;
        return "";
    }

    return response_string;
}