#include "GameBoard.h"
#include <fstream>
#include <cstdlib>

using namespace std;

GameBoard::GameBoard()
{
    //ctor
}

GameBoard::~GameBoard()
{
    //dtor
}

//Format of txt file must be:
//
//category1
//category2
//category3
//category4
//
//Q1-1
//A1
//Q2-1
//A2
//
//Q1-2
//A1
//Q2-2
//A2
//
//etc.
//////////////////////////////////////////

bool GameBoard::buildPremade(char* fname){
    ifstream filein;
    filein.open(fname);
    if (!filein.good()){    //Check to make sure file was opened successfully
        return false;
    }

    for(int i=0; i<4; i++){
		string temp;
        getline(filein, temp);
        cout << "temp is " << temp << "." << endl;
        for (int i = 0; i < temp.length(); i++)
			cout << "\'" << temp[i] << "\'";
		cout << endl;
        categories[i] = temp;
        gameBoard[i] = new questionNode(temp);
    }

    string tempQ, tempA;

    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            getline(filein, tempQ);
            getline(filein, tempA);

            questionNode* tempNode = gameBoard[i];
            while(tempNode->next != NULL){
                tempNode = tempNode->next;
            }
            tempNode->next = new questionNode(tempQ, tempA, categories[i], 20*j+20);
            tempNode->next->prev = tempNode;
        }
    }

    return true;
}

bool GameBoard::isFull(string categoryName){
    int catIndex = indexFinder(categoryName);

    if(catIndex == -1){return false;}
    int counter = 0;

    questionNode* tempNode = gameBoard[catIndex];

    while(tempNode->next != NULL){
        counter++;
        tempNode = tempNode->next;
    }
    if(counter == 3){return true;}

    return false;
}

bool GameBoard::isFinished(){

    bool finished = true;
    for(int i=0; i<4; i++){
        finished = isFull(categories[i]);
        if(!finished){return false;}
    }
    return true;
}

void GameBoard::buildCustom(){
    string tempC, tempQ, tempA;
    int index, pts;
    bool used = false;
    for(int i=0; i<4; i++){
        cout<<"Please enter category number "<<i+1<<":"<<endl;
        getline(cin, tempC);
        for(int j=0; j<i; j++){
            if(tempC == categories[j]){
                used = true;
            }
        }
        if(!used){
            categories[i] = tempC;
        }else{
            cout<<"Category has already been used"<<endl;
            used = false;
            i--;
        }
    }

    for(int i=0; i<4; i++){
        gameBoard[i] = new questionNode(categories[i]);
    }

    while(!isFinished()){
        pts = 20;
        cout<<"Which category would you like to add to?"<<endl;
        getline(cin, tempC);
        index = indexFinder(tempC);
        if(index != -1){
            if(!isFull(tempC)){
                cout<<"What question would you like to add?"<<endl;
                getline(cin, tempQ);
                cout<<"What is the answer to this question?"<<endl;
                getline(cin, tempA);
                questionNode* tempNode = gameBoard[index];
                while(tempNode->next != NULL){
                    pts = pts+20;
                    tempNode = tempNode->next;
                }
                tempNode->next = new questionNode(tempQ,tempA,tempC,pts);
                tempNode->next->prev = tempNode;

            }else{
                cout<<"That category is full. Please choose another."<<endl;
            }
        }else{
            cout<<"Please choose a valid category."<<endl;
        }



    }

}

void GameBoard::printAll(){
    for(int i=0; i<4; i++){
        questionNode* temp = gameBoard[i]->next;
        cout<<"Category: "<<categories[i]<<endl;
        while(temp != NULL){
            cout<<temp->points<<": "<<temp->question<<endl;
            temp = temp->next;
        }
        cout<<endl;
    }
}

bool GameBoard::isEmpty(){
    for(int i=0; i<4; i++){
        questionNode* tempNode = gameBoard[i];
        if(tempNode->next != NULL){
            return false;
        }
    }
    return true;
}

questionNode* GameBoard::findQuestion(){
    string cat, temp;
    int points;
    cout<<"What category would you like to choose from?"<<endl;
    getline(cin, cat);
    int index = indexFinder(cat);
    if(index == -1){
        return NULL;
    }
    questionNode* tempNode = gameBoard[index];
    if(tempNode->next == NULL){
        cout<<"Category "<<cat<<" is empty."<<endl;
        return NULL;
    }
    tempNode = tempNode->next;
    cout<<"Point values available:"<<endl;
    while(tempNode != NULL){
        cout<<tempNode->points<<endl;
        tempNode = tempNode->next;
    }
    tempNode = NULL;
    cout<<"Which would you like to answer?"<<endl;
    getline(cin, temp);
    points = atoi(temp.c_str());
    tempNode = gameBoard[index]->next;
    while(tempNode->points != points && tempNode != NULL){
        tempNode = tempNode->next;
        if(tempNode == NULL){
            break;
        }
    }
    return tempNode;
}

int GameBoard::answerQuestion(questionNode* qNode){
    if(qNode == NULL){
        return -1;
    }
    string answer;
    cout<<qNode->question<<endl;
    getline(cin, answer);
    if(answer == qNode->answer){
        cout<<"Correct! You earned "<<qNode->points<<" points!"<<endl;
        deleteNode(qNode);
        return qNode->points;
    }
    cout<<"That is incorrect."<<endl;
    deleteNode(qNode);
    return 0;
}

void GameBoard::deleteNode(questionNode* qNode){
    if(qNode->next == NULL){
        qNode->prev->next = NULL;
        delete qNode;
        return;
    }
    qNode->next->prev = qNode->prev;
    qNode->prev->next = qNode->next;
    delete qNode;
    return;
}

int GameBoard::indexFinder(string inputString){
	cout << "input string: " << inputString << endl;
	int returnInt = -1;
	for (int i = 0; i < 4; i++)
	{ 
		cout << "----------------" << endl;
		cout << categories[i].length() << endl;
		cout << "\"" << categories[i] << "\"" << endl;
		for (int j = 0; j < categories[i].length(); i++)
		{
			cout << "\'" << categories[j][i] << "\'";
		}
		cout << endl;
	}
    for(int i=0; i<4; i++){
		//cout << inputString << endl;
		//cout << inputString << ": " << endl;
		//cout << "good" << inputString << " == '" << categories[i] << ": " << endl;
        if(inputString == categories[i]){
			cout << "was found" << endl;
            returnInt = i;
        }
    }
	if (returnInt == -1)
		cout<<"Category not found."<<endl;
    return returnInt;
}
