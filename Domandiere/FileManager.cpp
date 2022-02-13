#include "FileManager.h"
using namespace std;

vector<Quesito> FileManager::LetturaDomandiere(string pathFileDomande, string pathFilePunteggi)
{
	//read text file where are the question and answer
	//to fill the class call also LetturaPunteggi()
	vector<Quesito> output;

	ifstream lettura(pathFileDomande);
	if (!lettura)
		exit(1);
	
	string domanda, risposta;
	int id = 0;
	while (getline(lettura, domanda) && getline(lettura, risposta))
	{
		//read and fill the vector<Quesito>
		output.push_back(Quesito(domanda, risposta, id, LetturaPunteggi(pathFilePunteggi, id)));
		id++;
	}
	lettura.close();
	return output;
}

bool FileManager::ScritturaPunteggi(string pathFile, vector<Quesito> domande)
{
	//save the binary file: save ID, nproposte, nerrori
	ofstream scrivi(pathFile, ios::out | ios::binary);
	if (!scrivi)
		return false;

	try {
		for (auto i : domande)
		{
			int id = i.ID();

			scrivi.write(reinterpret_cast<char*>(&id), sizeof(int));
			scrivi.write(reinterpret_cast<char*>(&i.score.nProposte), sizeof(int));
			scrivi.write(reinterpret_cast<char*>(&i.score.nErrori), sizeof(int));
		}
	}
	catch (...)
	{
		scrivi.close();
		return false;
	}
	scrivi.close();
	return true;
}

Score FileManager::LetturaPunteggi(string pathFile, int ID)
{
	//read the bin file where are saved the score 
	ifstream leggi(pathFile, ios::in | ios::binary);
	Score output = {0,0};

	if (!leggi)
		return output;
	streamoff bytes = (sizeof(ID) + sizeof(output.nProposte) + sizeof(output.nErrori)) * ID; //the cursor position

	leggi.seekg(bytes, ios::beg);

	leggi.read(reinterpret_cast<char*>(&ID), sizeof(int));
	leggi.read(reinterpret_cast<char*>(&output.nProposte), sizeof(int));
	leggi.read(reinterpret_cast<char*>(&output.nErrori), sizeof(int));

	return output;
}