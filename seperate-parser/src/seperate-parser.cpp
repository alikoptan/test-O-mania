#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class node {
	public:
		string id;
        string header;
        vector <node> children;
        node *parent;
        void add(char ch) {
            header += ch;
        }
        void destroy() {
        	id = "";
        	header = "";
        	children.clear();
        }
};

bool isMultiKeyword(int);
void clearExtraSpaces(string&);
void initialize();
void finalize();
void normalize();
void read();
pair <vector <node>, int> parse(int);
void exportNormal();
void traverse(node);

string megaToken = "";
vector <string> input;

string *multiKeywordList;

// main program node.
node program;

int main() {
	initialize();
	read();
	normalize();
	clearExtraSpaces(megaToken);
	exportNormal();

	int index = 0;
	program.header = "PROGRAM";
	program.children = parse(index).first;
	traverse(program);
	finalize();
}

void initialize() {
	multiKeywordList = new string[6];
	multiKeywordList[0] = "do";
	multiKeywordList[1] = "while";
	multiKeywordList[2] = "for";
	multiKeywordList[3] = "if";
	multiKeywordList[4] = "else";
	multiKeywordList[5] = "main";
}

bool valid(string str) {
    for (unsigned int i = 0; i < str.size(); i++) {
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
			if (hold == false) {
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

bool isMultiKeyword(int index) {
	for (unsigned int i = 0; i < 6; i++) {
		if (index + multiKeywordList[i].size() < megaToken.size()) {
			string str = megaToken.substr(index, multiKeywordList[i].size());
			if (str == multiKeywordList[i])
				return true;
		}
	}
	return false;
}

pair <string, unsigned int> crawl(int index) {
	pair <string, int> token;
	for (int i = index; i < megaToken.size(); i++) {
		token.first += megaToken[i];
		if (megaToken[i] == ';' || (megaToken[i] == '>' && megaToken[i - 1] == 'h')) {
			token.second = i + 2; //jump 4 lines.
			return token;
		}
		if (megaToken[i + 1] == '{') {
			token.second = i + 1; //these numbers are based on Normalize() function, number
			return token;		  // of spaces between words is constant.
		}
	}
	return token;
}

pair <vector <node>, int> parse(int index) {
	vector <node> children;
	node child;
	string web = crawl(index).first;
	int resIndex = crawl(index).second;
	while(true) {
		if (megaToken[resIndex] == '{') {
			pair <vector <node>, int> res = parse(resIndex + 1);
			child.children = res.first;
			index = res.second;
		}

	}


	return children;
}

//
//pair <vector <node>, int> parse(int index) {
//	cout << "PARSING: " << index << '\n';
//	vector <node> children;
//	node child;
//	for (unsigned int i = index; i < megaToken.size(); i++) {
//		child.add(megaToken[i]);
//		cout << "index = " << i << " " << "child got " << megaToken[i] << " added" << '\n';
//		if (isMultiKeyword(i) == true) {
//			cout << "I have found one here\n";
//			for (unsigned int j = i + 1; j < megaToken.size(); j++) {
//				child.add(megaToken[j]);
//				cout << "index = " << j << " child got " << megaToken[j] << " added\n";
//				if (megaToken[j + 1] == '{') {
//					i = j + 3;
//					child.children = parse(i).first;
//					i = parse(i).second;
//				}
//			}
//		}
//
//		if (megaToken[i + 1] == '}') {
//			cout << "reached end of function / scope\n";
//			return make_pair(children, i + 3);
//		}
//
//		// special cases for header .h files
//		if ((megaToken[i] == '>' && megaToken[i - 1] == 'h') || megaToken[i] == ';') {
//			cout << "reached a statment / header file\n";
//			i++;
//			children.push_back(child);
//			child.destroy();
//		}
//		index = i;
//	}
//	return make_pair(children, index);
//}

void traverse(node token) {
    printf("NODE CONTENT: %s\n", token.header.c_str());
    printf("# OF CHILDREN: %d\n\n", (int)token.children.size());
    for (unsigned int i = 0; i < token.children.size(); i++) {
        traverse(token.children[i]);
    }
    return;
}

//TODO: after wrapping up, exportNormal should write to file.
void exportNormal() {
    printf("--> %s\n\n", megaToken.c_str());
}

void finalize() {
	delete [] multiKeywordList;
}
