#include <iostream>
#include <cstdint>

using namespace std;

/*
https://www.linkedin.com/pulse/first-5-principles-oop-c-what-so-solid-abdalrahman-hesham

Interface Segregation Principle

This principle states that a client should never be forced implement an interface that it
doesn't use. In other words, If a class has a function public to the user, it must be
callable.

Back to our square example, one might think that adding a "SetLength" and "GetLength"
functions, while making the other width and height related functions empty or even warn
the user somehow, is a good approach. This can be seen below.

class Rectangle{
    protected:
    uint16_t Width;
    uint16_t Height;

    public:
    Rectangle(uint16_t width, uint16_t height): Width(width), Height(height){}
    virtual void SetWidth(uint16_t width){
        Width = width;
    }
    virtual void SetHeight(uint16_t height){
        Height = height;
    }
    virtual uint16_t GetWidth(){return Width;}
    virtual uint16_t GetHeight(){return Height;}
    virtual uint32_t CalculateArea(){return Width*Height;}
};

class Square : public Rectangle{
    public:
    Square(uint16_t L): Rectangle(L, L){}
    void SetWidth(uint16_t width) override{(void)width;}
    void SetHeight(uint16_t height) override{(void)height;}
    void SetLength(uint16_t L){ Width=L; Height=L;}
    uint16_t GetLength(){return Width;}
    uint16_t GetWidth() override{return GetLength();}
    uint16_t GetHeight() override{return GetLength();}
};

Now, the "SetWidth" and "SetHeight" functions do, basically nothing, while the "GetWidth"
and "GetHeight" functions call "GetLength" under the hood. So, what's the problem with
this design? Does our square class follow Liskov principle, now?

Actually, our class follows it indeed, by making the square class not behave in an
unexpected way as the Width and height functions have been emptied, they could also be
redesigned to print a warning or throw an exception when used. Still, this square class
provides interfaces that aren't usable by the user, which is confusing and requires
wasting lots of time both reading and writing the accompanying documentation.

A better approach would be to redesign the whole thing by simply making a 2D simple shape
base class that has all the basic functionalities, then each child class adds its own
specific functions. That way each class has no unused interfaces and follows the interface
segregation principle. This can be seen in the code below.
*/


class TwoDSimpleShape{
	protected:
		uint16_t Width;
		uint16_t Height;
	public:
		TwoDSimpleShape(uint16_t width, uint16_t height): Width(width), Height(height){}
		virtual uint32_t CalculateArea(){return Width*Height;}
		virtual ~TwoDSimpleShape() = default;
};

class Rectangle : public TwoDSimpleShape{
	public:
		Rectangle(uint16_t width, uint16_t height): TwoDSimpleShape(width, height){}
		void SetWidth(uint16_t width){Width = width;}
		void SetHeight(uint16_t height){Height = height;}
		uint16_t GetWidth(){return Width;}
		uint16_t GetHeight(){return Height;}
};

class Square : public TwoDSimpleShape{
	public:
		Square(uint16_t L): TwoDSimpleShape(L, L){}
		void SetLength(uint16_t L){ Width=L; Height=L;}
		uint16_t GetLength(){return Width;}
};

int main()
{
	cout << "Hello World" << endl;

	TwoDSimpleShape *rectangle = new Rectangle(3, 3);
	cout << rectangle->CalculateArea() << endl;

	TwoDSimpleShape *square = new Square(3);
	cout << square->CalculateArea() << endl;

	delete rectangle;
	delete square;
	cout << "End!" << endl;

	return 0;
}
