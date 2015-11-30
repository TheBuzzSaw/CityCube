#ifndef ADDRESS128_HPP
#define ADDRESS128_HPP

#include <SDL_stdinc.h>
#include <iostream>

namespace SDL2TK
{
    union Address128
    {
        Uint8 bytes[16];
    };

    std::ostream& operator<<(
        std::ostream& stream,
        const Address128& address128);
}

#endif
