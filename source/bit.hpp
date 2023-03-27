#pragma once
#include <iostream>

enum class Bit {
    Undefined, Low, High
};

std::ostream& operator<<(std::ostream& os, Bit bit)
{
    switch (bit) {
    case Bit::Undefined: os << 'X'; break;
    case Bit::High:      os << 'H'; break;
    case Bit::Low:       os << 'L'; break;
    }
    return os;
}
