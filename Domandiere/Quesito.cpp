#include "Quesito.h"
using namespace std;

Quesito::Quesito(string domanda, string risposta, int id, Score punteggi)
{
	this->_domanda = domanda;
	this->_risposta = risposta;
	this->_id = id;
	this->score = punteggi;
}