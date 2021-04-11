#include "addext.h"

add addext(int _rline) {
    add add_;
    _rline = _rline & 0x0000FFFF;
    add_.number = (_rline & 0x0000FF00) >> 8;
    add_.offset = _rline & 0x000000FF;
    return add_;
}

int getAdd(add _addin) {
    return (_addin.number << 8) + _addin.offset;
}