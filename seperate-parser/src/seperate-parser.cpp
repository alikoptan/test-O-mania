#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <typeinfo>

using namespace std;

class node {
public:
	unsigned short id;
	string header;
	node *child;
	virtual ~node() = default;
};

class condition : public node {
public:
	node *trueNode;
	node *falseNode;
	virtual ~condition() = default;
};

node entryPoint;



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
map <string, vector <string>> adj;

pair <vector <string>, int> testParse(int index) {
	pair <vector <string>, int> childern;
	string str;
	for (unsigned int i = index; i < megaToken.size(); i++) {
		str += megaToken[i];
		if (str.back() == '{') {
			childern.first.push_back(str);
			int stop = testParse(i + 1).second;
			adj[str] = testParse(i + 1).first;
			i = stop;
		}
		if (str.back() == ';' || (str[str.size() - 1] == '>' && str[str.size() - 2] == 'h')) {
			childern.first.push_back(str);
			str = "";
		}
		if (str.back() == '}') {
			childern.second = i;
			return childern;
		}
	}
	return childern;
}

node* createStatment(string s)
{
	node *ret = new node();
	//TODO : implement generate id
	ret->header = s;
	return ret;
}

condition* createCondition(string s)
{
	condition *ret = new condition();
	//TODO : implement generate id
	ret->header = s;
	return ret;
}

vector<node*> parseFor(string s)
{
	int begin = s.find('(');
	int end = s.find(')');

	vector<node*> ret;
	string initialize;
	string condition;
	string pre;

	int semi = 0;
	string cur;
	for(int i = begin + 1; i < end; i++)
	{
		cur += s[i];
		if(s[i] == ';')
		{
			if(semi == 0)
				initialize = cur;
			else if(semi == 1)
				condition = cur;
			cur = "";
			semi++;
		}
	}
	pre = cur;
	ret.push_back(createStatment(initialize));
	ret.push_back(createCondition(condition));
	ret.push_back(createStatment(pre));
	return ret;
}

node* getLastChild(node* node)
{
	if(node->child == nullptr)
		return node;
	else
		return getLastChild(node->child);
}

void dfs(node *node)
{
    if(node->child == nullptr)
        return;
    condition *cond = dynamic_cast<condition*>(node);
    if(cond != nullptr)
    {
        dfs(cond->trueNode);
        dfs(cond->child);
    }
    else
        dfs(node->child);
}

node* parse(string s)
{
    if(s.size() == 0)
        return nullptr;
	if(s.size() >= 3 && s.substr(0, 3) == "for")
	{
		int end = s.find(')');
		string forStatment;
		string insideFor;
		string rest;

		int endForIndex = s.find(')');
		forStatment = s.substr(0, endForIndex + 1);
		vector<node*> forNodes = parseFor(forStatment);

		//b3d l for hyb2a fiih '{'
		int endInsideForIndex;
		int open = 1;
		for(int i = endForIndex + 2; i < s.size(); i++)
		{
			if(s[i] == '{')
				open++;
			else if(s[i] == '}')
				open--;
			if(open == 0){
				endInsideForIndex = i;
				break;
			}
			insideFor += s[i];
		}

		node* insideForNode = parse(insideFor);

		node* lastInsideFor = getLastChild(insideForNode);

		//initialize then check condition
		forNodes[0]->child = forNodes[1];
		//after inside for return to post conditon
		lastInsideFor->child = forNodes[2];
		//after post condition return to check condition
		forNodes[2]->child = forNodes[1];

		//if true ad5ol loop
		condition* cond = dynamic_cast<condition*>(forNodes[1]);
		cond->trueNode = insideForNode;


		rest = s.substr(endInsideForIndex + 1);
		node* restNode = parse(rest);

		//if false a5rog bra l loop
		cond->falseNode = cond->child = restNode;
		return forNodes[0];
	}
	else if(s.size() >= 2 && s.substr(0, 2) == "if") {
		int start = s.find('(');
		int end = s.find(')');
		string statementBody = s.substr(start + 1, end - start - 1);
		string insideIf;
		condition *ifBody = createCondition(statementBody);

		int endInsideIfIndex;
		int open = 1;
		for(int i = end + 2; i < s.size(); i++) {
			if(s[i] == '{')
				open++;
			else if(s[i] == '}')
				open--;
			if(open == 0){
				endInsideIfIndex = i;
					break;
				}
			insideIf += s[i];
		}
		node *insideIfNode = parse(insideIf);
		ifBody->trueNode = insideIfNode;
		s = s.substr(endInsideIfIndex + 1);

		if (s.size() >= 4 && s.substr(0, 4) == "else") {
			string insideElse;
			int endInsideElseIndex;
			int open = 1;
			for (int i = 6; i < s.size(); i++) {
				if(s[i] == '{')
					open++;
				else if(s[i] == '}')
					open--;
				if(open == 0) {
					endInsideElseIndex = i;
					break;
				}
				insideElse += s[i];
			}
			node *insideElseNode = createStatment(insideElse);
			ifBody->falseNode = insideElseNode;
			s = s.substr(endInsideElseIndex + 1);
		}else {
			ifBody->falseNode = nullptr;
		}
		ifBody->child = parse(s);
		return ifBody;
	}
	else
	{
		int nextStatmentEnd = s.find(';');
		node* statement = createStatment(s.substr(0, nextStatmentEnd));
		statement->child = parse(s.substr(nextStatmentEnd + 1));
		return statement;
	}
}

void dfs(string x, int lev) {
	for (int i = 0; i < lev; i++)
		cout << "->";
	cout << x << '\n';
	for (auto s : adj[x])
		dfs(s, lev + 1);
}

int main() {
	/*read();
	normalize();
	clearExtraSpaces(megaToken);*/

	string test = "for(int i = 0; i < 5; i++){int x;x++;}int x = 0;";
	node* program = parse(test);
	dfs(program);
//
//	string p = "program";
//	adj[p] = testParse(0).first;
//
//
//	for (auto x : adj) {
//		cout <<
//
//	}
//	dfs("program", 0);
//	initialize();
//	exportNormal();
//
//	int index = 0;
//	program.header = "PROGRAM";
//	program.children = parse(index).first;
//	traverse(program);
//	finalize();
}

void initialize() {
	multiKeywordList = new string[6];
	multiKeywordList[0] = "do";
	multiKeywordList[1] = "while";
	multiKeywordList[2] = "for";
	multiKeywordList[3] = "if";
	multiKeywordList[4] = "else";
	multiKeywordList[5] = "main()";
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
	for (unsigned int i = index; i < megaToken.size(); i++) {
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
//
//void traverse(node token) {
//    printf("NODE CONTENT: %s\n", token.header.c_str());
//    printf("# OF CHILDREN: %d\n\n", (int)token.children.size());
//    for (unsigned int i = 0; i < token.children.size(); i++) {
//        traverse(token.children[i]);
//    }
//    return;
//}

//TODO: after wrapping up, exportNormal should write to file.
void exportNormal() {
    printf("--> %s\n\n", megaToken.c_str());
}

void finalize() {
	delete [] multiKeywordList;
}
