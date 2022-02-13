#include "Quesito.h"
using namespace std;

Quesito::Quesito(string domanda, vector<string> risposte, int id, Score punteggi)
{
	this->_domanda = domanda;
	this->_risposte = risposte;
	this->_id = id;
	this->score = punteggi;
}