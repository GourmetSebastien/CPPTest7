#ifndef VOITURE_H
#define VOITURE_H

#include "Modele.h"
#include "Option.h"
#include "OptionException.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Voiture
{
	friend Voiture operator+(const Option&,const Voiture&);
	friend Voiture operator+(const Voiture&,const Option&);
	friend ostream& operator<<(ostream& s,const Voiture&);

	private:
		string nom;
		Modele modele;
		Option* options[5]={};
	public:
		Voiture();
		Voiture(string,Modele);
		Voiture(const Voiture &);
		~Voiture();

		void setNom(string);
		void setModele(Modele);

		string getNom()const;
		Modele getModele()const;

		void Affiche()const;
		void AjouteOption(const Option&);
		void RetireOption(string);
		float getPrix()const;

		Voiture& operator=(const Voiture&);
		Voiture operator-(const Option&) const;
		Voiture operator-(string) const;
		int operator<(const Voiture&) const;
		int operator>(const Voiture&) const;
		int operator==(const Voiture&) const;
		Option* operator[](int) const;

		void Save()const;
		void Load(string);
};

#endif 