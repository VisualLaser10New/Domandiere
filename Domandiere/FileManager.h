#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Quesito.h"
using namespace std;

namespace FileManager
{
	vector<Quesito> LetturaDomandiere(string pathFileDomande, string PathFilePunteggi);

	bool ScritturaPunteggi(string pathFile, vector<Quesito> domande);

	Score LetturaPunteggi(string pathFile, int ID);
}

