#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Score
{
	int nProposte = 0;
	int nErrori = 0;
};

class Quesito 
{
private:
	string _domanda;
	string _risposta;
	int _id;

public:
	Quesito(string domanda, string risposta, int id, Score punteggi);	

	//readable variables
	string Domanda() const { return _domanda; }
	string Risposta() const { return _risposta; }
	int ID() const { return _id; }

	Score score;
};