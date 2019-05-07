//
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class node {
	public:
        string header;
        string content;
        vector <node> children;
        node *parent;
        void add(string str) {
            content += str;
        }
        void addChild(node newChild) {
            children.push_back(newChild);
        }
};

void clearExtraSpaces(string&);
bool is_singleKeyword(string);
bool is_doubleKeyword(string);
bool is_variable(string);
void initialize();
void finalize();
void normalize();
void read();
void exportNormal();
void parse();
void traverse(node);

string megaToken = "";
vector <string> input;

string *singleKeywordList;
string *doubleKeywordList;
string *variableList;

// main function node.
node mainNode;

int main() {
	initialize();
	read();
	normalize();
	clearExtraSpaces(megaToken);
	exportNormal();
	parse();
	traverse(mainNode);
	finalize();
}

void initialize() {

}

bool valid(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != '\t' || str[i] != ' ')
            return true;
    }
    return false;
}

void read() {
    // testing is done via input cpp file.
	ifstream fileReader("input.cpp");
	if (fileReader.is_open()) {
		cout << "--> START\n";
		string line;
		while(getline(fileReader, line)) {
			if (valid(line)) {
                input.push_back(line);
                printf("%s\n", line.c_str());
			}
		}
		cout << "--> END\n";
		fileReader.close();
	}else
		cout << "Unable to open file\n";
}

// Different code formats gets unified here.
void normalize() {
	for (unsigned int i = 0; i < input.size(); i++) {
		string smallToken = "";
		bool hold = false;
		for (unsigned int j = 0; j < input[i].size(); j++) {
			if (!hold) {
				if (input[i][j] == ' ') {
					smallToken += " ";
					hold = true;
					continue;
				}else
					smallToken += input[i][j];
			}else {
				if (input[i][j] != ' ') {
					hold = false;
					smallToken += input[i][j];
					continue;
				}
			}
		}
		if (smallToken != "")
			megaToken += smallToken + " ";
	}
}

// Clearing extra spaces after normalizing (for a cleaner lifestyle, cleaner life).
void clearExtraSpaces(string &str) {
	char *TemporaryString;
	TemporaryString = new char[str.size()];
	bool hold = false;
	int idx = 0;
	for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == '\t')
            continue;
		if (hold == true) {
			if (str[i] != ' ') {
				hold = false;
				TemporaryString[idx++] = str[i];
			}
		}else {
			if (str[i] == ' ') {
				hold = true;
			}
			TemporaryString[idx++] = str[i];
		}
	}
	str = "";
	for (int i = 0; i < idx; i++) {
		str += TemporaryString[i];
	}
	delete TemporaryString;
}

string toString(int num) {
    string numString = "";
    while(num > 0) {
        numString += (num % 10) + '0';
        num /= 10;
    }
    reverse(numString.begin(), numString.end());
    return numString;
}

// parses only code within main function. (FOR NOW..)
void parse() {
    mainNode.header = "0";
    mainNode.content = "MAIN NODE";
    string parsedToken = "";
    for (unsigned int i = 0; i < megaToken.size(); i++) {
        if (parsedToken.size() == 0 && megaToken[i] == ' ')
            continue;
        parsedToken += megaToken[i];
        if (megaToken[i] == ';') {
            i++;
            node newNode;
            newNode.header = mainNode.header + "." + toString(mainNode.children.size() + 1);
            newNode.add(parsedToken);
            parsedToken = "";
            mainNode.children.push_back(newNode);
        }
    }
}

void traverse(node token) {
    printf("NODE ID: %s\n", token.header.c_str());
    printf("NODE CONTENT:\n%s\n", token.content.c_str());
    //printf("NODE PARENT ID: %d\n", token.parent->header.c_str()); off for now
    printf("# OF CHILDREN: %d\n\n", token.children.size());
    for (int i = 0; i < token.children.size(); i++) {
        traverse(token.children[i]);
    }
    return;
}

//TODO: after wrapping up, exportNormal should write to file.
void exportNormal() {
    printf("--> %s\n\n", megaToken.c_str());
}

void finalize() {
	delete singleKeywordList;
	delete doubleKeywordList;
	delete variableList;
}
