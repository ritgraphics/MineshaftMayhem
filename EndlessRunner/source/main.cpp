
#include <vix_game.h>
#include <vix_curl_singleton.h>
#include <vix_jsoncpp.h>
#include <inttypes.h>

#include <vix_filemanager.h>
#include <vix_inireader.h>

int main(int argc, char* argv[])
{

#pragma region JSON_LEADERBOARD_STUFF
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

#pragma endregion

#pragma region INI_FILE_TESTING

    /*
    Vixen::FileManager::Initialize();

    Vixen::INIReader* _reader = new Vixen::INIReader;

    Vixen::File* file = Vixen::FileManager::OpenFile(Vixen::os_exec_dir() + VTEXT("test.ini"));
    if (file)
    {
        _reader->Load(file->Handle());

        _reader->PrintValues();
    }
    Vixen::FileManager::CloseFile(file);
    Vixen::FileManager::DeInitialize();
    */
#pragma endregion



	Vixen::Game _game;

	return _game.Run();


    return 0;
}