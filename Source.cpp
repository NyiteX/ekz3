#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

class Task
{
protected:
	struct A
	{
		string tas;
		string date;
		string tag;
		int prio;
	};
	vector<A>task;
public:
	virtual ~Task() {}

	virtual vector<A>getTask() { return task; }
	virtual void CreateTask()
	{
		A str;
		cout << "Task: \n";
		getline(cin, str.tas);
		cout << "Date task: \n";
		getline(cin, str.date);
		cout << "Tag: \n";
		getline(cin, str.tag);
		cout << "1 - High prio\t0 - Low prio\n";
		cin >> str.prio;
		cin.ignore();
		task.push_back(str);
	}
	virtual void PrintTask()
	{
		for (size_t i = 0; i < task.size(); i++)
		{
			cout << "task: " << task[i].tas << endl;
			cout << "date: " << task[i].date << endl;
			cout << "prio: " << task[i].prio << endl;
		}
		cout << task.size() << "task size\n";
	}
	virtual void SearchByName()
	{
		string a;
		cout << "Enter search name:\n";
		getline(cin, a);
		bool b = false;
		for (int i = 0; i < task.size(); i++)
		{

			if (!task[i].tas.find(a))
			{
				cout << i + 1 << "\t" << task[i].tas << "\n";
				b = true;
			}
		}
		if (b == false)
		{
			cout << "Ne nashlos'\n";
		}
	}
	virtual void SearchByDate()
	{
		string a;
		cout << "Enter search date:\n";
		getline(cin, a);
		bool b = false;
		for (int i = 0; i < task.size(); i++)
		{

			if (!task[i].date.find(a))
			{
				cout << i + 1 << "\t" << task[i].date << "\n";
				b = true;
			}
		}
		if (b == false)
		{
			cout << "Ne nashlos'\n";
		}
	}
};

class SavetoFile :public Task
{	
public:
	SavetoFile(vector<A>task)
	{	
		ofstream outfile("Task.txt");
		if (outfile.is_open())
		{
			cout << "File save opened.\n";
			cout << task.size() << "size task\n";
			for (int i = 0; i < task.size(); i++)
			{
				outfile << task[i].tas << endl;
				outfile << task[i].date << endl;
				outfile << task[i].tag << endl;
			}
			outfile.close();
		}
	}
	~SavetoFile(){}
};
class LoadFromFile
{
	string s;
public:
	LoadFromFile(string path)
	{		
		ifstream outfile(path);
		if (outfile.is_open())
		{
			cout << "File load opened.\n";
			int i = 0;
			while (!outfile.eof())
			{
				getline(outfile, s);
				cout << s << endl;
			}
			outfile.close();
		}		
	}
	~LoadFromFile(){}
};

class Factory
{
public:
	virtual	Task* createTask() = 0;
	virtual ~Factory() {};
};

class TaskFactory :public Factory
{
public:
	Task* createTask() override { return new Task; }
};


class Army
{
public:
	vector<Task* > vi;
	~Army()
	{
		int i;
		for (i = 0; i < vi.size(); i++) delete vi[i];
	}
	void create()
	{
		int i;
		for (i = 0; i < vi.size(); i++)  vi[i]->CreateTask(); 
	}
	void print()
	{
		int i;
		for (i = 0; i < vi.size(); i++)  vi[i]->PrintTask();
	}
	void save()
	{
		int i;
		for (i = 0; i < vi.size(); i++)	 SavetoFile sa(vi[i]->getTask());
	}
	void load()
	{
		LoadFromFile lo("Task.txt");
	}
	void searchbyname()
	{
		int i;
		for (i = 0; i < vi.size(); i++)	 vi[i]->SearchByName();
	}
	void searchbydate()
	{
		int i;
		for (i = 0; i < vi.size(); i++)	 vi[i]->SearchByDate();
	}
};
class Game
{
public:
	Army* createTaskS(Factory& factory)
	{
		Army* p = new Army;
		p->vi.push_back(factory.createTask());
		return p;
	}
};

int main()
{
	TaskFactory SP_factory;
	Game game;

	Army* SP = game.createTaskS(SP_factory);
	
	char vvod;
	do
	{
		system("cls");
		cout << "1.Create task.\n2.Print task.\n3.Save to file.\n4.Load from file\n";
		cout <<"5.Search by name.\n6.Search by date.\nESC - EXIT.\n";
		vvod = _getch();
		switch (vvod)
		{
		case'1':
			SP->create();
			system("pause");
			break;
		case'2':
			SP->print();
			system("pause");
			break;
		case'3':
			SP->save();
			system("pause");
			break;
		case'4':
			SP->load();
			system("pause");
			break;
		case'5':
			SP->searchbyname();
			system("pause");
			break;
		case'6':
			SP->searchbydate();
			system("pause");
			break;
		}
	} while (vvod != 27);
}