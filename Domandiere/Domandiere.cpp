// Domandiere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <ctime>
#include "Quesito.h"
#include "FileManager.h"
using namespace std;

//==========GLOBAL VARS
string pathDomandiere = ".\\domandiere.dmt"; //text domandiere
string pathScores = ".\\score.dmb";         //bin domandiere
vector<Quesito> a;
const int maxQuests = 10;
const int maxAnswers = 4;

//==========SYSTEM FUNCTIONS
void pc()
{
#ifdef _WIN32
#define CLS "cls"
#define PAUSE "pause"
#else
#define CLS "clear"
#define PAUSE "read -n 1 -s -p \"Press a key to continue...\""
#endif

	system(PAUSE);
	system(CLS);
}


//==========APP FUNCTIONS
void info()
{
	cout << "Copyright \xB8 Visual Laser 10 New\n" <<
		"Other products https://sites.google.com/view/visuallaser10/download-prodotti" <<
		endl;
	pc();

#ifdef _WIN32
	//open website
	system("start msedge https://sites.google.com/view/visuallaser10/download-prodotti");
#endif
}

void show(bool scoreToo = false)
{
	//print datas
	cout << "\n=======================================" << endl;
	for (vector<Quesito>::iterator t = a.begin(); t != a.end(); t++)
	{
		cout << "Question no. " << (int)(t)->ID() << ":\n" << //print question
			"\t" << t->Domanda() << "\n";

		for(auto risp : t->Risposte())
			cout << "\tAnswer: " << risp << endl; //print answers

		if (scoreToo)
		{
			//print score too
			cout << "Score\n\tNo. of total attemptions: " << t->score.nProposte << "\n" <<
				"\tNo. of incorrect attemptions: " << t->score.nErrori << "\n" <<
				"\tNo. of correct attemptions: " << t->score.nProposte - t->score.nErrori << "\n" << endl;
		}
		cout << "=======================================" << endl;
	}
}

vector<string> replies(int IDofQuestion, int& wherePutCorrect)
{
	//max 4 answers
	vector<string> output;
	while (output.size() < maxAnswers)
	{
		int n = 0;
		do {
			n = rand() % a.size();
		} while (n == IDofQuestion || find(output.begin(), output.end(), a[n].Risposte()[0]) != output.end());
		//if the extracted number is already extracted || is equal to correct -> restract

		output.push_back(a[n].Risposte()[0]);//insert the casual answer
	}

	wherePutCorrect = rand() % maxAnswers;
	output[wherePutCorrect] = a[IDofQuestion].Risposte()[0]; //in one of them put the correct answer

	return output;
}

vector<string> replies(int IDofQuestion, int IDofCorrect, int& wherePutCorrect)
{
	//if is a multiple ansers' question
	vector<string> output;
	int answerToSet = a[IDofQuestion].Risposte().size(); //number of answer

	output.resize(answerToSet); //allocate the vector

	for (int i = 0; i < a[IDofQuestion].Risposte().size(); i++) //foreach answer, put it in a random empty place in vector
	{
		int e = 0;
		do {
			e = rand() % answerToSet;
		} while (!output[e].empty());
		output[e] = a[IDofQuestion].Risposte()[i];

		if (i == IDofCorrect)
			wherePutCorrect = i;
	}
	return output;
}

int chiediRisposta(int nOfAnswers)
{
	//return a number from 1 to 4, that point to the user input
	char repl;

	do {
		repl = '\0';

		cout << "Select ";
		for (int i = 0; i < nOfAnswers; i++) {
			cout <<(char)('A' + i) << ", "; //print Select A, B, C, ...
		}
		cout << ": ";

		cin >> repl;
		cin.clear();
		//cin.ignore('\n', 80);

		repl = toupper(repl);

	} while (repl < 'A' || repl > (char)('A' + nOfAnswers));

	return (int)(repl - 65);
}

void domandiere()
{
	//this function ask 10 questions
	//each questions has the correct answer, and another 3 random answer
	//ever foreach question set the score variables, and save in bin file
	vector<int> asked = { -1 }; //-1, otherwise the 0 question never comes out
	srand(time(NULL));

	while (asked.size() <= maxQuests) //can ask max 10 quests
	{
		int random = rand() % (a.size()); // get an ID random quest
		if (find(asked.begin(), asked.end(), random) == asked.end())//if the question isn't already asked, ask it
		{
			asked.push_back(random);

			//ask the question
			int wherePutCorrect = 0; //where the answer randomize put the correct one, int from 1 to 4
			vector <string> answersToAsk;

			if (a[asked.back()].Risposte().size() == 1)
			{
				//if is a one answer's question
				answersToAsk = replies(a[asked.back()].ID(), wherePutCorrect);//random 4 aswers, where one of them is correct
			}
			else
			{
				//if is a multiple answers' question
				answersToAsk = replies(a[asked.back()].ID(), 0, wherePutCorrect);
			}

			cout << "\n=======================================\nQuestion no. " << asked.size() - 1 << ":\n\n" << a[asked.back()].Domanda(); //write the question

			char letter = 'A'; //letter -> A] B] C] D]
			for (auto i : answersToAsk)
			{
				cout << "\n" << letter++ << "] " << i; //write the answers, i is the answer <string>
			}
			cout << "\n" << endl;

			//answers
			a[asked.back()].score.nProposte++; //increase the number of proposal
			if (chiediRisposta(answersToAsk.size()) == wherePutCorrect) //ask the answer
			{
				cout << "\nCorrect" << endl;
			}
			else
			{
				cout << "\nWrong" << endl;
				a[asked.back()].score.nErrori++; //increase the number of error times
			}

			bool saved = false;
			do {
				saved = FileManager::ScritturaPunteggi(pathScores, a); //write the scores to file
			} while (!saved);
		}
	}

}

char menu()
{
	/*1) domandiere()
	* 2) show all question with correct answer
	* 3) show all question with correct answer with scores
	* 4) reload all files
	* 5) info
	* 6) exit
	*/

	char response = 0;
	cout <<
		"    ____  ____  __  ______    _   ______  ______________  ______\n" <<
		"   / __ \\/ __ \\/  |/  /   |  / | / / __ \\/  _/ ____/ __ \\/ ____/\n" <<
		"  / / / / / / / /|_/ / /| | /  |/ / / / // // __/ / /_/ / __/   \n" <<
		" / /_/ / /_/ / /  / / ___ |/ /|  / /_/ // // /___/ _, _/ /___   \n" <<
		"/_____/\\____/_/  /_/_/  |_/_/ |_/_____/___/_____/_/ |_/_____/ " << endl;

	cout << "Digit:\n" <<
		"1) Domandiere\n" <<
		"2) Show all question\n" <<
		"3) Show all question with scores\n" <<
		"4) Reload all files\n" <<
		"5) Info\n" <<
		"6) Exit\n" <<
		"7) Reset Scores" << endl;


	cin >> response;
	cin.clear();
	cin.ignore(80, '\n');


	switch (response)
	{
	case '1':
		domandiere();
		break;

	case '2':
		show();
		break;

	case '3':
		show(true);
		break;

	case '7':
		remove(pathScores.c_str()); //delete score file
	case '4':
	case '6':
		break;

	case '5':
		info();
		break;


	default:
		cout << "Not valid, retry" << endl;
		break;
	}
	pc();

	return response - 48;

}

bool valid()
{
	if (a.size() < 11)
		return false;

	if (a.back().Risposte().size() == 0)
		return false;

	return true;
}

//=========MAIN FUNCTION
int main()
{
	int response = 0;
	while (response != 6) //if response == 6 exit
	{
		a = FileManager::LetturaDomandiere(pathDomandiere, pathScores);
		if (!valid()) //check if domandiere.dmt is valid file
		{
			cout << "The file is not valid, check if there are\nat least 11 questions with 11 answer in domandiere.dmt" << endl;
			pc();
			return 1;
		}

		response = 0;
		while (response != 4 && response != 6 && response != 7) //if response == 4 || 7 reload all files
		{
			response = menu();
		}
	}
	return 0;
}