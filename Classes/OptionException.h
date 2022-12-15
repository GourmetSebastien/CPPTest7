#ifndef OPTIONEXCEPTION_H
#define	OPTIONEXCEPTION_H

#include "Exception.h"
#include <iostream>
#include <string>

class OptionException: public Exception
{
	private:

	public:
		OptionException();
		OptionException(string);
		OptionException(const OptionException&);
		~OptionException();
};
#endif