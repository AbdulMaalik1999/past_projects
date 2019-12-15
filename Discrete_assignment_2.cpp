#include<iostream>
#include<fstream>
#include<conio.h>
#include <windows.h> 
#include<string>
#include<queue>

using namespace std;

ifstream fin ("puzzle.txt");

queue<string> gameTree;
int moves;
bool found, solved, used[3628800];
string goalState, initialState, currentState, movedState, backTrack[3628800];
char in;

void findGoalState();
void output ();

void input()
{
   	cout<<"If you want to change the order of the input please change in the file "<<endl;
    cout << "Press Enter to continue" << endl;
    
    while(!kbhit());       
    
    initialState = "";

    for (int i = 0; i < 9; i++)
    {
        fin >> in;
        initialState += in;
    }

    currentState = initialState;
    
    findGoalState();
}

void outputState()
{
    system("CLS");

    cout << "-------" << endl;
    for (int j = 0; j < 7; j += 3)
    {
        char a = currentState[j], b = currentState[j + 1], c = currentState[j + 2];

        if (a == '0')
            a = ' ';
        if (b == '0')
            b = ' ';
        if (c == '0')
            c = ' ';

        cout << "|" << a << "|" << b << "|" << c << "|" << endl;
        cout << "-------" << endl;
    }
    cout << endl;
}

void findGoalState()
{
   goalState = "012345678";
}
// This funtion helps to identify if a state has been previously repeated or not.
int encode(string board)
{
    int encrypt[9] =
        {
            9*8*7*6*5*4*3*2, 8*7*6*5*4*3*2, 7*6*5*4*3*2, 6*5*4*3*2, 5*4*3*2, 4*3*2, 3*2, 2, 1
        };
    int value = 0;

    for (int i = 0; i < 9; i++)
    {
        value += (int(board[i]) - 47) * (encrypt[i]);
    }

    return value;
}

bool moveUp (string next)
{
    movedState = next;

    int from = movedState.find('0', 0), to; 

    if (from < 6)
        to = from + 3;
    else
        return false;

    movedState = movedState.substr(0, from) + movedState[to] + movedState.substr(from + 1, movedState.length() - from);
    movedState.replace(to, 1, "0");

    return true;

}

bool moveDown (string next)
{
    movedState = next;

    int from = movedState.find('0', 0), to;

    if (from > 2)
        to = from - 3;
    else
        return false;

    movedState = movedState.substr(0, from) + movedState[to] + movedState.substr(from + 1, movedState.length() - from);
    movedState.replace(to, 1, "0");

    return true;

}

bool moveRight (string next)
{
    movedState = next;

    int from = movedState.find('0', 0), to;

    if (from % 3 != 0)
        to = from - 1;
    else
        return false;

    movedState = movedState.substr(0, from) + movedState[to] + movedState.substr(from + 1, movedState.length() - from);
    movedState.replace(to, 1, "0");

    return true;
}

bool moveLeft (string next)
{
    movedState = next;

    int from = movedState.find('0', 0), to;

    if (from % 3 != 2)
        to = from + 1;
    else
        return false;

    movedState = movedState.substr(0, from) + movedState[to] + movedState.substr(from + 1, movedState.length() - from);
    movedState.replace(to, 1, "0");

    return true;

}

void output(string parentState[])
{
    for (int i = 0; i <= moves; i++)
    {
        currentState = parentState[i];
        outputState();
        
        Sleep(500);   
    }
}

void solve()
{
    cout << "Solving " << endl;
    Sleep(500);
    
    gameTree.push(currentState);

    found = false;

    while(!gameTree.empty())
    {
        int up = gameTree.size();

        for (int i = 1; i <= up; i++)
        {
            string next = gameTree.front();

            if (next == goalState)
            {
                found = true;
                break;
            }

            gameTree.pop();

            if(moveUp(next) && !used[encode(movedState)])
            {
                gameTree.push(movedState);
                backTrack[encode(movedState)] = next;
            }

            if(moveDown(next) && !used[encode(movedState)])
            {
                gameTree.push(movedState);
                backTrack[encode(movedState)] = next;
            }

            if(moveRight(next) && !used[encode(movedState)])
            {
                gameTree.push(movedState);
                backTrack[encode(movedState)] = next;
            }

            if(moveLeft(next) && !used[encode(movedState)])
            {
                gameTree.push(movedState);
                backTrack[encode(movedState)] = next;
            }

            used[encode(next)] = true;
        }

        if (found)
            break;

        moves ++;
    }

    string backTrackState = goalState, parentState[moves + 1];
    int index = moves;

    while(true)
    {
        parentState[index] = backTrackState;
        backTrackState = backTrack[encode(backTrackState)];

        if (backTrackState == currentState)
        {
            parentState[--index] = backTrackState;
            break;
        }

        --index;
    }

    output(parentState);
}

int main()
{
  

    input();

    outputState();

    while(true)
    {
        if (kbhit())
        {
            
                solve();
                break;
            

            outputState();
        }
        
    }

    
    
    
        cout << "It took " << moves << " moves  to solve it." << endl;
       
    
    cout << endl;
    
    system("PAUSE");
    
}
