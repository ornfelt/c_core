#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// Polymorphism
	
	struct sSomeBaseObject
	{
		virtual const char* IdentifyYourself()
		{
			return "BaseObject";
		}
	};
	
	struct sSomeSubObjectA : public sSomeBaseObject
	{
		//virtual const char* IdentifyYourself()
		const char* IdentifyYourself()
		{
			return "Subobject A";
		}
	};
	
	struct sSomeSubObjectB : public sSomeBaseObject
	{
		const char* IdentifyYourself()
		{
			return "Subobject B";
		}
	};
	// This works
	sSomeBaseObject ob_base;
	sSomeSubObjectA ob_A;
	sSomeSubObjectB ob_B;
	cout << ob_base.IdentifyYourself() << endl;
	cout << ob_A.IdentifyYourself() << endl;
	cout << ob_B.IdentifyYourself() << endl;
	cout << endl;
	
	// If we want an array of these objects:
	sSomeBaseObject objects[10];
	// Setting one of the objects to a sub-object doesn't work (compiler won't complain since it's a subclass) but the print will still be "BaseObject".
	// We can maybe fix that by adding virtual to IdentifyYourself above which tells the compiler that if I am a subclassed and any of my children happen to override this method, call the childs method instead... This doesn't work however since the objects are crucially sSomeBaseObject.
	objects[3] = sSomeSubObjectA();
	for (int i = 0; i < 10; i++)
		cout << objects[i].IdentifyYourself() << endl;
	cout << endl;

	// We instead want a structure where the compiler can intelligently work it out as to which method should be called on which object...
	// Create pointer to an array of pointers:
	sSomeBaseObject** pSomeArray = new sSomeBaseObject*[5];
	// After allocating array we need to create objects:
	pSomeArray[0] = new sSomeSubObjectA();
	pSomeArray[1] = new sSomeSubObjectB();
	pSomeArray[2] = new sSomeSubObjectB();
	pSomeArray[3] = new sSomeBaseObject();
	pSomeArray[4] = new sSomeSubObjectA();
	
	for (int i = 0; i < 5; i++)
		// Use arrow instead of '.' since pointers instead of objects...
		cout << pSomeArray[i]->IdentifyYourself() << endl;
	
	for (int i = 0; i < 5; i++)
		delete pSomeArray[i];

	delete[] pSomeArray;
	
	cout << endl;
	// We can do the same with vectors:
	vector<sSomeBaseObject*> vSomeVector;
	
	vSomeVector.push_back(new sSomeSubObjectA());
	vSomeVector.push_back(new sSomeSubObjectB());
	vSomeVector.push_back(new sSomeSubObjectB());
	vSomeVector.push_back(new sSomeBaseObject());
	vSomeVector.push_back(new sSomeSubObjectA());
	
	// Uses reference instead of pointers with &a
	for (auto &a: vSomeVector)
		cout << a->IdentifyYourself() << endl;
	
	for (auto &a: vSomeVector)
		delete a;
	
	vSomeVector.clear();
	
	cout << endl;	system("pause");	return 0;
}
// g++ .\pointers_poly.cpp; .\a.exe