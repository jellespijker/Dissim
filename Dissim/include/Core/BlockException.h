#ifndef DISSIM_BLOCKEXCEPTION_H_
#define DISSIM_BLOCKEXCEPTION_H_

#include <iostream>
#include <exception>
#include <string>

namespace dissim {

class BlockException : public std::exception {

public:
	BlockException(std::string m = "Block exception!") : msg(m) {};
	~BlockException() throw() {};
	const char* what() const throw() { return msg.c_str(); }

private:
	std::string msg;
};

}

#endif
