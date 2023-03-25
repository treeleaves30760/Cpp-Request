#include <iostream>
#include "../Request.h"
using namespace std;
int main()
{
    Request re;
    string s;
    s = re.Get("https://example.com");
    cout << s << endl;
    return 0;
}
