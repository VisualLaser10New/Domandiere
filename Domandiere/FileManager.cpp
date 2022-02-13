#include "FileManager.h"
using namespace std;

vector<string> split(string input, char at, int maxElement)
{
	vector<string> output;
	int end = 0, count = 0;

	while (end < input.size() && count < maxElement)
	{
		end = input.find(at, sizeof(char)); //get the first part of text where to split
		end = (end < 0) ? input.size() : end; //if string not contains the separator, get the full text as one element

		output.push_back(input.substr(0, end));
		input.erase(0, end+1);
		count++;
		end = 0;
	}
	return output;
}

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
		vector<string> risposte = split(risposta, '§', 20); //split in case of multiple answer
		output.push_back(Quesito(domanda, risposte, id, LetturaPunteggi(pathFilePunteggi, id)));
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