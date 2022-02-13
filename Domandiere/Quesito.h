#pragma once
#include <iostream>
#include <string>
#include <vector>
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
	vector<string> _risposte;
	int _id;

public:
	Quesito(string domanda, vector<string> risposte, int id, Score punteggi);	

	//readable variables
	string Domanda() const { return _domanda; }
	vector<string> Risposte() const { return _risposte; }
	int ID() const { return _id; }

	Score score;
};