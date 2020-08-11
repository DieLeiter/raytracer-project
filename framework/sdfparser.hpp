#ifndef SDFPARSER_HPP
#define SDFPARSER_HPP

#include "scenegraph.hpp"

class SdfParser{
public:
	void parse(char* argv[], Scenegraph &scene) const;
};

#endif