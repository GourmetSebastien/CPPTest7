#include "Option.h"
/*********************************************/
/*********Constructeur et Destructeur*********/
/*********************************************/

Option::Option()
{
	#ifdef DEBUG
		cout<<"Constructeur par défault de Option"<<endl;
	#endif
	
	code="Pas de code";
	intitule="Pas d'intitulé";
	prix=0;
}
Option::Option(string c,string i,float p)
{
	#ifdef DEBUG
		cout<<"Constructeur d'initialisation de Option"<<endl;
	#endif

	setCode(c);
	setIntitule(i);
	setPrix(p);
}
Option::Option(const Option &source)
{
	#ifdef DEBUG
		cout<<"Constructeur de copie d'option"<<endl;
	#endif

	setCode(source.getCode());
	setIntitule(source.getIntitule());
	setPrix(source.getPrix());
}
Option::~Option()
{
	#ifdef DEBUG
		cout<<"Destructeur d'Option"<<endl;
	#endif

}
/*********************************************/
/***********Getters et Setters****************/
/*********************************************/
string Option::getCode()const
{
	return code;
}
string Option::getIntitule()const
{
	return intitule;
}
float Option::getPrix()const
{
	return prix;
}
void Option::setCode(string c)
{
	if(c.length()!=4)
	{
		throw OptionException("Taille code option invalide");
	}
	code = c;
}
void Option::setIntitule(string i)
{
	if(i.length()<1)
	{
		throw OptionException("Taille intitule invalide");
	}
	intitule=i;
}
void Option::setPrix(float p)
{
	if(p<=0)
	{
		throw OptionException("Prix option invalide");
	}
	prix=p;
}

/*********************************************/
/************Modeles publiques****************/
/*********************************************/

void Option::Affiche()const
{
	cout<<"Code: "<<code<<endl<<"Intitulé: "<<intitule<<endl<<"Prix :"<<prix<<endl;
}

void Option::Save(ofstream &fichier)const
{
	int taille;
	string chaine=getCode();

	taille=chaine.size();
	fichier.write((char*)&taille,sizeof(int));
	fichier.write((char*)chaine.data(),taille*sizeof(char));
	chaine=getIntitule();
	taille=chaine.size();
	fichier.write((char*)&taille,sizeof(int));
	fichier.write((char*)chaine.data(),taille*sizeof(char));
	fichier.write((char*)&prix,sizeof(float));
}
void Option::Load(ifstream &fichier)
{
	string chaine;
	float prix;
	int taille;

	fichier.read((char*)&taille,sizeof(int));
	chaine.resize(taille);
	fichier.read((char*)chaine.data(),taille*sizeof(char));
	setCode(chaine);
	fichier.read((char*)&taille,sizeof(int));
	chaine.resize(taille);
	fichier.read((char*)chaine.data(),taille*sizeof(char));
	setIntitule(chaine);
	fichier.read((char*)&prix,sizeof(float));
	setPrix(prix);
}
/*********************************************/
/*************Surchage opérateur**************/
/*********************************************/
ostream& operator<<(ostream& s,const Option& source)
{
	s<<"Code: "<<source.getCode()<<endl<<"Intitulé: "<<source.getIntitule()<<endl<<"Prix :"<<source.getPrix()<<endl;
	return s;
}
istream& operator>>(istream& s,Option& source)
{
	string code,intitule;
	float prix;

	cout<<"Code:";
	getline(cin,code);
	if(code.length()!=4)
	{
		throw OptionException("Taille code option invalide");
	}
	cout<<endl;

	cout<<"intitule:";
	getline(cin,intitule);
	if(intitule.length()<1)
	{
		throw OptionException("Taille intitule invalide");
	}
	cout<<endl;

	cout<<"Prix:";
	cin>>prix;
	if(prix<=0)
	{
		throw OptionException("Prix option invalide");
	}
	cout<<endl;

	source.setCode(code);
	source.setIntitule(intitule);
	source.setPrix(prix);

	return s;
}
Option Option::operator--()
{
	if(getPrix()<=50)
	{
		throw OptionException("Prix négatif");
	}
	setPrix(getPrix()-50);
	return (*this);
}
Option Option::operator--(int n)
{
	if(((*this).getPrix())<=50)
	{
		throw OptionException("Prix négatif");
	}
	Option tmp(*this);
	(*this).setPrix(((*this).getPrix()-50));
	
	return tmp;
}