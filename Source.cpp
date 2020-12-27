#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

typedef string Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};

void Find_Lines(string* Check_Identifier_After, int*& lines);
int all_lines();
void print_lines(int* lines);
void Save_to_Tree_Identifiers(Node*& root, string* Check_Identifier_After, int* lines);
void PrintTree(Node* root, int level);
Node* Insert(Node* p, Info info);
Node* balanceHeight(Node* p);
int BFactor(Node* root);
Node* leftRotation(Node* q);
Node* rightRotation(Node* p);
int Height(Node* root);
Node* FindMin(Node* root);
Node* deleteMin(Node* p);
Node* Delete(Node* p, Info info);
void FindElem(Node*& root, Info info);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Node* root = NULL;
	int action, nodeCount = 1;
	int* lines = new int[all_lines()];
	string Check_Identifier_After[] = { "char ", "int ", "double ", "string ", "float ", "void ",
									   ", ", "bool " };
	string* TreeElemnts = new string[100];
	bool repeat;
	Info value;

	do
	{
		cout << endl << endl;
		cout << "Оберіть дію: " << endl;
		cout << "1 - Знайти номери рядків, які містять ідентифікатори" << endl;
		cout << "2 - Зберегти номери рядків та ідентифікатори у дерево" << endl;
		cout << "3 - Вивести дерево на екран" << endl;
		cout << "4 - Добавити елемент" << endl;
		cout << "5 - Видалити елемент" << endl;
		cout << "6 - Пошук елемента " << endl;
		cout << "0 - Завершити роботу програми" << endl;
		cout << "Введіть: "; cin >> action;

		switch (action)
		{
		case 1:
			cout << "Рядки в яких знайдено ідентифікатори: ";
			Find_Lines(Check_Identifier_After, lines);
			print_lines(lines);
			cout << endl << endl << endl;
			break;
		case 2:
			Save_to_Tree_Identifiers(root, Check_Identifier_After, lines);
			break;
		case 3:
			PrintTree(root, 0);
			break;
		case 4:
			cin.get(); cin.sync();
			cout << "Введіть: "; getline(cin, value);
			root = Insert(root, value);
			break;
		case 5:
			cin.get(); cin.sync();
			cout << "Введіть: "; getline(cin, value);
			root = Delete(root, value);
			break;
		case 6:
			cin.get(); cin.sync();
			cout << "Введіть: "; getline(cin, value);
			FindElem(root, value);
			PrintTree(root, 0);
			break;
		case 0:
			exit(0);
		default:
			cout << "\nПомилка!" << endl;
			repeat = 1;
		}

	} while (action == 1 ||
		action == 2 ||
		action == 3 ||
		action == 4 ||
		action == 5 ||
		action == 6 || repeat == 1);

	return 0;
}
int all_lines()
{
	int count = 0;
	ifstream f("test.txt", ios::in);

	string tmp;
	while (!f.eof())
	{
		getline(f, tmp);
		count++;
	}
	return count;
}
void Find_Lines(string* Check_Identifier_After, int*& lines)
{
	ifstream f("test.txt", ios::in);

	string tmp;

	int counter = 0,
		index_arr = 0;

	while (!f.eof())
	{
		getline(f, tmp);

		counter++;
		for (int j = 0; j < sizeof(Check_Identifier_After); j++)
		{
			size_t pos = tmp.find(Check_Identifier_After[j]);
			if (pos != -1)
			{
				lines[index_arr++] = counter;
				break;
			}
		}
	}
	lines[index_arr] = '/0';
}
void print_lines(int* lines)
{
	int i = 0;
	while (lines[i] != '/0')
		cout << lines[i++] << " ";
}
void Save_to_Tree_Identifiers(Node*& root, string* Check_Identifier_After, int* lines)
{
	ifstream f("test.txt", ios::in);

	string tmp,
		what_to_save;

	int i = 1,
		j = 0,
		size = all_lines();

	for (i; i < size; i++)
	{
		getline(f, tmp);

		if (i == lines[j])
		{
			for (int k = 0; k < sizeof(Check_Identifier_After); k++)
			{
				int pos = tmp.find(Check_Identifier_After[k]);

				if (pos != -1)
				{
					pos += Check_Identifier_After[k].length();

					what_to_save += to_string(i) + " ";

					for (pos; pos < tmp.length(); pos++)
					{
						if (tmp[pos] == ';' ||
							tmp[pos] == '(' ||
							tmp[pos] == '=' ||
							tmp[pos] == '[')
							break;
						else
							what_to_save += tmp[pos];
					}
					root = Insert(root, what_to_save);
					what_to_save = "";
				}
			}
			j++;
		}
	}
}
int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);

	return (hL > hR ? hL : hR) + 1;
}
Node* rightRotation(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	return q;
}
Node* leftRotation(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	return p;
}
int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}
Node* balanceHeight(Node* p)
{
	if (BFactor(p) == 2)
	{
		if (BFactor(p->right) < 0)
			p->right = rightRotation(p->right);
		return leftRotation(p);
	}
	if (BFactor(p) == -2)
	{
		if (BFactor(p->left) > 0)
			p->left = leftRotation(p->left);
		return rightRotation(p);
	}
	return p;
}
Node* Insert(Node* p, Info info)
{
	if (!p)
	{
		p = new Node;
		p->info = info;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	if (info < p->info)
		p->left = Insert(p->left, info);
	else
		if (info > p->info)
			p->right = Insert(p->right, info);

	return balanceHeight(p);
}
void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);

		for (int i = 1; i <= level; i++)
			cout << "                ";
		cout << root->info << endl;

		PrintTree(root->left, level + 1);
	}
}
Node* FindMin(Node* root)
{
	if (root->left != NULL)
		return FindMin(root->left);
	else
		return root;
}
Node* deleteMin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = deleteMin(p->left);
	return balanceHeight(p);
}
Node* Delete(Node* p, Info info)
{
	if (!p)
		return 0;
	if (info < p->info)
		p->left = Delete(p->left, info);
	else if (info > p->info)
		p->right = Delete(p->right, info);
	else
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r)
			return q;
		Node* min = FindMin(r);
		min->right = deleteMin(r);
		min->left = q;
		return balanceHeight(min);
	}
	return balanceHeight(p);
}
void FindElem(Node*& root, Info info)
{
	if (root != NULL)
	{
		if (root->info == info)
			root->info = "|" + info + "|";
		FindElem(root->left, info);
		FindElem(root->right, info);
	}
}