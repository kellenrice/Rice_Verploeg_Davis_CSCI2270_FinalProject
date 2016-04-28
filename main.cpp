#include <iostream>
#include <cstdlib>
#include "GameBoard.h"


using namespace std;

int main(int argc, char* argv[]){   //Takes in the txt filenames as arguments
    cout<<"Welcome to Jeopardy!\n"<<endl;

    int choice;
    string input;
    bool menuExit = false;  //Used to receive user input and control the menu loops

    GameBoard table;        //Create the game board

//////////////////////BUILD GAMEBOARD HERE//////////////////////////
//First menu will let the user choose to build their own game
//or to play one of the premade games in the txt files

    while(choice!=4 && !menuExit){
        cout<<"Would you like to:"<<endl;
        cout<<"1. Play game #1"<<endl;
        cout<<"2. Play game #2"<<endl;
        cout<<"3. Create your own custom game (need 12 questions and answers)"<<endl;
        cout<<"4. Quit"<<endl;

        getline(cin, input);
        choice = stoi(input);

        switch(choice){
        case 1:     //Load Game 1 Into Table
            cout<<"Setting up game 1...\n"<<endl;
            menuExit = table.buildPremade(argv[1]); //Will return true if the load is successful
            if(!menuExit){  //If not, this error will be displayed and the program will end
                cout<<"There was an issue loading the file.\nMake sure the program's arguments are the correct files."<<endl;
                return 1;
            }
            break;

        case 2:     //Load Game 2 Into Table
            cout<<"Setting up game 2...\n"<<endl;
            menuExit = table.buildPremade(argv[2]); //Same concept as choice 1
            if(!menuExit){
                cout<<"There was an issue loading the file.\nMake sure the program's arguments are the correct files."<<endl;
                return 1;
            }
            break;

        case 3:     //Begin Process to Create Custom Game
            table.buildCustom();
            menuExit = true;
            break;

        case 4:     //Quit
            cout<<"Thanks for playing!"<<endl;
            return 1;
            break;

        default:
            cout<<"Please enter a valid option."<<endl;

        }

    }

//////////////////////////////////////////////////////////////////////
//This is where gameplay begins. The menu controls the players' options
//and will run the game, switching players each turn.

    choice = 0;
    menuExit = false;
    string currentPlayer = "1";
    int p1 = 0;
    int p2 = 0;     //Variables to store each player's score
    int points = 0;
    while(choice!=4 && !menuExit){
        cout<<"Player "<<currentPlayer<<", it's your turn."<<endl;
        cout<<"Would you like to:"<<endl;
        cout<<"1. Answer a Question"<<endl;
        cout<<"2. Print Game Board"<<endl;
        cout<<"3. View Score"<<endl;
        cout<<"4. Quit"<<endl;
        getline(cin, input);
        choice = atoi(input.c_str());
        cout<<endl;
        questionNode* tempNode = new questionNode();

        switch(choice){
        case 1:     //Answer a question
            tempNode = table.findQuestion();        //Returns the node of the desired question
            points = table.answerQuestion(tempNode);    //Ask user for answer and determine correctness. Returns
                                                        //the amount of points scored (-1 for error)
            if(points != -1){
                if(currentPlayer == "1"){
                    p1 = p1+points;
                    currentPlayer = "2";
                }else{
                    p2 = p2+points;
                    currentPlayer = "1";    //Add points and switch player
                }
            }else{
                cout<<"Question or category not found. Please try again.\n"<<endl;
            }
            menuExit = table.isEmpty();     //When all questions are answered, game ends
            break;
        case 2:     //Print Table
            table.printAll();
            break;
        case 3:
            cout<<"Player 1: "<<p1<<endl;   //Displays the point values for each player
            cout<<"Player 2: "<<p2<<endl;
            break;
        case 4:     //Quit Game
            cout<<"Thanks for playing!"<<endl;
            return 1;
            break;
        default:
            cout<<"Please enter a valid option."<<endl;
        }


    }

    cout<<"\n\n=====GAME OVER=====\n"<<endl;
    cout<<"Final Score:"<<endl;                     //Gives game over message and will display the final
    cout<<"    Player 1: "<<p1<<endl;               //sore and congratulate the winner of the game
    cout<<"    Player 2: "<<p2<<"\n"<<endl;
    if(p1>p2){
        cout<<"Congratulations Player 1! You won!"<<endl;
    }else if(p2>p1){
        cout<<"Congratulations Player 2! You won!"<<endl;
    }else if(p2==p1){
        cout<<"It's a tie!"<<endl;
    }


    cout<<"\nThanks for playing!\n"<<endl;

}
