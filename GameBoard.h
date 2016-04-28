#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <iostream>
#include <cstdlib>

using namespace std;

struct questionNode{
    string question;
    string answer;
    string category;
    int points;
    questionNode* next;
    questionNode* prev;

    questionNode(){};

    questionNode(string in_category){
        category = in_category;
        next = NULL;
        prev = NULL;
    };

    questionNode(string in_question, string in_answer, string in_category, int in_points){
        question = in_question;
        answer = in_answer;
        category = in_category;
        points = in_points;
        next = NULL;
        prev = NULL;
    };
};



class GameBoard
{
    public:
        GameBoard();
        ~GameBoard();
        bool buildPremade(char* fname);
        bool isFull(string categoryName);
        bool isFinished();
        void buildCustom();
        void printAll();
        bool isEmpty();
        int answerQuestion(questionNode* qNode);
        questionNode* findQuestion();
        void deleteNode(questionNode* qNode);

        int indexFinder(string cat_search);

    private:
        string *categories = new string[4];
        questionNode* gameBoard[4];
};

#endif // GAMEBOARD_H
