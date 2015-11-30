#include "Address32.hpp"

namespace SDL2TK
{
    std::ostream& operator<<(std::ostream& stream, const Address32& address32)
    {
        return stream
            << static_cast<int>(address32.bytes[0])
            << '.' << static_cast<int>(address32.bytes[1])
            << '.' << static_cast<int>(address32.bytes[2])
            << '.' << static_cast<int>(address32.bytes[3]);
    }
}
