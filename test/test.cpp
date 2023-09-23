#include <iostream>
#include "../Request.h"
#include "../nlohmann/json.hpp"
using namespace std;
int test_get()
{
    cout << "----------Start GET test----------\n";
    try
    {
        Request re;
        string s;
        s = re.Get("https://example.com");
        cout << re.get_content() << endl;
        cout << "HTTP Status: " << re.get_status() << endl;
        cout << "Response Header: " << re.get_response_header() << endl;
        cout << "Response Cookie: " << re.get_response_cookie() << endl;
        cout << "Response History: " << re.get_response_history() << endl;
    }
    catch (...)
    {
        cout << "----------End GET test----------\n";
        return -1;
    }
    cout << "----------End GET test----------\n\n";
    return 0;
}

int test_post()
{
    cout << "----------Start Post test----------\n\n";
    try
    {
        string testURL = "https://jsonplaceholder.typicode.com/posts";
        Request request;

        nlohmann::json jsonData;
        jsonData["title"] = "Test Title";
        jsonData["body"] = "Test Body";
        jsonData["userId"] = 1;

        string response = request.Post(testURL, jsonData);
        int statusCode = request.get_status();

        if (!response.empty())
        {
            std::cout << "HTTP Status: " << statusCode << std::endl;
            std::cout << "Response: " << response << std::endl;
            cout << "Response Header: " << request.get_response_header() << endl;
            cout << "Response Cookie: " << request.get_response_cookie() << endl;
            cout << "Response History: " << request.get_response_history() << endl;
        }
        else
        {
            std::cerr << "Failed to send POST request" << std::endl;
        }
    }
    catch (...)
    {
        cout << "----------End POST test----------\n\n";
        return -1;
    }
    cout << "----------End POST test----------\n\n";
    return 0;
}

int main()
{
    int get_status = test_get();
    int post_status = test_post();
    string get_str = (get_status == 0) ? "Pass" : "Fail!";
    string post_str = (post_status == 0) ? "Pass" : "Fail!";
    cout << "----------Check List----------\n";
    cout << "Get  Status: " << get_str << endl;
    cout << "Post Status: " << post_str << endl;
    cout << "----------End Check List----------\n";
    return 0;
}
