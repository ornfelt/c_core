#include <iostream>
#include <cstdint>

using namespace std;

/*
https://www.linkedin.com/pulse/first-5-principles-oop-c-what-so-solid-abdalrahman-hesham

Liskov Substitution Principle

This principle states that every derived class should be substitutable for their base
class. In other words, derived classes should behave correctly, as expected and avoid
logical errors due to their parent class.

Say we have a Rectangle class, which is a basic class that has width and height
attributes, set and get width functions, set and get height functions and a calculate area
function, as seen below.

what's the problem with the code below? Isn't the square correctly handling the dimension
inequality case?

Well, the problem is that the user using "SetWidth" and "SetHeight" functions might not
get that they change the other attribute, so the user might get unexpected results when
calling "CalculateArea" function.

So, to sum it up, This Square class isn't substitutable for the Rectangle class, and
thereby breaks Liskov principle. See c++ code below, then go back to the C# solution.

For example, if we were to write a test for the classes below the results would differ.
In C#: 
[TestMethod]
public void TwentyFourfor4x6RectanglefromSquare()
{
	Rectangle newRectangle = new Square();
	newRectangle.Height = 4;
	newRectangle.Width = 6;
	var result = AreaCalculator.CalculateArea(newRectangle);
	Assert.AreEqual(24, result);
}
 
The above test would fail because the expected result is 24, however, the actual area
calculated would be 36.
This is the problem. Even though the Square class is a subset of the Rectangle class, the
Object of Rectangle class is not substitutable by the object of the Square class without
causing a problem in the system. If the system adhered to the Liskov Substitution
Principle, you may avoid the above problem.

We can fix the issues like this:
public abstract class Shape
{
	public abstract int Area();
}
 
Here we have moved an abstract method Area in the Shape class and each subclass will give
its own definition to the Area method. Rectangle and Square class can be modified as shown
in the listing below:
public class Rectangle : Shape
{
	public int Height { get; set; }
	public int Width { get; set; }
	public override int Area()
	{
		return Height * Width;
	}
}
 
public class Square : Shape
{
	public int Sides;
	public override int Area()
	{
		return Sides * Sides;
	}
}

Then...
[TestMethod]
public void TwentyFourfor4x6Rectangleand9for3x3Square()
{
	var shapes = new List<Shape>{
		new Rectangle{Height=4,Width=6},
		new Square{Sides=3}
	};
	var areas = new List<int>();

	foreach (Shape shape in shapes)
	{
		areas.Add(shape.Area());
	}
	Assert.AreEqual(24, areas[0]);
	Assert.AreEqual(9, areas[1]);
}

C# example from:
https://www.infragistics.com/community/blogs/b/dhananjay_kumar/posts/simplifying-the-liskov-substitution-principle-of-solid-in-c

ALSO:
From: https://www.youtube.com/watch?v=Ntraj80qN2k&t=582s

Behavioral subtyping (aka “IS-A” relationship)
• Contravariance of method arguments in a subtype.
• Covariance of return types in a subtype.
• Preconditions cannot be strengthened in a subtype.
• Postconditions cannot be weakened in a subtype.
• Invariants of the super type must be preserved in a subtype.

Guideline: Make sure that inheritance is about behavior, not about data.
Guideline: Make sure that the contract of base types is adhered to.
Guideline: Make sure to adhere to the required concept.
*/

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
		virtual ~Rectangle() = default;
};

class Square : public Rectangle{
	public:
		Square(uint16_t L): Rectangle(L, L){}
		void SetWidth(uint16_t width) override{
			Width = width; Height = width;
		}
		void SetHeight(uint16_t height) override{
			Width = height; Height = height;
		}
		uint16_t GetWidth() override{return Width;}
		uint16_t GetHeight() override{return Height;}
};
