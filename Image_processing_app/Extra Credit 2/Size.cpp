#include "Size.h"
#include <iostream>
#include <iomanip>

Size::Size() {
    this->m_size = 0;
}
Size::Size(unsigned int size) {
    this->m_size = size;
}

unsigned int Size::size() const {
    return m_size;
}

bool Size::isSizeEqual(const Size& dt) {
    if (this->m_size == dt.m_size)
        return 1;
    return 0;
}