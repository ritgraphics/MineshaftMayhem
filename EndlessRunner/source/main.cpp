
#include <vix_game.h>
#include <vix_curl_singleton.h>
#include <vix_jsoncpp.h>
#include <inttypes.h>

int main(int argc, char* argv[])
{
    //using namespace Vixen;

    //Curl::Initialize();

    //std::string s;

    //Json::Value root;
    //Json::Reader r;
    //

    //s = Curl::HTTPGet("https://mineshaftmayhem.herokuapp.com/");
    //

    //if (r.parse(s, root))
    //{
    //    if (root.isArray())
    //    {
    //        Json::ArrayIndex numItems = root.size();
    //        
    //        for (uint32_t i = 0; i < numItems; i++)
    //        {
    //            Json::Value _child = root[i];

    //            Json::Value _name = _child["name"];
    //            if (_name.empty())
    //                continue;
    //            Json::Value _score = _child["score"];
    //            if (_score.empty())
    //                continue;
    //            printf("Array: [ name: %s, score: %f]\n",
    //                _child["name"].asString().c_str(),
    //                _child["score"].asDouble());
    //        }
    //    }
    //}
    //
    //s.clear();

    //curl_easy_setopt(Curl::CurlInstance(), CURLOPT_POSTFIELDS, "name=Jake&score=3000");

    ///*Curl::HTTPPost("https://mineshaftmayhem.herokuapp.com/",
    //    "name=Matt&score=3000");*/

    //Curl::DeInitialize();

	Vixen::Game _game;

	return _game.Run();

    //CURL* curl;
    //CURLcode res;

    //curl_global_init(CURL_GLOBAL_DEFAULT);

    //curl = curl_easy_init();
    //if (curl)
    //{
    //    //struct string s;
    //    //init_string(&s);

    //    std::string s;
    //    curl_easy_setopt(curl, CURLOPT_URL, "https://mineshaftmayhem.herokuapp.com/");
    //    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Vixen::Curl::WriteFunc);
    //    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);



    //    res = curl_easy_perform(curl);

    //    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=fuckface&score=99999999999999999999999999999");

    //    res = curl_easy_perform(curl);

    //    /*if (res == CURLE_OK)
    //    {
    //    char* ct;
    //    res = curl_easy_getinfo(curl, CURLINFO_CONTENT)
    //    }*/

    //    /* always cleanup */
    //    curl_easy_cleanup(curl);
    //}

    //curl_global_cleanup();

    return 0;
}