#include "OptionException.h"
/*********************************************/
/*********Constructeur et Destructeur*********/
/*********************************************/
OptionException::OptionException()
{
	#ifdef DEBUG
		cout<<"Constructeur par défault de OptionException"<<endl;
	#endif
}
OptionException::OptionException(string m):Exception(m)
{
	#ifdef DEBUG
		cout<<"Constructeur d'initialisation de OptionException"<<endl;
	#endif
}
OptionException::OptionException(const OptionException&source):Exception(source)
{
	#ifdef DEBUG
		cout<<"Constructeur de copie de OptionException"<<endl;
	#endif

	setMessage(source.getMessage());
}
OptionException::~OptionException()
{
	#ifdef DEBUG
		cout<<"Destructeur de copie de OptionException"<<endl;
	#endif
}


