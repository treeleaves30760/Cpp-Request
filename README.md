# CPP_request

## Descriptiom

This is a c++ library for web API request, you can use it like Python's request.

## Installation

Use g++ for compile

```bash
g++ -std=c++11 -lcurl [your_program_files]
```

You can run the following command for testing and example

```bash
g++ -std=c++11 -lcurl test/test.cpp Request.cpp Request.h
```

And run command below to test

```bash
./a.out
```

## Usage

The `Request` class provides simple methods to make HTTP GET and POST requests. Here's a guide on how to use them:

### Initialization

First, you need to create an instance of the `Request` class.

```cpp
Request request;
```

### Making a GET Request

To make a GET request, use the `Get` method and provide the URL.

```cpp
std::string response = request.Get("https://example.com");
```

### Making a POST Request

For POST requests, use the `Post` method. Provide the URL and a JSON object with the data.

```cpp
nlohmann::json jsonData;
jsonData["key"] = "value";
std::string response = request.Post("https://example.com/post", jsonData);
```

### Accessing Response Data

Once you've made a request, you can access the response data, HTTP status, headers, cookies, and history as follows:

- Response content:

```cpp
std::string content = request.get_content();
```

- HTTP status:

```cpp
int status = request.get_status();
```

- Response headers:

```cpp
std::string headers = request.get_response_header();
```

- Cookies:

```cpp
std::string cookies = request.get_response_cookie();
```

- History (Note: this feature may not be fully implemented yet):

```cpp
std::string history = request.get_response_history();
```
