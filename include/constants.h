#pragma once
#include "raylib.h"
/*In C++, a namespace is a mechanism used to group related names (identifiers) under a common name, thereby preventing naming conflicts.*/
/* the inline keyword is a hint to the compiler that it should consider replacing a function call with the actual body of the function directly at the point of the call.*/
//I used google for this definitions, idk C++ :v
namespace cfg {

    namespace window{
        inline constexpr int WIDTH = 800;
        inline constexpr int HEIGHT = 450;
        inline constexpr int TARGET_FPS = 60;
        inline constexpr const char* TITLE = "Computer Science Simulator";
    }
    namespace world {
        inline constexpr float GRAVITY = 1.0f;
        inline constexpr float GROUND_Y= 350.0f;
        inline constexpr bool PLATFORM = true; 

    } // namespace 

    namespace player{
        inline constexpr int SIZE = 50;
        inline constexpr Vector2 START_POS = {50.0f, 50.0f};

    }

    namespace asset { 
        inline constexpr const char* MUSIC = "assets/audio/music/Megalovania.ogg";
        inline constexpr const char* GEORGEIMG  = "assets/sprites/George.jpg";
    }

}