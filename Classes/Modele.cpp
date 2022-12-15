#include "Modele.h"
/*********************************************/
/*********Constructeur et Destructeur*********/
/*********************************************/

Modele::Modele()
{
	#ifdef DEBUG
		cout<<"Constructeur par défaut de Modele"<<endl;
	#endif

	puissance=0;
	PrixDeBase=0;
	moteur=Essence;

	//nom=NULL;

	//nom=new char[50];
	//strcpy(nom,"Modele sans nom");

	nom=NULL;
	setNom("Modele sans nom");
}

Modele::Modele(const char *n,int p,Moteur m,float pdb)
{
	#ifdef DEBUG
		cout<<"Constructeur par d'initialisation de Modele ("<<n<<"-"<<p<<"-"<<m<<"-"<<pdb<<")"<<endl;
	#endif

	nom=NULL;
	setNom(n);
	setPuissance(p);
	setMoteur(m);
	setPrixDeBase(pdb);
}

Modele::Modele(const Modele &source)
{
	#ifdef DEBUG
		cout<<"Constructeur de copie de Modele ("<<source.getNom()<<"-"<<source.getPuissance()<<"-"<<source.getMoteur()<<"-"<<source.getPrixDeBase()<<")"<<endl;
	#endif

	nom=NULL;
	setNom(source.getNom());
	setPuissance(source.getPuissance());
	setMoteur(source.getMoteur());
	setPrixDeBase(source.getPrixDeBase());
}

Modele::~Modele()
{
	#ifdef DEBUG
		cout<<"Destructeur de Modele ("<<getNom()<<"-"<<getPuissance()<<"-"<<getMoteur()<<"-"<<getPrixDeBase()<<")"<<endl;
	#endif

	if(nom!=NULL)
		delete[]nom;
}
/*********************************************/
/***********Getters et Setters****************/
/*********************************************/
const char *Modele::getNom()const
{
	return nom;
}

int Modele::getPuissance()const
{
	return puissance;
}

Moteur Modele::getMoteur()const
{
	return moteur;
}

float Modele::getPrixDeBase()const
{
	return PrixDeBase;
}

void Modele::setNom(const char *n)
{
	if(nom!=NULL)
		delete[] nom;	
	nom=new char[strlen(n)+1];
	strcpy(nom,n);
}

void Modele::setPuissance(int p)
{
	if(p>=0)
		puissance=p;
}

void Modele::setMoteur(Moteur m)
{
	moteur=m;
}

void Modele::setPrixDeBase(float pdb)
{
	if(pdb>=0)
		PrixDeBase=pdb;
}

/*********************************************/
/************Modeles publiques****************/
/*********************************************/

void Modele::Affiche()const
{
	cout<<"Modele:"<<nom<<endl<<"Puissance:"<<puissance<<endl<<"Prix de base: "<<PrixDeBase<<endl<<"Type de moteur:";
	switch(moteur)
	{
		case Essence:
			cout<<"Essence"<<endl;
			break;
		case Diesel:
			cout<<"Diesel"<<endl;
			break;
		case Electrique:
			cout<<"Electrique"<<endl;
			break;
		case Hybride:
			cout<<"Hybride"<<endl;
			break;
	}
}
void Modele::Save(ofstream &fichier)const 
{
	int taille;
	
	taille=strlen(nom);
	fichier.write((char*)&taille,sizeof(int));
	fichier.write((char*)nom,taille*sizeof(char));
	fichier.write((char*)&puissance,sizeof(int));
	fichier.write((char*)&moteur,sizeof(Moteur));
	fichier.write((char*)&PrixDeBase,sizeof(float));
}
void Modele::Load(ifstream &fichier)
{
	int taille;
	fstream f;
	char *n;
	int pui;
	float PDB;
	Moteur m;

	fichier.read((char*)&taille,sizeof(int));
	n=new char[taille+1];
	fichier.read((char*)n,taille*sizeof(char));
	setNom(n);
	fichier.read((char*)&pui,sizeof(int));
	setPuissance(pui);
	fichier.read((char*)&m,sizeof(Moteur));
	setMoteur(m);
	fichier.read((char*)&PDB,sizeof(float));
	setPrixDeBase(PDB);
}
/*********************************************/
/*************Surchage opérateur**************/
/*********************************************/
ostream& operator<<(ostream& s,const Modele& source)
{
	s<<"Modele:"<<source.getNom()<<endl<<"Puissance:"<<source.getPuissance()<<endl<<"Prix de base:"<<source.getPrixDeBase()<<endl<<"Type de moteur:";
	switch(source.getMoteur())
	{
		case Essence:
			s<<"Essence"<<endl;
			break;
		case Diesel:
			s<<"Diesel"<<endl;
			break;
		case Electrique:
			s<<"Electrique"<<endl;
			break;
		case Hybride:
			s<<"Hybride"<<endl;
			break;
	}
	return s;
}
istream& operator>>(istream& s,Modele& source)
{
	char nom[30];
	int puissance,tmp;
	Moteur moteur;
	float PrixDeBase;

	cout<<"Modele:";
	fgets(nom,30,stdin);
	cout<<endl;

	cout<<"Puissance:";
	cin>>puissance;
	cout<<endl;

	cout<<"Moteur:";
	cin>>tmp;
	cout<<endl;
	moteur=static_cast<Moteur>(tmp-1);

	cout<<"Prix de base:";
	cin>>PrixDeBase;
	cout<<endl;

	source.setNom(nom);
	source.setPuissance(puissance);
	source.setMoteur(moteur);
	source.setPrixDeBase(PrixDeBase);

	return s;
}