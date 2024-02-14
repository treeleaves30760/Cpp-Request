#include "Request.h"
Request::Request()
{
    content = "";
    curl = curl_easy_init();
    http_status = -1;
    response_header = "";
    response_cookie = "";
    response_history = "";
    curl_headers = NULL;
}

Request::~Request()
{
    if (curl_headers)
    {
        curl_slist_free_all(curl_headers);
    }
}

size_t Request::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string *str = (std::string *)userdata;
    str->append(ptr, size * nmemb);
    return size * nmemb;
}

std::string Request::Get(const std::string &URL)
{
    if (!curl)
    {
        std::cerr << "Error initializing libcurl" << std::endl;
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_header);
    curl_easy_setopt(curl, CURLOPT_COOKIELIST, &response_cookie);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
    curl_easy_cleanup(curl);

    if (result != CURLE_OK)
    {
        std::cerr << "Error performing HTTP request: " << curl_easy_strerror(result) << std::endl;
        return "";
    }
    return content;
}

std::string Request::Post(const std::string &URL, const nlohmann::json &jsonData)
{
    if (!curl)
    {
        std::cerr << "Error initializing libcurl" << std::endl;
        return "";
    }

    std::string postData = jsonData.dump();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_header);
    curl_easy_setopt(curl, CURLOPT_COOKIELIST, &response_cookie);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_header);
    curl_easy_setopt(curl, CURLOPT_COOKIELIST, &response_cookie);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (result != CURLE_OK)
    {
        std::cerr << "Error performing HTTP request: " << curl_easy_strerror(result) << std::endl;
        return "";
    }
    return content;
}

HTTPSTATUS Request::get_status()
{
    return http_status;
}

std::string Request::get_content()
{
    return content;
}

void Request::SetHeaders(const nlohmann::json &headers)
{

    if (curl_headers)
    {
        curl_slist_free_all(curl_headers);
        curl_headers = NULL;
    }

    for (auto &[name, value] : headers.items())
    {
        std::string header = name + ": " + value.get<std::string>();
        curl_headers = curl_slist_append(curl_headers, header.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
}

nlohmann::json Request::GetHeaders()
{
    nlohmann::json headers;
    struct curl_slist *header_list;
    curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &header_list);
    for (struct curl_slist *next = header_list; next; next = next->next)
    {
        std::string header = next->data;
        std::string name = header.substr(0, header.find_first_of('='));
        std::string value = header.substr(header.find_first_of('=') + 1);
        headers[name] = value;
    }
    return headers;
}