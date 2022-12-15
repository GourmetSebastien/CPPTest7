#include "Voiture.h"
/*********************************************/
/*********Constructeur et Destructeur*********/
/*********************************************/

Voiture::Voiture()
{
	#ifdef DEBUG
		cout<<"Constructeur par défault de Voiture"<<endl;
	#endif
	
	setNom("Projet sans nom");
	setModele(modele);
}
Voiture::Voiture(string n,Modele source)
{
	#ifdef DEBUG
		cout<<"Constructeur d'initialisation de Voiture"<<endl;
	#endif

	setNom(n);
	setModele(source);
}
Voiture::Voiture(const Voiture &source)
{
	#ifdef DEBUG
		cout<<"Constructeur de copie de Voiture"<<endl;
	#endif

	setNom(source.getNom());
	setModele(source.getModele());

	for(int cpt=0;cpt<5;cpt++)
	{
		if(source.options[cpt]!=NULL)
		{
			options[cpt]=new Option;
			options[cpt]->setCode(source.options[cpt]->getCode());
			options[cpt]->setIntitule(source.options[cpt]->getIntitule());
			options[cpt]->setPrix(source.options[cpt]->getPrix());
		}
	}
}
Voiture::~Voiture()
{
	#ifdef DEBUG
		cout<<"Destructeur de Voiture"<<endl;
	#endif
	int cpt=0;

	while(cpt<5)
	{
		if(options[cpt]!=NULL)
		{
			delete options[cpt];
		}
		cpt++;
	}
}
/*********************************************/
/***********Getters et Setters****************/
/*********************************************/
string Voiture::getNom()const
{
	return nom;
}
Modele Voiture::getModele()const
{
	return modele;
}
void Voiture::setNom(string n)
{
	nom = n;
}
void Voiture::setModele(Modele source)
{
	modele.setNom(source.getNom());
	modele.setPuissance(source.getPuissance());
	modele.setMoteur(source.getMoteur());
	modele.setPrixDeBase(source.getPrixDeBase());
}

/*********************************************/
/************Modeles publiques****************/
/*********************************************/

void Voiture::Affiche()const
{
	int cpt=0;
	cout<<"Nom du projet :"<<nom<<endl;
	modele.Affiche();

	while(cpt<5)
	{
		cout<<"Option"<<(cpt+1)<<":";
		if(options[cpt]!=NULL)
		{
			options[cpt]->Affiche();
		}
		else
		{
			cout<<"Pas d'option"<<endl;
		}
		cpt++;
		cout<<endl;
	}
}
void Voiture::AjouteOption(const Option &source)
{
	int cpt=0,i=0;
	while(options[cpt]!=NULL && cpt<5)
	{
		cpt++;
	}
	if(cpt==5)
	{
		throw OptionException("Plus de place pour une nouvelle option");
	}
	else
	{
		while(i<5)
		{
			if(options[i]!=NULL && options[i]->getCode()==source.getCode())
			{
				throw OptionException("Option déjà existante");
			}
			i++;
		}
		options[cpt]=new Option;
		options[cpt]->setCode(source.getCode());
		options[cpt]->setIntitule(source.getIntitule());
		options[cpt]->setPrix(source.getPrix());
	}	
}
float Voiture::getPrix()const
{
	float total=0;
	int cpt=0;

	while(cpt<5)
	{
		if(options[cpt]!=NULL)
		{
			total+=options[cpt]->getPrix();
		}
		cpt++;
	}
	total+=modele.getPrixDeBase();
	return total;
}
void Voiture::RetireOption(string m)
{
	int cpt=0;

	while(cpt<5)
	{
		if(options[cpt]!=NULL && (m==options[cpt]->getCode()))
		{
			delete options[cpt];
			options[cpt]=NULL;
			cpt=6;
		}
		else
		{
			cpt++;
		}
	}
	if(cpt==5)
	{
		throw OptionException("Option inexistante");
	}
}
void Voiture::Save()const
{
	int cpt=0;
	string chaine=nom + ".car";

	ofstream fichier(chaine,ios::out);
	int taille=getNom().size();
	fichier.write((char*)&taille,sizeof(int));
	fichier.write((char*)getNom().data(),taille*sizeof(char));
	modele.Save(fichier);
	for(int i=0;i<5;i++)
	{
		if(options[i]!=NULL)
		{
			cpt++;
		}
	}
	fichier.write((char*)&cpt,sizeof(int));
	for(int i=0;i<5;i++)
	{
		if(options[i]!=NULL)
		{
			options[i]->Save(fichier);
		}
	}
	fichier.close();
}
void Voiture::Load(string n) 
{
	string chaine;
	int taille,cpt;
	Option tmp;

	ifstream fichier(n,ios::in);
	fichier.read((char*)&taille,sizeof(int));
	chaine.resize(taille);
	fichier.read((char*)chaine.data(),taille*sizeof(char));
	setNom(chaine);
	modele.Load(fichier);
	fichier.read((char*)&cpt,sizeof(int));
	for(int i=0;i<cpt;i++)
	{
		tmp.Load(fichier);
		AjouteOption(tmp);
	}
	fichier.close();
}
/*********************************************/
/*************Surchage opérateur**************/
/*********************************************/
Voiture& Voiture::operator=(const Voiture& source)
{
	setNom(source.getNom());
	setModele(source.getModele());
	for(int cpt=0;cpt<5;cpt++)
	{
		if(options[cpt]!=NULL)
			delete options[cpt];
		options[cpt]=NULL;
		if(source.options[cpt]!=NULL)
		{
			AjouteOption(*(source.options[cpt]));
		}
	}
	return(*this);
}
Voiture operator+ (const Voiture& source,const Option& o)
{
	Voiture v(source);
	v.AjouteOption(o);
	return v;
}
Voiture operator+ (const Option& o,const Voiture& source)
{
	return source+o;
}
Voiture Voiture::operator-(const string code)const
{
	Voiture v(*this);
	v.RetireOption(code);
	return v;
}
Voiture Voiture::operator-(const Option& o)const
{
	Voiture v(*this);
	v.RetireOption(o.getCode());
	return v;
}
int Voiture::operator<(const Voiture& source)const
{
	if(getPrix()<source.getPrix())
	{
		return 1;
	}
	return 0;
}
int Voiture::operator>(const Voiture& source)const
{
	if(getPrix()>source.getPrix())
	{
		return 1;
	}
	return 0;
}
int Voiture::operator==(const Voiture& source)const
{
	if(getPrix()==source.getPrix())
	{
		return 1;
	}
	return 0;
}
ostream& operator<<(ostream& s,const Voiture& source)
{
	s<<"Nom du projet:"<<source.getNom()<<endl;

	s<<source.getModele()<<endl;

	for(int cpt=0;cpt<5;cpt++)
	{
		s<<"Option"<<(cpt+1)<<":";
		if(source.options[cpt]!=NULL)
			s<<*(source.options[cpt]);
		else
			s<<"Pas d'option"<<endl;
		s<<endl;
	}
	return s;
}
Option* Voiture::operator[](int i)const
{
	return (*this).options[i];
}