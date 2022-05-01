#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <chrono>

#include "windows.h"
#include "psapi.h"

using namespace std;
vector <vector<int>> samples;

class Puzzle {
public:
	int p[3][3];
	int f, g;

	Puzzle(string st) {
		f = 0;
		g = 0;
		int k = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				p[i][j] = st[k++] - '0';
			}
		}
	}

	void display() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << p[i][j] << " ";
			}
			cout << endl;
		}
	}

	string toString() {
		string st = "123456780";
		int k = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				st[k++] = p[i][j] + '0';
			}
		}
		return st;
	}


	int manhDist() {	
		int md = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				switch (p[i][j])
				{
				case 1:
					md += abs(i - 0) + abs(j - 0);
					break;
				case 2:
					md += abs(i - 0) + abs(j - 1);
					break;
				case 3:
					md += abs(i - 0) + abs(j - 2);
					break;
				case 4:
					md += abs(i - 1) + abs(j - 0);
					break;
				case 5:
					md += abs(i - 1) + abs(j - 1);
					break;
				case 6:
					md += abs(i - 1) + abs(j - 2);
					break;
				case 7:
					md += abs(i - 2) + abs(j - 0);
					break;
				case 8:
					md += abs(i - 2) + abs(j - 1);
					break;
				}
			}
		}
		return md;
	}

	bool goal_test() {
		string goal = "123456780";
		string cur = toString();
		if (goal == cur) {
			return 1;
		}
		return 0;
	}

	void updateF() {
			f = 0;
			int manDistance = manhDist();
			f = manDistance + g;		
	}

	void fgSet() {
		f = 0;
		g = 0;
	}

};

bool operator<(const Puzzle& p1, const Puzzle& p2) {

	return p1.f > p2.f;
}

priority_queue <Puzzle> openSet;
unordered_set <string> visited;
int maxLength, numNodes;

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

bool isValid(int i, int j) {
	if (i >= 0 && j >= 0 && i < 3 && j < 3)
		return 1;
	else
		return 0;
}

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

Puzzle move(Puzzle s, int i1, int j1, int i2, int j2) {
	string st = s.toString();
	int index1 = i1 * 3 + j1, index2 = i2 * 3 + j2;
	char tempChar = st[index1];
	st[index1] = st[index2];
	st[index2] = tempChar;
	Puzzle newPuzzle(st);
	return newPuzzle;
}

void expand(Puzzle s, queue <Puzzle>& inputQueue) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (s.p[i][j] == 0) {
				if (isValid(i - 1, j)) {
					Puzzle newPuzzle = move(s, i, j, i - 1, j);
					if (visited.find(newPuzzle.toString()) == visited.end()) {
						visited.insert(newPuzzle.toString());
						newPuzzle.g++;
						numNodes++;
						inputQueue.push(newPuzzle);
					}
				}
				if (isValid(i + 1, j)) {
					Puzzle newPuzzle = move(s, i, j, i + 1, j);
					if (visited.find(newPuzzle.toString()) == visited.end()) {
						visited.insert(newPuzzle.toString());
						newPuzzle.g++;
						numNodes++;
						inputQueue.push(newPuzzle);
					}
				}
				if (isValid(i, j - 1)) {
					Puzzle newPuzzle = move(s, i, j, i, j - 1);
					if (visited.find(newPuzzle.toString()) == visited.end()) {
						visited.insert(newPuzzle.toString());
						newPuzzle.g++;
						numNodes++;
						inputQueue.push(newPuzzle);
					}
				}
				if (isValid(i, j + 1)) {
					Puzzle newPuzzle = move(s, i, j, i, j + 1);
					if (visited.find(newPuzzle.toString()) == visited.end()) {
						visited.insert(newPuzzle.toString());
						newPuzzle.g++;
						numNodes++;
						inputQueue.push(newPuzzle);
					}
				}

			}
		}
	}

}

queue <Puzzle> parentExpand(Puzzle s, int depth) {
	queue <Puzzle> temp1;
	expand(s, temp1);
	queue <Puzzle> temp2(temp1);
	queue <Puzzle> temp3;
	depth--;
	while (depth > 0) {
		while (!temp2.empty()) {
			Puzzle c = temp2.front();
			temp2.pop();
			expand(c, temp3);
			queue <Puzzle> temp4(temp3);
			while (!temp4.empty()) {
				temp1.push(temp4.front());
				temp4.pop();
			}
		}
		depth--;
		while (!temp3.empty()) {
			temp2.push(temp3.front());
			temp3.pop();
		}
	}
	return temp1;
}

Puzzle aStar(Puzzle s, int depth) {	

	maxLength = 0;
	numNodes = 0;
	s.fgSet();
	visited.clear();
	visited.insert(s.toString());
	openSet = priority_queue <Puzzle>();

	while (!s.goal_test()) {
		queue <Puzzle> parentExpRet = parentExpand(s, depth);
		deque <Puzzle> temp;
		while (!parentExpRet.empty()) {
			temp.push_back(parentExpRet.front());
			parentExpRet.pop();
		}
		for (int i = 0; i < temp.size(); i++) {
			temp[i].updateF();
			openSet.push(temp[i]);
			if (openSet.size() > maxLength) {
				maxLength = openSet.size();
			}
		}
		if (!openSet.empty()) {
			s = openSet.top();
			openSet.pop();
		}
		else break;
	}
	if (s.goal_test())
		cout << "Solved" << endl;
	else
		cout << "Not Solved" << endl;

	cout << "Maximum openSet length: " << maxLength << endl;		
	cout << "Number of nodes: " << numNodes << endl << endl;							
	return s;
}

int main(int argc, char **argv) {
	int depth = 1;
	int cases;
	string temp;
	char c;
									


	 srand ( time(NULL) ); 
   OpenAndFill(argv[1]);
   auto start = chrono::steady_clock::now();

	 ifstream myfile(argv[1]);
	 vector<string> puzzles;
	 if (myfile.is_open())
	 {
		 myfile >> cases;
		 cout << "Cases: " << cases << endl;
		 for (int j = 0; j < cases; j++)
		 {
			 temp = "";
			 for (int i = 0; i < 9; i++)
			 {				 
				 myfile >> c;
				 temp += c;
			 }
			 puzzles.push_back(temp);
		 }
	 }
	 else cout << "Unable to open file" << endl;
	while (puzzles.size() > 0) { 			
    if (!isSolvable(samples[0])) {		
      cout << "Not Solved" << endl;
    }					
    else {  
      Puzzle s(puzzles[0]); 
      cout << "Start: " << endl;
      s.display();
      cout << endl;											
      aStar(s, depth);							
    }				
		puzzles.erase(puzzles.begin());
    samples.erase(samples.begin());
	}
  auto end = chrono::steady_clock::now();

  cout << "Elapsed time in milliseconds: "
  << chrono::duration_cast<chrono::milliseconds>(end - start).count()
  << " ms" << endl;

  PROCESS_MEMORY_COUNTERS_EX pmc;
  GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
  SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
  SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
  cout << "Physical memory currently used by this procces: " << physMemUsedByMe / 1048576 << "MiB" << endl;
	
  return 0;
}
