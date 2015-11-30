#ifndef PORT_HPP
#define PORT_HPP

#include <SDL_stdinc.h>
#include <iostream>

namespace SDL2TK
{
    struct Port
    {
        Uint16 networkValue;

        static Port FromHostValue(Uint16 hostValue);
        Uint16 ToHostValue() const;
    };

    std::ostream& operator<<(std::ostream& stream, const Port& port);
}

#endif
