#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/*
https://www.youtube.com/watch?v=Ntraj80qN2k&t=582s
Powerpoint: https://github.com/CppCon/CppCon2020/blob/main/Presentations/breaking_dependencies_the_solid_principles/breaking_dependencies_the_solid_principles__klaus_iglberger__cppcon_2020.pdf
*/

class Shape
{
	public:
		Shape() = default;
		virtual ~Shape() = default;
		//virtual void translate( Vector3D const& ) = 0;
		//virtual void rotate( Quaternion const& ) = 0;
		virtual void draw() const = 0;
};

class Circle : public Shape
{
	public:
		explicit Circle( double rad )
		: radius{ rad }
		//, // ... Remaining data members
		{}
		virtual ~Circle() = default;
		double getRadius() const noexcept;
		// ... getCenter(), getRotation(), ...
		//void translate( Vector3D const& ) override;
		//void rotate( Quaternion const& ) override;
		void draw() const override { cout << "Drawing circle..." << endl; }
	private:
		double radius;
		// ... Remaining data members
};

class Square : public Shape
{
	public:
		explicit Square( double s ) : side{ s } 
		//, // ... Remaining data members
		{}
		virtual ~Square() = default;
		double getSide() const noexcept;
		// ... getCenter(), getRotation(), ...
		//void translate( Vector3D const& ) override;
		//void rotate( Quaternion const& ) override;
		void draw() const override { cout << "Drawing Square..." << endl; }
	private:
		double side;
		// ... Remaining data members
};

void draw(std::vector<std::unique_ptr<Shape>> const& shapes )
{
	for( auto const& s : shapes )
	{
		s->draw();
	}
}

int main()
{
	cout << "Hello world" << endl;
	using Shapes = std::vector<std::unique_ptr<Shape>>;
	// Creating some shapes
	Shapes shapes;
	shapes.push_back( std::make_unique<Circle>( 2.0 ) );
	shapes.push_back( std::make_unique<Square>( 1.5 ) );
	shapes.push_back( std::make_unique<Circle>( 4.2 ) );
	// Drawing all shapes
	draw( shapes );

	cout << "End!" << endl;
}
