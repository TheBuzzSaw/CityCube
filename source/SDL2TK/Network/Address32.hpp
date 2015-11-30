#ifndef ADDRESS32_HPP
#define ADDRESS32_HPP

#include <SDL_stdinc.h>
#include <iostream>

namespace SDL2TK
{
    union Address32
    {
        Uint8 bytes[4];
        Uint32 address;
    };

    std::ostream& operator<<(std::ostream& stream, const Address32& address32);
}

#endif

