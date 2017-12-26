// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <direct.h>

#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>
#include <chrono> // 20171226
#include <ctime>  // 20171216
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

void getToken(const string& setData, vector<string> & tokens, const string& delim)
{
	if (delim.empty())
	{
		string buf;
		stringstream strSrm( setData );

		while (strSrm >> buf)
		{
			tokens.push_back(buf);
		}
	}
	else
	{
		string::size_type iLastPos = setData.find_first_not_of(delim, 0 );
		string::size_type iPos = setData.find_first_of(delim, iLastPos);

		while (iPos != string::npos)
		{
			tokens.push_back(setData.substr(iLastPos, iPos - iLastPos));
			iLastPos = setData.find_first_not_of(delim, iPos + 1);
			iPos = setData.find_first_of(delim, iLastPos);
		}
	}
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
{	
	/*
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

	cout << "----------- compare start -------------1" << endl;
	itr = tokens.begin();
	for (int i = 0;i < tokens.size(); i++, itr++)
	{
		cout << tokens[i] << " " << *itr << endl;
		
	}
	cout << "----------- compare __end -------------1" << endl;
	/*
	int iData = 0;
	
	szData1.clear();
	cin >> szData1;
	iData = atoi(szData1.c_str());
	cout << "input data : " << szData1 << " ...get data : " << iData << endl;
	*/
	szData1.clear();
	szData1 = "CLANG";
	szData1 += " Life is clang.";
	
	tokens.clear();
	getToken(szData1, tokens, "\0");
	cout << "----------- start -------------2" << endl;
	
	for ( itr = tokens.begin() ; itr!=tokens.end(); itr++)
	{
		cout <<  *itr << endl;
	}
	cout << "----------- __end -------------2" << endl;
	tokens.clear();
	getToken(szData1, tokens, " .");
	cout << "----------- start -------------3" << endl;
	for (itr = tokens.begin(); itr != tokens.end(); itr++)
	{
		cout << *itr << endl;
	}
	cout << "----------- __end -------------3" << endl;
	
	
}

struct STR_EX
{
	STR_EX() { iData = 0, strData = ""; }
	int iData;
	string strData;
};

void showReview(STR_EX* ss)
{
	cout << ss->iData << " " << ss->strData << endl;
}
void test_container()
{
	// seq cont : vector, list, deque
	// 연관 컨테이너 : set, map,

	
	vector<STR_EX*> vecSTR_EX;

	auto_ptr<STR_EX> strEX(new STR_EX);
	auto_ptr<STR_EX> strEX2(new STR_EX);
	strEX->iData = 11;
	strEX->strData = "eleven";
	vecSTR_EX.push_back(strEX.get());

	strEX2->iData = 22;
	strEX2->strData = "twentytwo";
	vecSTR_EX.push_back(strEX2.get());

	for (vector<STR_EX*>::iterator it = vecSTR_EX.begin(); it != vecSTR_EX.end();it++)
	{
		cout << (*it)->iData << " " << (*it)->strData << endl;
		// showReview((STR_EX*)(*it));
		
	}
	cout << "<< 2'nd display ----------------------------->" << endl;
	for_each(vecSTR_EX.begin(), vecSTR_EX.end(), showReview);

	vector<int> vecInt(10);
	auto a_it = vecInt.begin();
	*a_it = 100;
	cout << *a_it << endl;

	cout << "<< map example display :: start ----------------------------->" << endl;
	map<string, int> mapData;
	mapData["abc"] = 1;
	mapData["efg"] = 2;

	string szData = "";
	szData = to_string(mapData["abc"]);
	cout << szData << endl;
	map<string, int>::iterator it = mapData.find("efg");
	if (it != mapData.end())
		cout << it->first << ", " << it->second << endl;
	else
		cout << "cannot search." << endl;

	it = mapData.find("asdf");
	if (it == mapData.end()) 
		cout << "what? what are you doning??" << endl;

	cout << "<< map example display :: __end ----------------------------->" << endl;
	

	map<string, string> mapData2;
	mapData2.insert(make_pair("a", "z"));
	mapData2.insert(make_pair("b", "y"));
	pair<string, string> p("c","x");
	mapData2.insert(p);


	map<string, string>::iterator mit = mapData2.find("a");
	if (mit != mapData2.end())
	{
		cout << mit->first << ", " << mit->second << endl;
	}
}

// smart pointer
void test_autoptr()
{
	string strData;
	int iGet=0;
	//int* iData;
	//iData = new int;
	
	auto_ptr<int> iData = auto_ptr<int>(new int);
	iGet = 48;
	*iData = iGet;
	cout << "Address1 = " << iData.get() << ", Value = " << *iData << endl;
	cout << "Address2 = " << &iGet << ", Value = " << iGet << endl;


}

void test_string2()
{
	string szPath1 = "";
	string szDelim = "";
	string szResult = "";
	// char cPath2[1024];
	// _getcwd(cPath2, 1024);	
	// char* --> string
	// szPath1.assign(cPath2, strlen(cPath2));

	// auto_ptr<char> cPath1(new char[1024]);
	// _getcwd( cPath1.get(), 1024);

	szPath1.resize(1024);
	string::iterator itr = szPath1.begin();
	_getcwd( &(*itr), 1024);
	szPath1.resize( strlen(szPath1.c_str()) );

	szResult = szPath1 + ", count : " + to_string(szPath1.length());
	cout << szResult << endl;

	// 마지막의 "\"를 찾아서 위치를 알아내고,
	szDelim = "\\";
	size_t len = szPath1.find_last_of(szDelim);
	if (len != string::npos)
	{		
		szResult = szPath1.substr(0, len);
		cout << szResult << ", count : " <<  to_string( szResult.length())  << endl;
	}
	else
	{
		cout << "cannot find" << endl;
	}

}
// get date & time
// [since c++11] use chrono lib. to measure duration time 
using namespace std::chrono;
void WriteLog(string szMsg)
{
	// get directory
	// make full path ( current directory + date )
	string szFullName;
	string szCurName;
	string szFileName;
	ofstream hFile;

	// get current directory
	const int iCharSize = 1024;
	char cCurPath[iCharSize];
	memset(cCurPath, 0x0, iCharSize);
	_getcwd(cCurPath, iCharSize);
	szCurName.assign(cCurPath, strlen(cCurPath));

	// get filename using date
	char cDate[iCharSize];	
	memset(cDate, 0x0, iCharSize);
	time_t now = time(NULL);
	struct tm* tmInfo = localtime(&now);
	strftime(cDate, iCharSize, "%Y%m%d_%H", tmInfo);
	szFileName.assign(cDate, strlen(cDate));

	// start 
	time_point< system_clock> t_start = system_clock::now();	

	// make full path name
	szFullName = szCurName + "\\" + szFileName + ".log";

	hFile.open(szFullName, ios::out|ios::app);
	if (hFile.is_open())
	{
		hFile << szMsg << endl;
		hFile.close();
	}

	// duration time  
	time_point< system_clock> t_end = system_clock::now();
	seconds Sec = duration_cast<seconds>(t_end - t_start);
	milliseconds milSec = duration_cast<milliseconds>(t_end - t_start);
	microseconds microSec = duration_cast<microseconds>(t_end - t_start);
	minutes min = duration_cast<minutes>(t_end - t_start);
	hours hour = duration_cast<hours>(t_end - t_start);

	cout << ">> File save time -->  " << endl;
	cout << ">> " << milSec.count() << "[ms]" << endl;
	cout << ">> " << microSec.count() << "[um]" << endl;
	cout << ">> " << Sec.count() << "[sec]" << endl;
	cout << ">> " << min.count() << "[min]" << endl;
	cout << ">> " << hour.count() << "[hour]" << endl;

}

int main() 
{
	// test_ex1();

	// test_string();
	
	// test_autoptr();

	// test_container();
	// test_string2();

	WriteLog("my name is junsoyoung.");
	system("pause");

	return 0;
}
