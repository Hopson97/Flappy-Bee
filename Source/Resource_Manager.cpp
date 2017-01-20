#include "Resource_Manager.h"

Texture_Manager::Texture_Manager()
{
    std::string path ("Res/Textures/");

    registerResource(Texture_ID::Splash_SFML, path + "Splash/SFML.png");
    registerResource(Texture_ID::Splash_MH,   path + "Splash/MatthewHopson.png");

    registerResource(Texture_ID::Bee,           path + "Bee.png");
    registerResource(Texture_ID::Pipe_Top,      path + "Pipe_Top.png");
    registerResource(Texture_ID::Pipe_Bottom,   path + "Pipe_Bottom.png");

    registerResource(Texture_ID::Ground,   path + "Ground.png");


    registerResource(Texture_ID::Background_Nature, path + "bg.jpg");
}

Font_Manager::Font_Manager()
{
    std::string path ("Res/Fonts/");

    registerResource(Font_ID::RS, path + "rs.ttf");
}

Sound_Manager::Sound_Manager()
{
    std::string path ("Res/Sounds/");

    registerResource(Sound_ID::Splash_Made_By, path + "MadeBy.ogg");

    registerResource(Sound_ID::Hit,     path + "sfx_hit.wav");
    registerResource(Sound_ID::Wing,    path + "sfx_wing.wav");
    registerResource(Sound_ID::Score,   path + "sfx_point.wav");
}
