#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
void aStarMisplacedTile(){
    
}

void aStarManhattanDistance(){
    
}

void print(vector<int>& puzzle) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0){
            cout << endl;
        } 
        cout << puzzle[i] << " ";
    }
    cout << endl;
}

void search(vector<int> puzzle, int heuristic) {
    
}

int main(){
    int userChoice=0;
    int num1=0;
    int num2=0;
    int num3=0;
    int num4=0;
    int num5=0;
    int num6=0;
    int num7=0;
    int num8=0;
    int num9=0;
    vector<int> puzzle;

    
    cout << "Enter your 8 puzzle board. First enter in the first row, with 3 numbers and spaces between each number. Use 0 to represent the blank space." << endl;
    cin >> num1 >> num2 >> num3;
    puzzle.push_back(num1);
    puzzle.push_back(num2);
    puzzle.push_back(num3);
    cout << "Please enter the second row of your puzzle board." << endl;
    cin >> num4 >> num5 >> num6;
    puzzle.push_back(num4);
    puzzle.push_back(num5);
    puzzle.push_back(num6);
    cout << "Please enter the third row of your puzzle board." << endl;
    cin >> num7 >> num8 >> num9;
    puzzle.push_back(num7);
    puzzle.push_back(num8);
    puzzle.push_back(num9);
    cout << "Enter 1 to use Uniform Cost Search, 2 to use A* with the Misplaced Tile heuristic, and 3 to use A* with the Manhattan Distance heuristic to solve the eight puzzle: "<< endl;
    cin >> userChoice;
    if(userChoice == 1){
        search(puzzle,0);
    }
    else if(userChoice == 2){
       // search(puzzle,);
    }
    else if(userChoice == 3){
       // search(puzzle,);
    }
    else{
        cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
    } 
    
}

