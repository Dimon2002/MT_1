#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

static const string Base = ".txt";
static const string Keywords = "Keywords";
static const string Separators = "Separators";
static const string OperationSigns = "OperationSigns";
static const string TableVariables = "Variables";

#pragma region ConstTable

class ConstTable
{
public:
	ConstTable(const string& fileName)
	{
		CreateTable(fileName);
	};
	~ConstTable()
	{
		_table.clear();
	};

	int IndexByWord(const string& text);
	string WordByIndex(int Index);

	void PrintTable(const string& outFileName);
private:
	vector<string> _table;

	int IsContains(int Index);
	void CreateTable(const string& fileName);
};

void ConstTable::CreateTable(const string& fileName)
{
	ifstream fin(fileName);
	if (!fin.is_open())
		cerr << "File didn't openned";

	string s;
	while (fin >> s)
		_table.push_back(s);

	fin.close();
}

int ConstTable::IndexByWord(const string& text)
{
	for (int i = 0; i < _table.size(); i++)
		if (_table[i] == text)
			return i;
	return -1;
}

string ConstTable::WordByIndex(int Index)
{
	return IsContains(Index) == -1 ? string() : _table[Index];
}

int ConstTable::IsContains(int Index)
{
	return Index >= 0 && Index < _table.size() ? Index : -1;
}

void ConstTable::PrintTable(const string& outFileName)
{
	ofstream fout(outFileName);
	int i = 0;
	for (auto& el : _table)
		fout << ++i << " " << el << endl;
	fout.close();
}

#pragma endregion

#pragma region VariableTable

ostream& operator << (ostream& out, pair<bool, int> el)
{
	return out << "{ " << el.first << ", " << el.second << " }" << endl;
}

struct Lexeme
{
	string name;
	bool type = false;
	int value = -1;

	Lexeme(const string& Name)
	{
		name = Name;
	}

	friend bool operator == (const Lexeme& leftOperand, const Lexeme& rightOperand)
	{
		return
			leftOperand.name == rightOperand.name &&
			leftOperand.type == rightOperand.type &&
			leftOperand.value == rightOperand.value;
	}

	friend bool operator != (const Lexeme& leftOperand, const Lexeme& rightOperand)
	{
		return !(leftOperand == rightOperand);
	}

	friend ostream& operator << (ostream& out, const Lexeme& el)
	{
		if (!el.name.empty())
		{
			return out << "{ " << el.name << ", " << el.type << ", " << el.value << " }" << endl;
		}
		return out << "The element doesn`t exist!";
	}
};

class VariableTable
{
public:
	VariableTable(const string& fileName)
	{
		CreateTable(fileName);
	};
	~VariableTable()
	{
		_table.clear();
	};

	int SearchByWord(const string& NameVariable);

	Lexeme SearchByIndex(int Index);

	void SetAttribute(const string& NameVariable, bool TypeVariable, int ValueVariable);
	pair<bool, int> GetAttribute(int Index);
	string SearchByNumber(int Index);

	void PrintTable(const string& outFileName);
private:
	vector<Lexeme> _table;

	void CreateTable(const string& FileName);
	void AddingElement(Lexeme El);

	int IsContains(const string& NameEl);
	int IsContains(const int& Index);
};

void VariableTable::CreateTable(const string& FileName)
{
	ifstream fin(FileName);
	if (!fin.is_open())
		cerr << "File didn't openned";

	string s;
	while (fin >> s)
		_table.push_back(Lexeme(s));

	fin.close();
}

void VariableTable::AddingElement(Lexeme El)
{
	_table.push_back(El);
}

void VariableTable::SetAttribute(const string& NameVariable, bool TypeVariable, int ValueVariable)
{
	auto indexElement = SearchByWord(NameVariable);
	_table[indexElement].type = TypeVariable;
	_table[indexElement].value = ValueVariable;
}

void VariableTable::PrintTable(const string& outFileName)
{
	ofstream fout(outFileName);
	int i = 0;
	for (auto& el : _table)
		fout << "[" << ++i << "] " << el << endl;
	fout.close();
}


int VariableTable::IsContains(const string& NameEl)
{
	auto x = find(_table.begin(), _table.end() - 1, Lexeme(NameEl).name);
	if (*x != _table.back().name || _table.back().name == NameEl)
		return distance(_table.begin(), x);
	return -1;
}

int VariableTable::IsContains(const int& Index)
{
	return Index >= 0 && Index < _table.size() ? Index : -1;
}

int VariableTable::SearchByWord(const string& NameVariable)
{
	int indexElement = IsContains(NameVariable);
	if (indexElement == -1)
	{
		AddingElement(Lexeme(NameVariable));
		return indexElement + 1;
	}
	return indexElement;
}


Lexeme VariableTable::SearchByIndex(int Index)
{
	int indexElement = IsContains(Index);
	if (indexElement != -1)
	{
		return _table[indexElement];
	}
	return Lexeme({});
}

pair<bool, int> VariableTable::GetAttribute(int Index)
{
	auto Element = SearchByIndex(Index);
	return make_pair(Element.type, Element.value);
}

string VariableTable::SearchByNumber(int Index)
{
	return SearchByIndex(Index).name;
}

#pragma endregion

int main()
{
	ConstTable t(Keywords + Base);
	// cout << t.IndexByWord("While");
	// cout << t.WordByIndex(3);
	// cout << t.WordByIndex(10);

	//VariableTable t2("Words.txt");
	//t2.SetAttribute("int", true, 1053240);
	//auto x = t2.SearchByWord("int");
	//t2.PrintTable("Жижа.txt");
	// cout << t2.IsContains("Int");
	// t.PrintTable();
}