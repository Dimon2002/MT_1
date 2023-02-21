#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

static const string Format = ".txt";
static const string Keywords = "Keywords";
static const string Separators = "Separators";
static const string OperationSigns = "OperationSigns";
static const string OutFileFormat = "Out";

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

	Lexeme() {}
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
	VariableTable()
	{
		CreateEmptyTable();
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

	void CreateEmptyTable();
	void AddingElement(Lexeme El);

	int IsContains(const string& NameEl);
	int IsContains(const int& Index);
};

void VariableTable::CreateEmptyTable()
{
	_table.resize(0);
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
	if (_table.size() == 0) 
		return -1;

	auto x = find(_table.begin(), _table.end() - 1, NameEl);
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
	// ConstTable t(Keywords + Format);
	// t.PrintTable(Keywords + OutFileFormat + Format);

	VariableTable t2;
	auto x = t2.SearchByWord("Value1");
	cout << x << endl;
	t2.SetAttribute("Value1", true, 100);
	t2.PrintTable(Keywords + OutFileFormat + Format);
}