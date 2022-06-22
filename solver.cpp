#ifndef SOLVER
#define SOLVER

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>

struct weightedWord
{
    std::string word;
    int weight;
    bool operator<(const weightedWord& a) const
    {
        return weight > a.weight;
    }
};

//Function Declarations:
std::string getMode();
std::string getAnswersString(std::string&, std::ifstream&);
std::vector<int> weighLetters(std::string&);
std::vector<weightedWord> getAnswersVector(std::string&, std::ifstream&, std::vector<int>&);
int weighWords(std::string&, std::vector<int>& weightedLetters);

void displayModes();
void displayModeSelected(std::string&);


int main()
{
    //Get Mode for answers.txt
    std::ifstream inputFile;
    std::string fileName = getMode();
    displayModeSelected(fileName);

    //Weigh answer letters for all words
    std::string answerString = getAnswersString(fileName, inputFile);
    std::vector<int> weightedLetters = weighLetters(answerString);
    
    //Weigh answer words based on letter weight
    std::vector<weightedWord> potentialAnswers = getAnswersVector(fileName, inputFile, weightedLetters);

    //Sort potiential Answers
    std::sort(potentialAnswers.begin(), potentialAnswers.end());

    int count = 0;
    for(auto i : potentialAnswers)
    {
        std::cout << i.word << " " << i.weight << '\n';
        if(count == 4)
            break;
        count++;
    }
        
}

std::string getMode()
{
    std::string fileName;
    enum wordleModes {test, nyt, original};

    displayModes();
    int mode;
    std::cin >> mode;

    switch (mode)
    {
    case test:
        fileName = "test-answers.txt";
        break;
    case nyt:
        fileName = "wordle-nyt-answers-alphabetical.txt";
        break;
    case original:
        fileName = "wordle-answers-alphabetical.txt";
        break;
    default:
        break;
    }
    return fileName;
}

std::string getAnswersString(std::string& fileName, std::ifstream& inputFile)
{
    std::string answersString, temp;
    inputFile.open(fileName, std::ios::in);
    while(getline(inputFile, temp))
    {
        answersString += temp;
    }
    inputFile.close();
    return answersString;
}

std::vector<int> weighLetters(std::string& answersString)
{
    std::vector<int> alphabet(26,0);
    int i = 0;
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        alphabet[i] = std::count(answersString.begin(), answersString.end(), ch);
        i++;
    }
    return alphabet;
}

std::vector<weightedWord> getAnswersVector(std::string& fileName, std::ifstream& inputFile, std::vector<int>& weightedLetters)
{
    std::vector<weightedWord> vect;
    std::string tempString;
    weightedWord tempWord;
    inputFile.open(fileName, std::ios::in);
    while(getline(inputFile, tempString))
    {
        tempWord.word = tempString;
        tempWord.weight = weighWords(tempString, weightedLetters);
        vect.push_back(tempWord);
    }
    inputFile.close();
    return vect;
}

int weighWords(std::string& word, std::vector<int>& weightedLetters)
{
    int tempWeight = 0;
    for(int i = 0; i < 5; i++)
    {
        for(char ch = 'a'; ch <= 'z'; ch++)
        {
            if(word[i] == ch)
            {
                tempWeight += weightedLetters[ch - 97];
                break;
            }
        }
    }
    return tempWeight;
}

void displayModes()
{
    std::cout << "Select Mode: [0]test, [1]nyt, or [2]original ";
}

void displayModeSelected(std::string& fileName)
{
    std::cout << "Opening " << fileName << "...\n";
}


#endif