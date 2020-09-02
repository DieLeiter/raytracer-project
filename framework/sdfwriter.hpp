#ifndef SDFWRITER_HPP
#define SDFWRITER_HPP

#include <string>

class SdfWriter{
public:
	void write(float progress_percentage, std::string const& filename) const;
};

#endif