#include "Exception.h"
/*********************************************/
/*********Constructeur et Destructeur*********/
/*********************************************/
Exception::Exception()
{
	#ifdef DEBUG
		cout<<"Constructeur par défault de Exception"<<endl;
	#endif

	setMessage("Pas de message");
}
Exception::Exception(string m)
{
	#ifdef DEBUG
		cout<<"Constructeur d'initialisation de Exception"<<endl;
	#endif

	setMessage(m);
}
Exception::Exception(const Exception&source)
{
	#ifdef DEBUG
		cout<<"Constructeur de copie de Exception"<<endl;
	#endif

	setMessage(source.getMessage());
}
Exception::~Exception()
{
	#ifdef DEBUG
		cout<<"Destructeur de copie de Exception"<<endl;
	#endif
}
/*********************************************/
/***********Getters et Setters****************/
/*********************************************/
void Exception::setMessage(string m)
{
	message=m;
}
string Exception::getMessage()const
{
	return message;
}

