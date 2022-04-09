#pragma once

class Size {
public:

	Size();
	Size(unsigned int size);

	unsigned int size() const;

	bool isSizeEqual(const Size& dt);

protected:
	unsigned int m_size;
};