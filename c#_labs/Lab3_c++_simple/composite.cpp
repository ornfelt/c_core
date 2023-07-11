// CPP program to illustrate
// Composite design pattern
#include <iostream>
#include <vector>
using namespace std;

class BoardObject {
public:
	virtual void Add(BoardObject a)
	{
	}
	virtual void Remove()
	{
	}
	virtual void Delete(BoardObject a)
	{
	}
};

class Board : public BoardObject {

public:
	void Add(BoardObject a)
	{
		cout << "something is added to the Board" << endl;
	}
	void Remove()
	{
		cout << "something is removed from the Board" << endl;
	}
	void Delete(BoardObject a)
	{
		cout << "something is deleted from Board " << endl;
	}
};

class SuperBoard : public BoardObject {
	vector<BoardObject> copyBoards;

public:
	void AddElement(BoardObject a)
	{
		copyBoards.push_back(a);
	}

	void Add(BoardObject a)
	{
		cout << "something is added to the copy" << endl;
	}
	void Remove()
	{
		cout << "something is removed from the copy" << endl;
	}
	void Delete(BoardObject a)
	{
		cout << "something is deleted from the copy";
	}
};

int main()
{
	Board a;
	Board b;
	SuperBoard superBoard;

	superBoard.AddElement(a);
	superBoard.AddElement(b);

	superBoard.Add(a);
	superBoard.Add(b);

	//a.Add(b);
	//superBoard.Remove();
	//b.Remove();

	return 0;
}
