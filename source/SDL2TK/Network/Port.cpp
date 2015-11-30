#include "Port.hpp"
#include <SDL_endian.h>

namespace SDL2TK
{
    Port Port::FromHostValue(Uint16 hostValue)
    {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        return { hostValue };
#else
        return { SDL_Swap16(hostValue) };
#endif
    }

    Uint16 Port::ToHostValue() const
    {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        return networkValue;
#else
        return SDL_Swap16(networkValue);
#endif
    }

    std::ostream& operator<<(std::ostream& stream, const Port& port)
    {
        return stream << port.ToHostValue();
    }
}
