#include "Address128.hpp"
#include <iomanip>

namespace SDL2TK
{
    std::ostream& operator<<(
        std::ostream& stream,
        const Address128& address128)
    {
        const Uint8* bytes = address128.bytes;

        stream
            << std::hex << std::setfill('0')
            << std::setw(2) << static_cast<int>(bytes[0])
            << std::setw(2) << static_cast<int>(bytes[1]);

        for (int i = 1; i < 8; ++i)
        {
            int n = i * 2;
            stream
                << ':'
                << std::setw(2) << static_cast<int>(bytes[n])
                << std::setw(2) << static_cast<int>(bytes[n + 1]);
        }

        return stream << std::dec;
    }
}
