// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Node {
	Node() : name_() {}

	Node(string name) : name_(name) {}

	Node(const Node& r) {
		name_ = r.name_;
		children_ = r.children_;
	}

	void write(int indent) {
		for (int i = 0; i < indent * 4; i++) cout << " ";
		cout << name_ << endl;
		//for (auto it = children_.begin(); it != children_.end(); it++) {
		for ( map<string, Node>::iterator it = children_.begin(); it != children_.end(); it++) {
			it->second.write(indent + 1);
		}
	}

	string name_;
	map<string, Node> children_;
};

list<string> stringToList(string str) {
	istringstream f(str);
	string s;
	list<string> res;

	while (getline(f, s, '/')) res.push_back(s);
	return res;
}

void test_ex1()
{
	string inputs[]{
		"/비둘기/기러기/호랑이/사자",
		"/비둘기/기러기/호랑이/여우",
		"/비둘기/기러기/고양이",
		"/비둘기/기러기/강아지",
		"/짬타이거"
	};
	int count = sizeof(inputs) / sizeof(string);
	Node root;
	for (int i = 0; i < count; i++)
	{
		list<string> inputList = stringToList(inputs[i]);
		Node* current = &root;
		for (string s : inputList)
		{
			if (current->children_.find(s) == current->children_.end())
			{
				Node newNode(s);
				current->children_[s] = newNode;
			}
			current = &current->children_[s];
		}
	}
	root.write(-2);


}

void test_string()
{	/*
	string s;
	char getData[1024] = { 0x0, };
	// cin >> s;
	cin.getline( getData, 1024, ' ');
	s = getData;
	int isize = s.length();
	cout << " size : " << isize << endl;
	cout << " content : " << s << endl;
	cout << " 3'rd charactor : " << s[2] << endl;
	*/

	string szData1("CLANG Junsoyoung Life is good");
	string szData2 = szData1.substr(0, 3);
	cout << szData1 << endl;
	cout << szData2 << endl;

	string::size_type pos = szData1.find_first_of(" ,");
	cout << szData1.substr(0, pos) << endl;
	cout << szData1.substr(pos + 1, szData1.length()) << endl;

	string buf;
	stringstream ss(szData1);

	vector<string> tokens;

	while (ss >> buf)
	{
		tokens.push_back(buf);
		// cout << buf << endl;
	}
	vector<string>::iterator itr;

	for( itr = tokens.begin(); itr!=tokens.end(); itr++)
	{
		cout << *itr << endl;
	}
	/*
	int iData = 0;
	
	szData1.clear();
	cin >> szData1;
	iData = szData1.
	cout << iData << endl;
	*/
}

int main() 
{
	// test_ex1();

	test_string();
	
	system("pause");

	return 0;
}
