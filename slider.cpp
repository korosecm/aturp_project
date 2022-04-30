#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

int n = 9;
vector<int> final_state = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
map<vector<int>, bool> visit;
vector <vector<int>> samples;

struct node {
    vector<int> state;
    node* parent;

    node()
    {
        parent = NULL;
    }
};

void OpenAndFill(string filename) {
    ifstream my_file;
    my_file.open(filename, ios::out);
    string line;
    vector<int> temp;
    vector<int> sample;
    int numOfSamples;
    int chng = 0;

    while (getline(my_file, line))
    {
 
        istringstream str(line);
        int n;
        while (str >> n)
        {
            temp.push_back(n);
            
        }

    }
    numOfSamples = temp[0];
    //temp.erase(temp.begin());

    for (size_t i = 0; i < numOfSamples; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            sample.push_back(temp[chng + j + 1]);
        }
        chng += 9;
        samples.push_back(sample);
        sample.clear();
        
    }

}

//Pogledamo ce se da sploh resit z inverzijami
int getInvCount(vector<int> arr)
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i + 1; j < 9; j++)
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

bool isSolvable(vector<int> puzzle)
{
    // Prestejemo inverzije
    int invCount = getInvCount(puzzle);

    // Ce je sodo stevilo iverzij.
    return (invCount % 2 == 0);
}


void printState(vector<int> state)
{
    for (int i = 0; i < 9; )
    {
        for (int j = 0; j < 3; ++j, ++i)
            cout << state[i] << " ";
        cout << endl;
    }
    cout << endl;
}

void printPath(node* state)
{
    vector<node*> path;
    while (state)
    {
        path.push_back(state);
        state = state->parent;
    }

    cout << path.size() - 1 << endl;

    //Za izpisovanje vsakega stanja
    /*for (int i = path.size() - 1; i >= 0; --i)
        printState(path[i]->state);*/
}

node* createNewState(node* state, int x, int y)
{
    node* new_state = new node();
    new_state->state = state->state;
    swap(new_state->state[x], new_state->state[y]);

    return new_state;
}

void BFS(node* start_state)
{


    visit[start_state->state] = 1;

    int pos, row, col;

    node* curr = new node(), * child = new node();
    queue<node*> q;
    q.push(start_state);



    while (!q.empty())
    {
        curr = q.front();
        q.pop();

        if (curr->state == final_state)
        {
            printPath(curr);
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            if (curr->state[i] == 0)
            {
                pos = i;
                break;
            }
        }
        row = pos / 3;
        col = pos % 3;

        if (col != 0)
        {
            child = createNewState(curr, pos, pos - 1);

            if (visit[child->state] == 0)
            {
                visit[child->state] = 1;
                child->parent = curr;
                q.push(child);
            }
        }

        if (col != 2)
        {
            child = createNewState(curr, pos, pos + 1);

            if (visit[child->state] == 0)
            {
                visit[child->state] = 1;
                child->parent = curr;
                q.push(child);
            }
        }

        if (row != 0)
        {
            child = createNewState(curr, pos, pos - 3);

            if (visit[child->state] == 0)
            {
                visit[child->state] = 1;
                child->parent = curr;
                q.push(child);
            }
        }

        if (row != 2)
        {
            child = createNewState(curr, pos, pos + 3);

            if (visit[child->state] == 0)
            {
                visit[child->state] = 1;
                child->parent = curr;
                q.push(child);
            }
        }
    }
}

int main(int argc, char **argv)
{


   /* int x;
    node* start_state = new node();

    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        start_state->state.push_back(x);
    }

    BFS(start_state);*/
    auto start = chrono::steady_clock::now();

    OpenAndFill(argv[1]);
    
    
    
    for (int i = 0; i < samples.size(); i++)
    {
        node* start_state = new node();
        
        for (int j = 0; j < 9; j++)
        {
 
            start_state->state = samples[i];
        }
 
        if (isSolvable(samples[i])) {
            BFS(start_state);
        }
        else {
            cout << "0 0" << endl;
        }

        
 
        start_state->state.clear();
        visit.clear();

    }

    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in milliseconds: "
    << chrono::duration_cast<chrono::milliseconds>(end - start).count()
    << " ms" << endl;

    return 0;
}