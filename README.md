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

Include the Resquest.h in your code

```c++
#include "Request.h"
```

The simple example of the code

```c++
Request re;
string s;
s = re.Get("https://example.com");
cout << re.get_content() << endl;   // output the response of URL
cout << re.get_status() << endl;    // output the response status
```
