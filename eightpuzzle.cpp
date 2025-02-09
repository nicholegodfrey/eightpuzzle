#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

//returns heuristic val for misplaced tile
int aStarMisplacedTile(vector<int> puzzle){
    int val = 0;
    for(int i = 0; i < 9; i++){
        //dont care abt blank
        if(puzzle[i] != 0){
            //counts if any tile is in wrong spot
            if(puzzle[i] != i+1){
                val++;
            }
        }
    }
    return val;  
}
//returns heuristic val for manhattan
int aStarManhattanDistance(vector<int> puzzle){
    int val = 0;
    for(int i=0; i<9; i++){
        //dont care abt blank
        if(puzzle[i] != 0){
            // the correct position of the tile
            int correctX = (puzzle[i]-1)/3;
            int correctY = (puzzle[i]-1)%3;
            //position rn
            int coordX = i/3;
            int coordY = i%3;
            //add up distances
            val += abs(correctX - coordX) + abs(correctY - coordY);
        }
    }
    return val;
}

//prints out the puzzle board
void print(vector<int>& puzzle) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0){
            cout << endl;
        } 
        cout << puzzle[i] << " ";
    }
    cout << endl;
}
 
//used for UNIFORM SEARCH, bc no heuristic
//replaces heuristic with 0
//following general search algorithm from class
void uniformCost(vector<int> puzzle) {
    //making my queue (mineheap)
    //stores depth+ heuristc and the current puzzle state
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater <pair<int, vector<int>>>> minHeap;
    //reference to goal state
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    //keeps track of depths for each step in the puzzle
    map<vector<int>, int> depth;
    set<vector<int>> visited;

    //making the head node (initial state of puzzle)
    minHeap.push(make_pair(0, puzzle));
    visited.insert(puzzle); //mark as done
    depth[puzzle] = 0;

    //moves for the tiles makes it easier for later
    vector<int> xmoves= {1, -1,0,0};
    vector<int> ymoves= {0,0,1,-1};

    int nodesExpanded = 0;
    int queueSize=0;
    
    //my loop do, will return if empty
    while(!minHeap.empty()){
        //KEEPS the max val
        queueSize = max(queueSize, (int)minHeap.size());
        vector<int> curr = minHeap.top().second;
        //remove the front
        minHeap.pop();
        nodesExpanded++;
        //where we at
        cout << "The best state to expand with a g(n) = " << depth[curr] << " and h(n) = " << 0 << " is..." << endl;
        print(curr);

        //check if were done !! (if goal test, return)
        if(curr == goal){
            cout << "Solved!" << endl;
            cout<< "Solution Depth: " << depth[curr] << endl;
            cout << "Nodes Expanded: " << nodesExpanded << endl;
            cout << "Max Queue Size: " << queueSize << endl;
            return; //done

        }
        //else, we are expanding
        //now solving
        //find the blank space within the vector
        int blank= find (curr.begin(), curr.end(), 0) - curr.begin();
        int blankX= blank / 3;
        int blankY= blank % 3;

        //iterates through possible moves
        for(int i=0; i<4; i++){
            int newX= blankX + xmoves[i];
            int newY= blankY + ymoves[i];
            //check if new position works
            if(newX >= 0 && newX < 3 && newY >= 0 && newY < 3){
                //perform a swap !! within the vector
                vector<int> next = curr;
                swap(next[blankX*3 + blankY], next[newX*3 + newY]);
                //check if the new state has been visited
                if(visited.find(next) == visited.end()){
                    visited.insert(next);
                    depth[next] = depth[curr] + 1;
                    minHeap.push(make_pair(depth[next], next));
                    
                    
                }
            }
        }


    }
}

//used for A* SEARCH, bc has heuristic
//following general search algorithm from class
void generalSearch(vector<int> puzzle,function<int(vector<int>)> heuristic) {
    //making my queue (mineheap)
    //stores depth+ heuristc and the current puzzle state
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater <pair<int, vector<int>>>> minHeap;
    //reference to goal state
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    //keeps track of depths for each step in the puzzle
    map<vector<int>, int> depth;
    set<vector<int>> visited;

    //making the head node (initial state of puzzle)
    minHeap.push(make_pair(heuristic(puzzle), puzzle));
    visited.insert(puzzle); //mark as done
    depth[puzzle] = 0;

    //moves for the tiles makes it easier for later
    vector<int> xmoves= {0,0,1, -1};
    vector<int> ymoves= { 1, -1, 0,0};

    int nodesExpanded = 0;
    int queueSize=0;
    
    //my loop do, will return if empty
    while(!minHeap.empty()){
        //KEEPS the max val
        queueSize = max(queueSize, (int)minHeap.size());
        vector<int> curr = minHeap.top().second;
        //remove the front
        minHeap.pop();
        nodesExpanded++;
        //where we at
        cout << "The best state to expand with a g(n) = " << depth[curr] << " and h(n) = " << heuristic(curr) << " is..." << endl;
        print(curr);

        //check if were done !! (if goal test, return)
        if(curr == goal){
            cout << "Solved!" << endl;
            cout<< "Solution Depth: " << depth[curr] << endl;
            cout << "Nodes Expanded: " << nodesExpanded << endl;
            cout << "Max Queue Size: " << queueSize << endl;
            return; //done

        }
        //else, we are expanding
        //now solving
        //find the blank space within the vector, convert to reg coords
        int blank= find (curr.begin(), curr.end(), 0) - curr.begin();
        int blankX= blank / 3;
        int blankY= blank % 3;

        //iterates through possible moves
        for(int i=0; i<4; i++){
            int newX= blankX + xmoves[i];
            int newY= blankY + ymoves[i];
            //check if new position works
            if(newX >= 0 && newX < 3 && newY >= 0 && newY < 3){
                //perform a swap !! within the vector
                vector<int> next = curr;
                swap(next[blank], next[newX*3 + newY]);
                //check if the new state has been visited
                if(visited.find(next) == visited.end()){
                      visited.insert(next);
                    depth[next] = depth[curr] + 1;
                    //essentially g(n) + h(n)!, pushes onto heap
                    minHeap.push(make_pair(depth[next]+ heuristic(next), next));
                  
                }
            }
        }


    }
}

int main(){
    int userPuzzle=0;
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
    //puzzle to solve
    vector<int> puzzle;
    cout << "Enter '1' if you would like to use a default puzzle. Enter '2' if you would like to enter your own puzzle. " << endl;
    cin >> userPuzzle;
    if(userPuzzle==1){
        cout << "Select a difficulty level for the puzzle. Enter '1' for easy, '2' for medium, or '3' for hard." << endl;
    }
    else if(userPuzzle==2){
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
        
        }
    else{
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }
    
    cout << "Enter 1 to use Uniform Cost Search, 2 to use A* with the Misplaced Tile heuristic, and 3 to use A* with the Manhattan Distance heuristic to solve the eight puzzle: "<< endl;
    cin >> userChoice;
    if(userChoice == 1){
        uniformCost(puzzle);
    }
    else if(userChoice == 2){
        generalSearch(puzzle, aStarMisplacedTile);
    }
    else if(userChoice == 3){
        generalSearch(puzzle, aStarManhattanDistance);
    }
    else{
        cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
    } 
}

