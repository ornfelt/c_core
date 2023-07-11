![C++ Design Patterns for Humans](https://user-images.githubusercontent.com/20260845/56855972-fb720600-691e-11e9-9efc-4755d6b4cb5b.png)

---

<p align="center">
🎉 Ultra-simplified explanation to design patterns! 🎉
</p>
<p align="center">
A topic that can easily make anyone's mind wobble. Here I try to make them stick
in to your mind (and maybe mine) by explaining them in the <i>simplest</i> way
possible. 
</p>
<p align="center">
This work is a derivative of
<a href="https://github.com/kamranahmedse/design-patterns-for-humans">
"Design Patterns for Humans"</a> by <a href="https://github.com/kamranahmedse">
kamranahmedse</a>, used under
<a href="https://creativecommons.org/licenses/by/4.0/">CC BY 4.0</a>.
</p>

---

## Introduction

Design patterns are solutions to recurring problems; **guidelines for how to
tackle certain problems**. They are not classes, packages, or libraries that
you can plug into your application and wait for the magic to happen. These are,
rather, guidelines on how to tackle certain problems in certain situations.

> Design patterns are solutions to recurring problems; guidelines for how to
> tackle certain problems.

Wikipedia describes design patterns as:

> [...] a general reusable solution to a commonly occurring problem within a
> given context in software design. It is not a finished design that can be
> transformed directly into source or machine code. It is a description or
> template for how to solve a problem that can be used in many different
> situations.

### ⚠️ Be Careful

- Design patterns are not a silver bullet to all your problems.
- Do not try to force them; bad things are supposed to happen, if done so.
- Keep in mind that design patterns are solutions **to** problems, not solutions
  **finding** problems; so don't overthink.
- If used in a correct place in a correct manner, they can prove to be a savior;
  or else they can result in a horrible mess of a code.

## Types of Design Patterns

- [Creational](#creational-design-patterns)
- [Structural](#structural-design-patterns)
- [Behavioral](#behavioral-design-patterns)

## Creational Design Patterns

In plain words:

> Creational patterns are focused towards how to instantiate an object or group
> of related objects.

Wikipedia says:

> In software engineering, creational design patterns are design patterns that
> deal with object creation mechanisms, trying to create objects in a manner
> suitable to the situation. The basic form of object creation could result in
> design problems or added complexity to the design. Creational design patterns
> solve this problem by somehow controlling this object creation.

- [Simple Factory](#-simple-factory)
- [Factory Method](#-factory-method)
- [Abstract Factory](#-abstract-factory)
- [Builder](#-builder)
- [Prototype](#-prototype)
- [Singleton](#-singleton)

### 🏠 Simple Factory

#### Overview

Real world example:

> Consider, you are building a house and you need doors. You can either put on
> your carpenter clothes, bring some wood, glue, nails and all the tools required
> to build the door and start building it in your house or you can simply call the
> factory and get the built door delivered to you so that you don't need to learn
> anything about the door making or to deal with the mess that comes with making
> it.

In plain words:

> Simple factory simply generates an instance for client without exposing any
> instantiation logic to the client.

Wikipedia says:

> In object-oriented programming (OOP), a factory is an object for creating
> other objects – formally a factory is a function or method that returns objects
> of a varying prototype or class from some method call, which is assumed to be
> "new".

#### Programmatic Example

First of all we have a door base class and a wooden door derived class:

```cpp
class Door
{
  public:
    virtual float getWidth(void) = 0;
    virtual float getHeight(void) = 0;
};

class WoodenDoor : public Door
{
  public:
    WoodenDoor(float width, float height)
        : width_(width), height_(height)
    {
    }

    float getWidth(void)
    {
      return width_;
    }

    float getHeight(void)
    {
      return height_;
    }

  private:
    float width_;
    float height_;
};
```

Then we have our door factory that makes the door and returns it:

```cpp
class DoorFactory
{
  public:
    static std::shared_ptr<Door> makeDoor(float width, float height)
    {
      return std::make_shared<WoodenDoor>(width, height);
    }
};
```

Here is how this can be used:

```cpp
// Make a door with dimensions 100x200.
std::shared_ptr<Door> door = DoorFactory::makeDoor(100, 200);

std::cout << "width = " << door->getWidth() << std::endl;
// Output: width = 100
std::cout << "height = " << door->getHeight() << std::endl;
// Output: height = 200

// We can use the factory again to make a door with dimensions 50x100.
std::shared_ptr<Door> door2 = DoorFactory::makeDoor(50, 100);

std::cout << "width = " << door2->getWidth() << std::endl;
// Output: width = 50
std::cout << "height = " << door2->getHeight() << std::endl;
// Output: height = 100
```

#### When To Use

When creating an object is not just a few assignments and involves some logic,
it makes sense to put it in a dedicated factory instead of repeating the same
code everywhere.

### 🏭 Factory Method

#### Overview

Real world example:

> Consider the case of a hiring manager. It is impossible for one person to
> interview for each of the positions. Based on the job opening, she has to decide
> and delegate the interview steps to different people.

In plain words:

> It provides a way to delegate the instantiation logic to child classes.

Wikipedia says:

> In class-based programming, the factory method pattern is a creational pattern
> that uses factory methods to deal with the problem of creating objects without
> having to specify the exact class of the object that will be created. This is
> done by creating objects by calling a factory method—either specified in an
> interface and implemented by child classes, or implemented in a base class and
> optionally overridden by derived classes—rather than by calling a constructor.

#### Programmatic Example

Taking our hiring manager example above. First of all we have an interviewer
interface and some implementations for it:

```cpp
class Interviewer
{
  public:
    virtual void askQuestions(void) = 0;
};

class Developer : public Interviewer
{
  public:
    void askQuestions(void)
    {
      std::cout << "Asking about design patterns!" << std::endl;
    }
};

class CommunityExecutive : public Interviewer
{
  public:
    void askQuestions(void)
    {
      std::cout << "Asking about community building!" << std::endl;
    }
};
```

Now let us create our hiring manager class:

```cpp
class HiringManager
{
  public:
    void takeInterview(void)
    {
      std::shared_ptr<Interviewer> interviewer = makeInterviewer();
      interviewer->askQuestions();
    }

  protected:
    virtual std::shared_ptr<Interviewer> makeInterviewer(void) = 0;
};
```

Now any child can extend it and provide the required interviewer:

```cpp
class DevelopmentManager : public HiringManager
{
  protected:
    std::shared_ptr<Interviewer> makeInterviewer(void)
    {
      return std::make_shared<Developer>();
    }
};

class MarketingManager : public HiringManager
{
  protected:
    std::shared_ptr<Interviewer> makeInterviewer(void)
    {
      return std::make_shared<CommunityExecutive>();
    }
};
```

Here is how this can be used:

```cpp
DevelopmentManager developmentManager = DevelopmentManager();
developmentManager.takeInterview(); // Output: Asking about design patterns!

MarketingManager marketingManager = MarketingManager();
marketingManager.takeInterview(); // Output: Asking about community building!
```

#### When To Use

Useful when there is some generic processing in a class but the required
sub-class is dynamically decided at runtime. Or putting it in other words, when
the client doesn't know what exact sub-class it might need.

### 🔨 Abstract Factory

#### Overview

Real world example:

> Extending our door example from Simple Factory. Based on your needs you might
> get a wooden door from a wooden door shop, iron door from an iron shop or a PVC
> door from the relevant shop. Plus you might need a guy with different kind of
> specialities to fit the door, for example a carpenter for wooden door, welder
> for iron door etc. As you can see there is a dependency between the doors now,
> wooden door needs carpenter, iron door needs a welder etc.

In plain words:

> A factory of factories; a factory that groups the individual but
> related/dependent factories together without specifying their concrete classes.

Wikipedia says:

> The abstract factory pattern provides a way to encapsulate a group of
> individual factories that have a common theme without specifying their concrete
> classes.

#### Programmatic Example

Translating the door example above. First of all we have our door base class
and some derivation of it:

```cpp
class Door
{
  public:
    virtual void getDescription(void) = 0;
};

class WoodenDoor : public Door
{
  public:
    void getDescription(void)
    {
      std::cout << "I am a wooden door." << std::endl;
    }
};

class IronDoor : public Door
{
  public:
    void getDescription(void)
    {
      std::cout << "I am an iron door." << std::endl;
    }
};
```

Then we have some fitting experts for each door type:

```cpp
class DoorFittingExpert
{
  public:
    virtual void getDescription(void) = 0;
};

class Welder : public DoorFittingExpert
{
  public:
    void getDescription(void)
    {
      std::cout << "I can only fit iron doors." << std::endl;
    }
};

class Carpenter : public DoorFittingExpert
{
  public:
    void getDescription(void)
    {
      std::cout << "I can only fit wooden doors." << std::endl;

    }
};
```

Now we have our abstract factory that would let us make family of related
objects i.e. wooden door factory would create a wooden door and wooden door
fitting expert and iron door factory would create an iron door and iron door
fitting expert:

```cpp
class DoorFactory
{
  public:
    virtual std::shared_ptr<Door> makeDoor(void) = 0;
    virtual std::shared_ptr<DoorFittingExpert> makeFittingExpert(void) = 0;
};

class WoodenDoorFactory : public DoorFactory
{
  public:
    std::shared_ptr<Door> makeDoor(void)
    {
      return std::make_shared<WoodenDoor>();
    }

    std::shared_ptr<DoorFittingExpert> makeFittingExpert(void)
    {
      return std::make_shared<Carpenter>();
    }
};

class IronDoorFactory : public DoorFactory
{
  public:
    std::shared_ptr<Door> makeDoor(void)
    {
      return std::make_shared<IronDoor>();
    }

    std::shared_ptr<DoorFittingExpert> makeFittingExpert(void)
    {
      return std::make_shared<Welder>();
    }
};
```

Here is how this can be used:

```cpp
WoodenDoorFactory woodenFactory = WoodenDoorFactory();
std::shared_ptr<Door> door = woodenFactory.makeDoor();
std::shared_ptr<DoorFittingExpert> expert = woodenFactory.makeFittingExpert();

door->getDescription(); // Output: I am a wooden door.
expert->getDescription(); // Output: I can only fit wooden doors.

IronDoorFactory ironFactory = IronDoorFactory();
std::shared_ptr<Door> door2 = ironFactory.makeDoor();
std::shared_ptr<DoorFittingExpert> expert2 = woodenFactory.makeFittingExpert();

door2->getDescription(); // Output: I am an iron door.
expert2->getDescription(); // Output: I can only fit iron doors.
```

As you can see the wooden door factory has encapsulated the carpenter and the
wooden door also iron door factory has encapsulated the iron door and welder.
And thus it had helped us make sure that for each of the created door, we do not
get a wrong fitting expert.

#### When To Use

When there are interrelated dependencies with not-that-simple creation logic
involved.

### 👷 Builder

#### Overview

Real world example:

> Imagine you are at Hardee's and you order a specific deal, lets say,
> "Big Hardee" and they hand it over to you without _any questions_; this is the
> example of simple factory. But there are cases when the creation logic might
> involve more steps. For example you want a customized Subway deal, you have
> several options in how your burger is made e.g what bread do you want? what
> types of sauces would you like? What cheese would you want? etc. In such cases
> builder pattern comes to the rescue.

In plain words:

> Allows you to create different flavors of an object while avoiding constructor
> pollution. Useful when there could be several flavors of an object. Or when
> there are a lot of steps involved in creation of an object.

Wikipedia says:

> The builder pattern is an object creation software design pattern with the
> intentions of finding a solution to the telescoping constructor anti-pattern.

Having said that let me add a bit about what telescoping constructor
anti-pattern is. At one point or the other we have all seen a constructor like
below:

```cpp
class Burger
{
  public:
    Burger(int patties, bool cheese = true, bool pepperoni = true,
           bool tomato = true, bool lettuce = true);
}
```

As you can see; the number of constructor parameters can quickly get out of hand
and it might become difficult to understand the arrangement of parameters. Plus
this parameter list could keep on growing if you would want to add more options
in future. This is called telescoping constructor anti-pattern.

#### Programmatic Example

The sane alternative is to use the builder pattern. First of all we have our
burger that we want to make:

```cpp
class Burger
{
  public:
    Burger(BurgerBuilder* builder);
        : patties_(builder->patties), cheese_(builder->cheese),
          pepperoni_(builder->pepperoni), lettuce_(builder->lettuce),
          tomato_(builder->tomato)
    {
    }

    void getDescription(void);
    {
      std::cout << patties_ << " patties";
      if (cheese_) {
        std::cout << ", cheese";
      }
      if (pepperoni_) {
        std::cout << ", pepperoni";
      }
      if (lettuce_){
        std::cout << ", lettuce";
      }
      if (tomato_) {
        std::cout << ", tomato";
      }
      std::cout << std::endl;
    }

  private:
    int patties_;
    bool cheese_;
    bool pepperoni_;
    bool lettuce_;
    bool tomato_;
};
```

And then we have the builder

```cpp
class BurgerBuilder
{
  public:
    BurgerBuilder(int patties)
        : patties(patties), cheese(false), pepperoni(false), lettuce(false),
          tomato(false)
    {
    }

    BurgerBuilder& addCheese(void)
    {
      cheese = true;
      return (*this);
    }

    BurgerBuilder& addPepperoni(void)
    {
      pepperoni = true;
      return (*this);
    }

    BurgerBuilder& addLettuce(void)
    {
      lettuce = true;
      return (*this);
    }

    BurgerBuilder& addTomato(void)
    {
      tomato = true;
      return (*this);
    }

    std::shared_ptr<Burger> build(void)
    {
      return std::make_shared<Burger>(this);
    }

    int patties;
    bool cheese;
    bool pepperoni;
    bool lettuce;
    bool tomato;
};

```

Here is how this can be used:

```cpp
// One double patty burger with no dairy.
std::shared_ptr<Burger> burger = BurgerBuilder(2).
    addPepperoni().
    addLettuce().
    addTomato().
    build();
burger->getDescription();
// Output: 2 patties, pepperoni, lettuce, tomato

// One triple patty buger with everything.
std::shared_ptr<Burger> burger2 = BurgerBuilder(3).
    addPepperoni().
    addCheese().
    addLettuce().
    addTomato().
    build();
burger2->getDescription();
// Output: 3 patties, cheese, pepperoni, lettuce, tomato
```

#### When To Use

When there could be several flavors of an object and to avoid the constructor
telescoping. The key difference from the factory pattern is that; factory
pattern is to be used when the creation is a one step process while builder
pattern is to be used when the creation is a multi step process.

### 🐑 Prototype

#### Overview

Real world example:

> Remember dolly? The sheep that was cloned! Lets not get into the details but
> the key point here is that it is all about cloning.

In plain words:

> Create object based on an existing object through cloning.

Wikipedia says:

> The prototype pattern is a creational design pattern in software development.
> It is used when the type of objects to create is determined by a prototypical
> instance, which is cloned to produce new objects.

In short, it allows you to create a copy of an existing object and modify it to
your needs, instead of going through the trouble of creating an object from
scratch and setting it up.

#### Programmatic Example

Let's create a sheep class

```cpp
class Sheep
{
  public:
    Sheep(const std::string& name, const std::string& category)
        : name_(name), category_(category)
    {
    }

    void setName(const std::string name)
    {
      name_ = name;
    }

    std::string getName(void)
    {
      return name_;
    }

    void setCategory(const std::string category)
    {
      category_ = category;
    }

    std::string getCategory(void)
    {
      return category_;
    }

  private:
    std::string name_;
    std::string category_;
};
```

Here is how we can clone this object

```cpp
Sheep original = Sheep("Molly", "Mountain Sheep");
std::cout << original.getName() << std::endl; // Output: Molly
std::cout << original.getCategory() << std::endl; // Output: Mountain Sheep

Sheep clone = original;
clone.setName("Dolly");
std::cout << clone.getName() << std::endl; // Output: Dolly
std::cout << clone.getCategory() << std::endl; // Output: Mountain Sheep
```

#### When To Use

When an object is required that is similar to existing object or when the
creation would be expensive as compared to cloning.

### 💍 Singleton

#### Overview

Real world example:

> There can only be one president of a country at a time. The same president has
> to be brought to action, whenever duty calls. President here is singleton.

In plain words:

> Ensures that only one object of a particular class is ever created.

Wikipedia says:

> In software engineering, the singleton pattern is a software design pattern
> that restricts the instantiation of a class to one object. This is useful when
> exactly one object is needed to coordinate actions across the system.

Singleton pattern is actually considered an anti-pattern and overuse of it
should be avoided. It is not necessarily bad and could have some valid use-cases
but should be used with caution because it introduces a global state in your
application and change to it in one place could affect in the other areas and it
could become pretty difficult to debug. The other bad thing about them is it
makes your code tightly coupled plus mocking the singleton could be difficult.

#### Programmatic Example

To create a singleton, make the constructor private, disable cloning, and create
a static variable to house the instance.

```cpp
class President
{
  public:
    static President& getInstance()
    {
      static President instance;
      return instance;
    }

  private:
    President()
    {
    }

    ~President()
    {
    }
};
```

Here is how this can be used:

```cpp
President& president1 = President::getInstance();
President& president2 = President::getInstance();

// There can only be 1 president, so they must be the same.
assert(&president1 == &president2);
```

#### When To Use

When exactly one object is needed to coordinate actions across a system.

## Structural Design Patterns

In plain words:

> Structural patterns are mostly concerned with object composition or in other
> words how the entities can use each other. Or yet another explanation would be,
> they help in answering "How to build a software component?"

Wikipedia says:

> In software engineering, structural design patterns are design patterns that
> ease the design by identifying a simple way to realize relationships between
> entities.

- [Adapter](#-adapter)
- [Bridge](#-bridge)
- [Composite](#-composite)
- [Decorator](#-decorator)
- [Facade](#-facade)
- [Flyweight](#-flyweight)
- [Proxy](#-proxy)

### 🔌 Adapter

#### Overview

Real world example:

> Consider that you have some pictures in your memory card and you need to
> transfer them to your computer. In order to transfer them you need some kind of
> adapter that is compatible with your computer ports so that you can attach
> memory card to your computer. In this case card reader is an adapter.

Another real world example:

> Another example would be the famous power adapter; a three legged plug can't
> be connected to a two pronged outlet, it needs to use a power adapter that makes
> it compatible with the two pronged outlet.

And another:

> Yet another example would be a translator translating words spoken by one
> person to another.

In plain words:

> Adapter pattern lets you wrap an otherwise incompatible object in an adapter
> to make it compatible with another class.

Wikipedia says:

> In software engineering, the adapter pattern is a software design pattern that
> allows the interface of an existing class to be used as another interface. It is
> often used to make existing classes work with others without modifying their
> source code.

#### Programmatic Example

Consider a game where there is a hunter and he hunts lions. First we have a
lion class that all types of lions have to implement.

```cpp
class Lion
{
  public:
    virtual void roar(void) = 0;
};

class AfricanLion : public Lion
{
  public:
    void roar(void)
    {
      std::cout << "*African lion roar*" << std::endl;
    }
};

class AsianLion : public Lion
{
  public:
    void roar(void)
    {
      std::cout << "*Asian lion roar*" << std::endl;
    }
};
```

And hunter expects any implementation of lion class.

```cpp
class Hunter
{
  public:
    void hunt(Lion& lion)
    {
      lion.roar();
    }
};
```

Now let's say we have to add a wild dog in our game so that hunter can hunt
that also (Note: I do not condone the hunting of any dogs). But we can't do that
directly because dog has a different interface. To make it compatible for our
hunter, we will have to create an adapter that is compatible.

```cpp
class WildDog
{
  public:
    void bark(void)
    {
      std::cout << "*wild dog bark*" << std::endl;
    }
};

class WildDogAdapter : public Lion
{
  public:
    WildDogAdapter(std::shared_ptr<WildDog> dog)
        : dog_(dog)
    {
    }

    void roar(void)
    {
      dog_->bark();
    }

  private:
    std::shared_ptr<WildDog> dog_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<WildDog> wildDog = std::make_shared<WildDog>();
WildDogAdapter wildDogAdapter(wildDog);

Hunter hunter;
hunter.hunt(wildDogAdapter); // Output: *wild dog bark*
```

#### When To Use

When you need to make an object compatible with the interface of another class.

### 🚡 Bridge

#### Overview

Real world example:

> Consider you have a website with different pages and you are supposed to allow
> the user to change the theme. What would you do? Create multiple copies of each
> of the pages for each of the themes or would you just create separate theme and
> load them based on the user's preferences? Bridge pattern allows you to do the
> second i.e.

![With and without the bridge pattern](https://cloud.githubusercontent.com/assets/11269635/23065293/33b7aea0-f515-11e6-983f-98823c9845ee.png)

In plain words:

> Bridge pattern is about preferring composition over inheritance.
> Implementation details are pushed from a hierarchy to another object with a
> separate hierarchy.

Wikipedia says:

> The bridge pattern is a design pattern used in software engineering that is
> meant to "decouple an abstraction from its implementation so that the two can
> vary independently."

#### Programmatic Example

Translating our WebPage example from above. Here we have the web page hierarchy.

```cpp
class WebPage
{
  public:
    virtual std::string getContent(void) = 0;
};

class About : public WebPage
{
  public:
    About(std::shared_ptr<Theme> theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "About page in " + theme_->getColor();
    }

  private:
    std::shared_ptr<Theme> theme_;
};

class Projects : public WebPage
{
  public:
    Projects(std::shared_ptr<Theme> theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "Projects page in " + theme_->getColor();
    }

  private:
    std::shared_ptr<Theme> theme_;
};


class Careers : public WebPage
{
  public:
    Careers(std::shared_ptr<Theme> theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "Careers page in " + theme_->getColor();
    }

  private:
    std::shared_ptr<Theme> theme_;
};
```

And the separate theme hierarchy.

```cpp
class Theme
{
  public:
    virtual std::string getColor(void) = 0;
};

class DarkTheme : public Theme
{
  public:
    std::string getColor(void)
    {
      return "dark palette";
    }
};

class LightTheme : public Theme
{
  public:
    std::string getColor(void)
    {
      return "light palette";
    }
};

class AquaTheme : public Theme
{
  public:
    std::string getColor(void)
    {
      return "aqua palette";
    }
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Theme> darkTheme = std::make_shared<DarkTheme>();
About about(darkTheme);
Careers careers(darkTheme);

std::cout << about.getContent() << std::endl;
// Output: About page in dark palette
std::cout << careers.getContent() << std::endl;
// Output: Careers page in dark palette
```

#### When To Use

When you need to implement several variants of some functionality for a class,
you find yourself extending a class in competing ways, or you need to allow
switching between implementations at runtime.

### 🌿 Composite

#### Overview

Real world example:

> Every organization is composed of employees. Each of the employees has the
> same features i.e. has a salary, has some responsibilities, may or may not
> report to someone, may or may not have some subordinates etc.

In plain words:

> Composite pattern lets clients treat the individual objects in a uniform
> manner.

Wikipedia says:

> In software engineering, the composite pattern is a partitioning design
> pattern. The composite pattern describes that a group of objects is to be
> treated in the same way as a single instance of an object. The intent of a
> composite is to "compose" objects into tree structures to represent part-whole
> hierarchies. Implementing the composite pattern lets clients treat individual
> objects and compositions uniformly.

#### Programmatic Example

Taking our employees example from above. Here we have different employee types

```cpp
class Employee
{
  public:
    virtual std::string getName(void) = 0;
    virtual void setSalary(float salary) = 0;
    virtual float getSalary(void) = 0;
    virtual std::string getRole(void) = 0;
};

class Developer : public Employee
{
  public:
    Developer(const std::string& name, float salary)
        : name_(name), salary_(salary), role_("Developer")
    {
    }

    std::string getName(void)
    {
      return name_;
    }

    void setSalary(float salary)
    {
      salary_ = salary;
    }

    float getSalary(void)
    {
      return salary_;
    }

    std::string getRole(void)
    {
      return role_;
    }

  private:
    std::string name_;
    float salary_;
    std::string role_;
};

class Designer : public Employee
{
  public:
    Designer(const std::string& name, float salary)
        : name_(name), salary_(salary), role_("Designer")
    {
    }

    std::string getName(void)
    {
      return name_;
    }

    void setSalary(float salary)
    {
      salary_ = salary;
    }

    float getSalary(void)
    {
      return salary_;
    }

    std::string getRole(void)
    {
      return role_;
    }

  private:
    std::string name_;
    float salary_;
    std::string role_;
};
```

Then we have an organization which consists of several different types of employees

```cpp
class Organization
{
  public:
    void addEmployee(std::shared_ptr<Employee> employee)
    {
      employees_.push_back(employee);
    }

    float getNetSalaries(void)
    {
      float net = 0;
      for (auto employee : employees_) {
        net += employee->getSalary();
      }

      return net;
    }

  private:
    std::vector<std::shared_ptr<Employee>> employees_;
};
```

Here is how this can be used:

```cpp
// Prepare the employees.
std::shared_ptr<Employee> jane = std::make_shared<Developer>("Jane", 50000);
std::shared_ptr<Employee> john = std::make_shared<Designer>("John", 45000);

// Add them to the organization.
Organization org;
org.addEmployee(jane);
org.addEmployee(john);

// Get the net salaries.
std::cout << org.getNetSalaries() << std::endl; // Output: 95000
```

#### When To Use

TODO

### ☕ Decorator

#### Overview

Real world example:

> Imagine you run a car service shop offering multiple services. Now how do you
> calculate the bill to be charged? You pick one service and dynamically keep
> adding to it the prices for the provided services till you get the final cost.
> Here each type of service is a decorator.

In plain words:

> Decorator pattern lets you dynamically change the behavior of an object at
> run time by wrapping them in an object of a decorator class.

Wikipedia says:

> In object-oriented programming, the decorator pattern is a design pattern that
> allows behavior to be added to an individual object, either statically or
> dynamically, without affecting the behavior of other objects from the same
> class. The decorator pattern is often useful for adhering to the Single
> Responsibility Principle, as it allows functionality to be divided between
> classes with unique areas of concern.

#### Programmatic Example

Lets take coffee for example. First of all we have a simple coffee implementing
the coffee class

```cpp
class Coffee
{
  public:
    virtual float getPrice(void) = 0;
    virtual std::string getDescription(void) = 0;
};

class SimpleCoffee : public Coffee
{
  public:
    float getPrice(void)
    {
      return 3;
    }

    std::string getDescription(void)
    {
      return "Simple coffee";
    }
};
```

We want to make the code extensible to allow options to modify it if required.
Lets make some add-ons (decorators)

```cpp
class MilkCoffee : public Coffee
{
  public:
    MilkCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 0.5;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", milk";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

class WhipCoffee : public Coffee
{
  public:
    WhipCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 2;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", whip";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

class VanillaCoffee : public Coffee
{
  public:
    VanillaCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 1;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", vanilla";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Coffee> simple = std::make_shared<SimpleCoffee>();
std::cout << simple->getPrice() << std::endl;
// Output: 3
std::cout << simple->getDescription() << std::endl;
// Output: Simple coffee

std::shared_ptr<Coffee> milk = std::make_shared<MilkCoffee>(simple);
std::cout << milk->getPrice() << std::endl;
// Output: 3.5
std::cout << milk->getDescription() << std::endl;
// Output: Simple coffee, milk

std::shared_ptr<Coffee> whip = std::make_shared<WhipCoffee>(milk);
std::cout << whip->getPrice() << std::endl;
// Output: 5.5
std::cout << whip->getDescription() << std::endl;
// Output: Simple coffee, milk, whip

std::shared_ptr<Coffee> vanilla = std::make_shared<VanillaCoffee>(whip);
std::cout << vanilla->getPrice() << std::endl;
// Output: 6.5
std::cout << vanilla->getDescription() << std::endl;
// Output: Simple coffee, milk, whip, vanilla
```

#### When To Use

TODO

### 📦 Facade

#### Overview

Real world example:

> How do you turn on the computer? "Hit the power button" you say! That is what
> you believe because you are using a simple interface that computer provides on
> the outside, internally it has to do a lot of stuff to make it happen. This
> simple interface to the complex subsystem is a facade.

In plain words:

> Facade pattern provides a simplified interface to a complex subsystem.

Wikipedia says:

> A facade is an object that provides a simplified interface to a larger body of
> code, such as a class library.

#### Programmatic Example

Taking our computer example from above. Here we have the computer class

```cpp
class Computer
{
  public:
    void makeBootSound(void)
    {
      std::cout << "Beep!" << std::endl;
    }

    void showLoadingScreen(void)
    {
      std::cout << "Loading..." << std::endl;
    }

    void showWelcomeScreen(void)
    {
      std::cout << "Ready to use!" << std::endl;
    }

    void closeEverything(void)
    {
      std::cout << "Closing all programs!" << std::endl;
    }
    void sleep(void)
    {
      std::cout << "Zzz" << std::endl;
    }
};
```

Here we have the facade

```cpp
class ComputerFacade
{
  public:
    ComputerFacade(std::shared_ptr<Computer> computer)
        : computer_(computer)
    {
    }

    void turnOn(void)
    {
      computer_->makeBootSound();
      computer_->showLoadingScreen();
      computer_->showWelcomeScreen();
    }

    void turnOff(void)
    {
      computer_->closeEverything();
      computer_->sleep();
    }

  private:
    std::shared_ptr<Computer> computer_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Computer> computer = std::make_shared<Computer>();
ComputerFacade facade(computer);

facade.turnOn();
// Output:
// Beep!
// Loading...
// Ready to use!

facade.turnOff();
// Output:
// Closing all programs!
// Zzz
```

#### When To Use

TODO

### 🍃 Flyweight

#### Overview

Real world example:

> Did you ever have fresh tea from some stall? They often make more than one
> cup that you demanded and save the rest for any other customer so to save the
> resources e.g. gas etc. Flyweight pattern is all about that i.e. sharing.

In plain words:

> It is used to minimize memory usage or computational expenses by sharing as
> much as possible with similar objects.

Wikipedia says:

> In computer programming, flyweight is a software design pattern. A flyweight
> is an object that minimizes memory use by sharing as much data as possible with
> other similar objects; it is a way to use objects in large numbers when a simple
> repeated representation would use an unacceptable amount of memory.

#### Programmatic Example

Translating our tea example from above. First of all we have tea types and tea
maker

```cpp
struct Tea
{
};

class TeaMaker
{
  public:
    std::shared_ptr<Tea> make(const std::string& preference)
    {
      auto match = availableTea_.find(preference);
      if (match == availableTea_.end()) {
        availableTea_[preference] = std::make_shared<Tea>();
      }

      return availableTea_[preference];
    }

    int getPreferenceCount(void)
    {
      return availableTea_.size();
    }

  private:
    std::unordered_map<std::string, std::shared_ptr<Tea>> availableTea_;
};
```

Then we have the tea shop which takes orders and serves them

```cpp
class TeaShop
{
  public:
    TeaShop(std::shared_ptr<TeaMaker> maker)
        : maker_(maker)
    {
    }

    void takeOrder(const std::string& preference, int table)
    {
      orders_[table] = maker_->make(preference);
    }

    void serve(void)
    {
      for (auto order : orders_) {
        std::cout << "Serving tea to table " << order.first << std::endl;
      }
    }

    int getPreferenceCount(void)
    {
      return maker_->getPreferenceCount();
    }

  private:
    std::shared_ptr<TeaMaker> maker_;
    std::unordered_map<int, std::shared_ptr<Tea>> orders_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<TeaMaker> maker = std::make_shared<TeaMaker>();
TeaShop shop(maker);

// No orders have been taken, so there are no available teas.
std::cout << shop.getPreferenceCount() << std::endl; // Output: 0

// Take some orders.
shop.takeOrder("half sugar", 1);
shop.takeOrder("with milk", 2);
shop.takeOrder("with boba", 5);

// We create a new batch of tea for each preference.
std::cout << shop.getPreferenceCount() << std::endl; // Output: 3

// Take an order with a previously requested preference.
shop.takeOrder("half sugar", 4);

// Since we have some tea from the last time this request was made, no new
// batch was created.
std::cout << shop.getPreferenceCount() << std::endl; // Output: 3

// Serve the customers.
shop.serve();
// Output: (Note: Since the map is unordered, the serving order may vary.)
// Serving tea to table 4
// Serving tea to table 5
// Serving tea to table 1
// Serving tea to table 2
```

#### When To Use

TODO

### 🎱 Proxy

#### Overview

Real world example:

> Have you ever used an access card to go through a door? There are multiple
> options to open that door i.e. it can be opened either using access card or by
> pressing a button that bypasses the security. The door's main functionality is
> to open but there is a proxy added on top of it to add some functionality. Let
> me better explain it using the code example below.

In plain words:

> Using the proxy pattern, a class represents the functionality of another
> class.

Wikipedia says:

> A proxy, in its most general form, is a class functioning as an interface to
> something else. A proxy is a wrapper or agent object that is being called by the
> client to access the real serving object behind the scenes. Use of the proxy can
> simply be forwarding to the real object, or can provide additional logic. In the
> proxy extra functionality can be provided, for example caching when operations
> on the real object are resource intensive, or checking preconditions before
> operations on the real object are invoked.

#### Programmatic Example

Taking our security door example from above. Firstly we have the door class
and an implementation of door

```cpp
class Door
{
  public:
    virtual void open(void) = 0;
    virtual void close(void) = 0;
};

class LabDoor : public Door
{
  public:
    void open(void)
    {
      std::cout << "Opening lab door" << std::endl;
    }

    void close(void)
    {
      std::cout << "Closing lab door" << std::endl;
    }
};
```

Then we have a proxy to secure any doors that we want

```cpp
class SecuredDoor
{
  public:
    SecuredDoor(std::shared_ptr<Door> door)
        : door_(door)
    {
    }

    void open(const std::string& password)
    {
      if (authenticate(password)) {
        door_->open();
      } else {
        std::cout << "No way, Jose!" << std::endl;
      }
    }

    void close(void)
    {
      door_->close();
    }

  private:
    bool authenticate(const std::string& password)
    {
      return password == "Bond007";
    }

    std::shared_ptr<Door> door_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Door> labDoor = std::make_shared<LabDoor>();
SecuredDoor securedDoor(labDoor);

securedDoor.open("invalid"); // Output: No way, Jose!
securedDoor.open("Bond007"); // Output: Opening lab door
securedDoor.close(); // Output: Closing lab door
```

#### When To Use

TODO

## Behavioral Design Patterns

In plain words:

> It is concerned with assignment of responsibilities between the objects. What
> makes them different from structural patterns is they don't just specify the
> structure but also outline the patterns for message passing/communication
> between them. Or in other words, they assist in answering "How to run a behavior
> in software component?"

Wikipedia says:

> In software engineering, behavioral design patterns are design patterns that
> identify common communication patterns between objects and realize these
> patterns. By doing so, these patterns increase flexibility in carrying out this
> communication.

- [Chain of Responsibility](#-chain-of-responsibility)
- [Command](#-command)
- [Iterator](#-iterator)
- [Mediator](#-mediator)
- [Memento](#-memento)
- [Observer](#-observer)
- [Visitor](#-visitor)
- [Strategy](#-strategy)
- [State](#-state)
- [Template Method](#-template-method)

### 🔗 Chain of Responsibility

#### Overview

Real world example:

> For example, you have three payment methods (`A`, `B` and `C`) setup in your
> account; each having a different amount in it. `A` has 100 USD, `B` has 300 USD
> and `C` having 1000 USD and the preference for payments is chosen as `A` then
> `B` then `C`. You try to purchase something that is worth 210 USD. Using Chain
> of Responsibility, first of all account `A` will be checked if it can make the
> purchase, if yes purchase will be made and the chain will be broken. If not,
> request will move forward to account `B` checking for amount if yes chain will
> be broken otherwise the request will keep forwarding till it finds the suitable
> handler. Here `A`, `B` and `C` are links of the chain and the whole phenomenon
> is Chain of Responsibility.

In plain words:

> It helps building a chain of objects. Request enters from one end and keeps
> going from object to object till it finds the suitable handler.

Wikipedia says:

> In object-oriented design, the chain-of-responsibility pattern is a design
> pattern consisting of a source of command objects and a series of processing
> objects. Each processing object contains logic that defines the types of command
> objects that it can handle; the rest are passed to the next processing object in
> the chain.

#### Programmatic Example

Translating our account example above. First of all we have a base account
having the logic for chaining the accounts together and some accounts.

```cpp
class Account
{
  public:
    Account(void)
        : name_("empty account"), balance_(0), successor_()
    {
    }

    void setNext(std::shared_ptr<Account> account)
    {
      successor_ = account;
    }

    void pay(float amount)
    {
      if (canPay(amount)) {
        std::cout << "Paid " << amount << " using " << name_ << "."
                  << std::endl;
        balance_ -= amount;
      } else if (successor_) {
        std::cout << "Cannot pay using " << name_ << ". Proceeding ..."
                  << std::endl;
        successor_->pay(amount);
      } else {
        std::cerr << "None of the accounts have enough balance." << std::endl;
      }
    }

    bool canPay(float amount)
    {
      return balance_ >= amount;
    }

  protected:
    std::string name_;
    float balance_;
    std::shared_ptr<Account> successor_;
};

class Bank : public Account
{
  public:
    Bank(float balance)
    {
      name_ = "bank";
      balance_ = balance;
    }
};

class Paypal : public Account
{
  public:
    Paypal(float balance)
    {
      name_ = "paypal";
      balance_ = balance;
    }
};

class Bitcoin : public Account
{
  public:
    Bitcoin(float balance)
    {
      name_ = "bitcoin";
      balance_ = balance;
    }
};
```

Now let's prepare the chain using the links defined above (i.e., Bank, Paypal,
Bitcoin).

```cpp
// We are going to create the chain: bank->paypal->bitcoin.

// First, create the accounts.
std::shared_ptr<Bank> bank = std::make_shared<Bank>(100);
std::shared_ptr<Paypal> paypal = std::make_shared<Paypal>(200);
std::shared_ptr<Bitcoin> bitcoin = std::make_shared<Bitcoin>(300);

// Next, establish the order.
bank->setNext(paypal);
paypal->setNext(bitcoin);

// Let's try to pay using the first priority (i.e., the bank).
bank->pay(250);
// Output:
// Cannot pay using bank. Proceeding ...
// Cannot pay using paypal. Proceeding ...
// Paid 250 using bitcoin.
```

#### When To Use

TODO

### 👮 Command

#### Overview

Real world example:

> A generic example would be you ordering food at a restaurant. You (i.e.
> `Client`) ask the waiter (i.e. `Invoker`) to bring some food (i.e. `Command`)
> and waiter simply forwards the request to Chef (i.e. `Receiver`) who has the
> knowledge of what and how to cook.

Another example:

> Another example would be you (i.e. `Client`) switching on (i.e. `Command`) the
> television (i.e. `Receiver`) using a remote control (`Invoker`).

In plain words:

> Allows you to encapsulate actions in objects. The key idea behind this pattern
> is to provide the means to decouple client from receiver.

Wikipedia says:

> In object-oriented programming, the command pattern is a behavioral design
> pattern in which an object is used to encapsulate all information needed to
> perform an action or trigger an event at a later time. This information includes
> the method name, the object that owns the method and values for the method
> parameters.

#### Programmatic Example

First of all we have the receiver that has the implementation of every action
that could be performed.

```cpp
// The receiver.
class Bulb
{
  public:
    void turnOn(void)
    {
      std::cout << "Bulb has been lit." << std::endl;
    }

    void turnOff(void)
    {
      std::cout << "Darkness!" << std::endl;
    }
};
```

Then we have an interface that each of the commands are going to implement and
then we have a set of commands.

```cpp
class Command
{
  public:
    virtual void execute(void) = 0;
    virtual void undo(void) = 0;
    virtual void redo(void) = 0;
};

// A command.
class TurnOn : public Command
{
  public:
    TurnOn(std::shared_ptr<Bulb> bulb)
        : bulb_(bulb)
    {
    }

    void execute(void)
    {
      bulb_->turnOn();
    }

    void undo(void)
    {
      bulb_->turnOff();
    }

    void redo(void)
    {
      execute();
    }

  private:
    std::shared_ptr<Bulb> bulb_;
};

// Another command.
class TurnOff : public Command
{
  public:
    TurnOff(std::shared_ptr<Bulb> bulb)
        : bulb_(bulb)
    {
    }

    void execute(void)
    {
      bulb_->turnOff();
    }

    void undo(void)
    {
      bulb_->turnOn();
    }

    void redo(void)
    {
      execute();
    }

  private:
    std::shared_ptr<Bulb> bulb_;
};
```

Then we have an invoker with whom the client will interact to process any
commands.

```cpp
// The invoker.
class RemoteControl
{
  public:
    void submit(std::shared_ptr<Command> command)
    {
      command->execute();
    }
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Bulb> bulb = std::make_shared<Bulb>();

std::shared_ptr<TurnOn> turnOn = std::make_shared<TurnOn>(bulb);
std::shared_ptr<TurnOff> turnOff = std::make_shared<TurnOff>(bulb);

RemoteControl remote;
remote.submit(turnOn);
remote.submit(turnOff);
// Output:
// Bulb has been lit.
// Darkness!
```

Command pattern can also be used to implement a transaction based system. Where
you keep maintaining the history of commands as soon as you execute them. If the
final command is successfully executed, all good otherwise just iterate through
the history and keep executing the `undo` on all the executed commands.

#### When To Use

TODO

### ➿ Iterator

#### Overview

Real world example:

> An old radio set will be a good example of iterator, where user could start at
> some channel and then use next or previous buttons to go through the respective
> channels. Or take an example of MP3 player or a TV set where you could press the
> next and previous buttons to go through the consecutive channels or in other
> words they all provide an interface to iterate through the respective channels,
> songs or radio stations.

In plain words:

> It presents a way to access the elements of an object without exposing the
> underlying presentation.

Wikipedia says:

> In object-oriented programming, the iterator pattern is a design pattern in
> which an iterator is used to traverse a container and access the container's
> elements. The iterator pattern decouples algorithms from containers; in some
> cases, algorithms are necessarily container-specific and thus cannot be
> decoupled.

#### Programmatic Example

```cpp
#include <iostream>
#include <string>
#include <vector>

/**
 * C++ has its own implementation of iterator that works with a different
 * generics containers defined by the standard library.
 */

template <typename T, typename U>
class Iterator {
	public:
		typedef typename std::vector<T>::iterator iter_type;
		Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
			m_it_ = m_p_data_->m_data_.begin();
		}

		void First() {
			m_it_ = m_p_data_->m_data_.begin();
		}

		void Next() {
			m_it_++;
		}

		bool IsDone() {
			return (m_it_ == m_p_data_->m_data_.end());
		}

		iter_type Current() {
			return m_it_;
		}

	private:
		U *m_p_data_;
		iter_type m_it_;
};

/**
 * Generic Collections/Containers provides one or several methods for retrieving
 * fresh iterator instances, compatible with the collection class.
 */

template <class T>
class Container {
	friend class Iterator<T, Container>;

	public:
	void Add(T a) {
		m_data_.push_back(a);
	}

	Iterator<T, Container> *CreateIterator() {
		return new Iterator<T, Container>(this);
	}

	private:
	std::vector<T> m_data_;
};

class Data {
	public:
		Data(int a = 0) : m_data_(a) {}

		void set_data(int a) {
			m_data_ = a;
		}

		int data() {
			return m_data_;
		}

	private:
		int m_data_;
};

/**
 * The client code may or may not know about the Concrete Iterator or Collection
 * classes, for this implementation the container is generic so you can used
 * with an int or with a custom class.
 */
void ClientCode() {
	std::cout << "________________Iterator with int______________________________________" << std::endl;
	Container<int> cont;

	for (int i = 0; i < 10; i++) {
		cont.Add(i);
	}

	Iterator<int, Container<int>> *it = cont.CreateIterator();
	for (it->First(); !it->IsDone(); it->Next()) {
		std::cout << *it->Current() << std::endl;
	}

	Container<Data> cont2;
	Data a(100), b(1000), c(10000);
	cont2.Add(a);
	cont2.Add(b);
	cont2.Add(c);

	std::cout << "________________Iterator with custom Class______________________________" << std::endl;
	Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
	for (it2->First(); !it2->IsDone(); it2->Next()) {
		std::cout << it2->Current()->data() << std::endl;
	}
	delete it;
	delete it2;
}

int main() {
	ClientCode();
	return 0;
}

// Output:
/**
________________Iterator with int______________________________________
0
1
2
3
4
5
6
7
8
9
________________Iterator with custom Class______________________________
100
1000
10000
*/
```

#### When To Use

TODO

### 👽 Mediator

#### Overview

Real world example:

> A general example would be when you talk to someone on your mobile phone,
> there is a network provider sitting between you and them and your conversation
> goes through it instead of being directly sent. In this case network provider is
> mediator.

In plain words:

> Mediator pattern adds a third party object (called mediator) to control the
> interaction between two objects (called colleagues). It helps reduce the
> coupling between the classes communicating with each other. Because now they
> don't need to have the knowledge of each other's implementation.

Wikipedia says:

> In software engineering, the mediator pattern defines an object that
> encapsulates how a set of objects interact. This pattern is considered to be a
> behavioral pattern due to the way it can alter the program's running behavior.

#### Programmatic Example

```cpp
#include <iostream>
#include <string>
#include <list>
#include <initializer_list>

/**
 * The Mediator interface declares a method used by components to notify the
 * chatroom about various events. The Mediator may react to these events and
 * pass the execution to other components.

 initializer_list ref: https://en.cppreference.com/w/cpp/utility/initializer_list
 */
class Participant;
class Mediator {
	public:
		virtual ~Mediator(){};
		virtual void Register(Participant *participant) = 0;
		virtual void UnRegister(Participant *participant) = 0;
		virtual void Notify(Participant *sender, std::string event) const = 0;
		virtual void Send(std::string from, std::string to, std::string message) = 0;
};

/**
 * The Base Component provides the basic functionality of storing a chatroom's
 * instance inside component objects. AKA AbstractColleague / AbstractParticipant.
 */
class Participant {
	protected:
		Mediator *mediator_;
		std::string name_;

	public:
		Participant(const std::string name, Mediator *chatroom = nullptr) : name_(name), mediator_(chatroom) {
		}

		virtual ~Participant(){};

		void set_mediator(Mediator *chatroom) {
			this->mediator_ = chatroom;
		}

		void Send(std::string to, std::string message) {
			std::cout << "Participant: Sending message!" << std::endl;
			mediator_->Send(name_, to, message);
		}

		virtual void Receive(std::string from, std::string message) const {
			std::cout << from << " to " << name_ << ": " << message << std::endl;
		}

		std::string getName() {
			return name_;
		}
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete chatroom classes.
 * AKA ConcreteColleague, ConcreteParticipant.
 */
class Beatle : public Participant {
	public:
		Beatle(const std::string name) : Participant(name) { 
		}
		void DoA() {
			std::cout << "Component 1 does A.\n";
			this->mediator_->Notify(this, "A");
		}
		void DoB() {
			std::cout << "Component 1 does B.\n";
			this->mediator_->Notify(this, "B");
		}

		void Receive(std::string from, std::string message) const override {
			std::cout << "To a Beatle: ";
			Participant::Receive(from, message);
		}
};

class NonBeatle : public Participant {
	public:
		NonBeatle(const std::string name) : Participant(name) { 
		}
		void DoC() {
			std::cout << "Component 2 does C.\n";
			this->mediator_->Notify(this, "C");
		}
		void DoD() {
			std::cout << "Component 2 does D.\n";
			this->mediator_->Notify(this, "D");
		}

		void Receive(std::string from, std::string message) const override {
			std::cout << "To a non-Beatle: ";
			Participant::Receive(from, message);
		}
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
template<typename T>
class ChatRoom : public Mediator {
	private:
		std::list<T> participants;

	public:
		ChatRoom(std::initializer_list<T> participants_init_list) : participants(participants_init_list) {

			std::cout << "init list size: " << participants.size() << std::endl;
			std::list<Participant *>::iterator participant_it = participants.begin();
			while (participant_it != participants.end()) {
				std::cout << "Initializing participant: " << (*participant_it)->getName() << std::endl;
				(*participant_it)->set_mediator(this);
				++participant_it;
			}
		}

		void Register(Participant *participant) override {
			participants.push_back(participant);
		}

		void UnRegister(Participant *participant) override {
			participants.remove(participant);
		}

		void Notify(Participant *sender, std::string event) const override {
			if (event == "A") {
				std::cout << "Mediator reacts on A and triggers following operations:\n";
				//this->component2_->DoC();
			}
			if (event == "D") {
				std::cout << "Mediator reacts on D and triggers following operations:\n";
				//this->component1_->DoB();
				//this->component2_->DoC();
			}
		}

		void Send(std::string from, std::string to, std::string message) override {
			std::list<Participant *>::iterator participant_it = participants.begin();
			bool message_sent = false;

			while (participant_it != participants.end()) {
				if ((*participant_it)->getName() == to) {
					std::cout << "ChatRooom: Forwarding message to " << (*participant_it)->getName() << "..." << std::endl;
					(*participant_it)->Receive(from, message);
					message_sent = true;
				}
				++participant_it;
			}

			if (!message_sent)
				std::cout << "Invalid recipient: " << to << std::endl;
		}
};

/**
 * The client code.
 */
void ClientCode() {
	Participant *george = new Beatle("George"); // Harrison
	Participant *paul = new Beatle("Paul"); // McCartney
	Participant *ringo = new Beatle("Ringo"); // Starr
	Participant *john = new Beatle("John"); // Lennon
	Participant *yoko = new NonBeatle("Yoko");

	// Registration occurs in constructor
	ChatRoom<Participant*> *chatroom = new ChatRoom<Participant*>({george, paul, ringo, john, yoko});

	// New participants can be added later as well...
	Participant *jonas = new NonBeatle("Jonas");
	jonas->set_mediator(chatroom);
	chatroom->Register(jonas);

	// Testing
	std::cout << "\n";
	yoko->Send("John", "Hi John!");
	std::cout << "\n";
	paul->Send("Ringo", "All you need is love");
	std::cout << "\n";
	ringo->Send("George", "My sweet Lord");
	std::cout << "\n";
	paul->Send("John", "Can't buy me love");
	std::cout << "\n";
	john->Send("Yoko", "My sweet love");

	std::cout << "\n";
	paul->Send("Jonas", "Hi jonas!");
	std::cout << "\n";
	john->Send("Test", "invalid test message");
	std::cout << "\n";
	john->Send("Paul", "valid test message");

	std::cout << "\n";
	jonas->Send("Ringo", "valid test message2");

	delete george;
	delete paul;
	delete ringo;
	delete yoko;
	delete john;
	delete jonas;
	delete chatroom;
}

int main() {
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}

// Output:
/**
init list size: 5
Initializing participant: George
Initializing participant: Paul
Initializing participant: Ringo
Initializing participant: John
Initializing participant: Yoko

Participant: Sending message!
ChatRooom: Forwarding message to John...
To a Beatle: Yoko to John: Hi John!

Participant: Sending message!
ChatRooom: Forwarding message to Ringo...
To a Beatle: Paul to Ringo: All you need is love

Participant: Sending message!
ChatRooom: Forwarding message to George...
To a Beatle: Ringo to George: My sweet Lord

Participant: Sending message!
ChatRooom: Forwarding message to John...
To a Beatle: Paul to John: Can't buy me love

Participant: Sending message!
ChatRooom: Forwarding message to Yoko...
To a non-Beatle: John to Yoko: My sweet love

Participant: Sending message!
ChatRooom: Forwarding message to Jonas...
To a non-Beatle: Paul to Jonas: Hi jonas!

Participant: Sending message!
Invalid recipient: Test

Participant: Sending message!
ChatRooom: Forwarding message to Paul...
To a Beatle: John to Paul: valid test message

Participant: Sending message!
ChatRooom: Forwarding message to Ringo...
To a Beatle: Jonas to Ringo: valid test message2

End of program!
*/
```

#### When To Use

TODO

### 💾 Memento

#### Overview

Real world example:

> Take the example of calculator (i.e. originator), where whenever you perform
> some calculation the last calculation is saved in memory (i.e. memento) so that
> you can get back to it and maybe get it restored using some action buttons (i.e.
> caretaker).

In plain words:

> Memento pattern is about capturing and storing the current state of an object
> in a manner that it can be restored later on in a smooth manner.

Wikipedia says:

> The memento pattern is a software design pattern that provides the ability to
> restore an object to its previous state (undo via rollback).

Usually useful when you need to provide some sort of undo functionality.

#### Programmatic Example

```cpp
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

/**
 * The Memento interface provides a way to retrieve the memento's metadata, such
 * as creation date or name. However, it doesn't expose the SalesProspect's state.
 */
class Memento {
	public:
		virtual ~Memento() {}
		virtual std::string GetName() const = 0;
		virtual std::string date() const = 0;
		virtual std::string state() const = 0;
		const virtual std::string name() const = 0;
		const virtual std::string phone() const = 0;
		const virtual double budget() const = 0;
};

/**
 * The Concrete Memento contains the infrastructure for storing the SalesProspect's
 * state.
 */
class ConcreteMemento : public Memento {
	private:
		std::string date_;
		std::string state_;

		std::string name_;
		std::string phone_;
		double budget_;

	public:
		ConcreteMemento(std::string state, std::string name, std::string phone, double budget) : state_(state), name_(name), phone_(phone), budget_(budget) {
			this->state_ = state;
			std::time_t now = std::time(0);
			this->date_ = std::ctime(&now);
		}

		// Getters and setters
		const std::string name() const override { return name_; } 
		void name(const std::string& name) { name_ = name; }

		const std::string phone() const override { return phone_; } 
		void phone(const std::string& phone) { phone_ = phone; }

		const double budget() const override { return budget_; } 
		void budget(const double& budget) { budget_ = budget; }

		/**
		 * The SalesProspect uses this method when restoring its state.
		 */
		std::string state() const override {
			return this->state_;
		}
		/**
		 * The rest of the methods are used by the ProspectMemory to display metadata.
		 */
		std::string GetName() const override {
			return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
		}
		std::string date() const override {
			return this->date_;
		}
};

/**
 * The SalesProspect holds some important state that may change over time. It also
 * defines a method for saving the state inside a memento and another method for
 * restoring the state from it.
 */
class SalesProspect {
	/**
	 * @var string For the sake of simplicity, the originator's state is stored
	 * inside a single variable.
	 */
	private:
		std::string state_;
		std::string name_;
		std::string phone_;
		double budget_;

		std::string GenerateRandomString(int length = 10) {
			const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			int stringLength = sizeof(alphanum) - 1;

			std::string random_string;
			for (int i = 0; i < length; i++) {
				random_string += alphanum[std::rand() % stringLength];
			}
			return random_string;
		}

	public:
		SalesProspect(std::string state) : state_(state) {
			std::cout << "SalesProspect: My initial state is: " << this->state_ << "\n";
		}
		/**
		 * The SalesProspect's business logic may affect its internal state. Therefore,
		 * the client should backup the state before launching methods of the business
		 * logic via the save() method.
		 */
		void DoSomething() {
			std::cout << "SalesProspect: I'm doing something important.\n";
			this->state_ = this->GenerateRandomString(30);
			std::cout << "SalesProspect: and my state has changed to: " << this->state_ << "\n";

			// Change name, phone and budget...
		}

		// Getters and setters
		//const std::string& name() const { return name_; } 
		const std::string name() const { return name_; } 
		void name(const std::string& name) { name_ = name; }

		//const std::string& phone() const { return phone_; } 
		const std::string phone() const { return phone_; } 
		void phone(const std::string& phone) { phone_ = phone; }

		//const double& budget() const { return budget_; } 
		const double budget() const { return budget_; } 
		void budget(const double& budget) { budget_ = budget; }

		std::string state() const {
			return this->state_;
		}

		/**
		 * Saves the current state inside a memento.
		 */
		Memento *Save() {
			std::cout << "Saving state..." << std::endl;
			return new ConcreteMemento(this->state_, this->name_, this->phone_, this->budget_);
		}
		/**
		 * Restores the SalesProspect's state from a memento object.
		 */
		void Restore(Memento *memento) {
			this->state_ = memento->state();
			std::cout << "SalesProspect: My state has been restored to: " << this->state_ << "\n";

			this->name_ = memento->name();
			this->phone_ = memento->phone();
			this->budget_ = memento->budget();
			//this->name(memento->name());
			//this->phone(memento->phone());
			//this->budget(memento->budget());
			std::cout << "New name, phone and budget: " << name_ << ", " << phone_ << ", " << budget_ << std::endl;
		}
};

/**
 * The ProspectMemory doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */
class ProspectMemory {
	/**
	 * @var Memento[]
	 */
	private:
		std::vector<Memento *> mementos_;

		/**
		 * @var SalesProspect
		 */
		SalesProspect *originator_;

	public:
		ProspectMemory(SalesProspect* originator) : originator_(originator) {
		}

		~ProspectMemory() {
			for (auto m : mementos_) delete m;
		}

		void Backup() {
			std::cout << "\nCaretaker: Saving SalesProspect's state...\n";
			std::cout << "state, name, phone and budget: " << this->originator_->state() << "," << this->originator_->name() << ", " << this->originator_->phone() << ", " << this->originator_->budget() << std::endl;
			this->mementos_.push_back(this->originator_->Save());
		}
		void Undo() {
			if (!this->mementos_.size()) {
				return;
			}
			Memento *memento = this->mementos_.back();
			this->mementos_.pop_back();
			std::cout << "ProspectMemory: Restoring state to: " << memento->GetName() << "\n";
			try {
				this->originator_->Restore(memento);
			} catch (...) {
				this->Undo();
			}
		}
		void ShowHistory() const {
			std::cout << "ProspectMemory: Here's the list of mementos:\n";
			for (Memento *memento : this->mementos_) {
				std::cout << memento->GetName() << "\n";
				std::cout << "name, phone and budget: " << memento->name() << ", " << memento->phone() << ", " << memento->budget() << std::endl;
			}
		}
};

/**
 * Client code.
 */
void ClientCode() {
	SalesProspect *originator = new SalesProspect("Super-duper-super-puper-super.");
	ProspectMemory *caretaker = new ProspectMemory(originator);
	originator->name("Noel van Halen"); // setName
	originator->phone("(412) 256-0990"); // setPhone
	originator->budget(2500); // setBudget

	caretaker->Backup();
	originator->DoSomething();
	originator->name("Testing person"); // setName
	originator->phone("081111"); // setPhone
	originator->budget(25.9522); // setBudget

	caretaker->Backup();
	originator->DoSomething();
	originator->name("Leo Welch"); // setName
	originator->phone("(310) 209-7111"); // setPhone
	originator->budget(100000.25); // setBudget

	caretaker->Backup();
	originator->DoSomething();
	originator->name("Jonas test"); // setName
	originator->phone("123"); // setPhone
	originator->budget(1500); // setBudget
	std::cout << "\nstate, name, phone and budget (before rollback): " << originator->state() << originator->name() << ", " << originator->phone() << ", " << originator->budget() << std::endl;

	std::cout << "\n";
	caretaker->ShowHistory();
	std::cout << "\nClient: Now, let's rollback!\n\n";
	caretaker->Undo();
	std::cout << "\nClient: Once more!\n\n";
	caretaker->Undo();

	delete originator;
	delete caretaker;
}

int main() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}

// Output:
/**
SalesProspect: My initial state is: Super-duper-super-puper-super.

Caretaker: Saving SalesProspect's state...
state, name, phone and budget: Super-duper-super-puper-super.,Noel van Halen, (412) 256-0990, 2500
Saving state...
SalesProspect: I'm doing something important.
SalesProspect: and my state has changed to: Ud5dfGgugCCVZ8GedRiEHQVQ58ocEq

Caretaker: Saving SalesProspect's state...
state, name, phone and budget: Ud5dfGgugCCVZ8GedRiEHQVQ58ocEq,Testing person, 081111, 25.9522
Saving state...
SalesProspect: I'm doing something important.
SalesProspect: and my state has changed to: zbW9lLGF1tAYaDwiw9HwvwZgLNKkIX

Caretaker: Saving SalesProspect's state...
state, name, phone and budget: zbW9lLGF1tAYaDwiw9HwvwZgLNKkIX,Leo Welch, (310) 209-7111, 100000
Saving state...
SalesProspect: I'm doing something important.
SalesProspect: and my state has changed to: FoU9OjVBS7jM0KhmjaWC6KETsPQSWo

state, name, phone and budget (before rollback): FoU9OjVBS7jM0KhmjaWC6KETsPQSWoJonas test, 123, 1500

ProspectMemory: Here's the list of mementos:
Tue Jul 11 15:48:08 2023
 / (Super-dup...)
name, phone and budget: Noel van Halen, (412) 256-0990, 2500
Tue Jul 11 15:48:08 2023
 / (Ud5dfGgug...)
name, phone and budget: Testing person, 081111, 25.9522
Tue Jul 11 15:48:08 2023
 / (zbW9lLGF1...)
name, phone and budget: Leo Welch, (310) 209-7111, 100000

Client: Now, let's rollback!

ProspectMemory: Restoring state to: Tue Jul 11 15:48:08 2023
 / (zbW9lLGF1...)
SalesProspect: My state has been restored to: zbW9lLGF1tAYaDwiw9HwvwZgLNKkIX
New name, phone and budget: Leo Welch, (310) 209-7111, 100000

Client: Once more!

ProspectMemory: Restoring state to: Tue Jul 11 15:48:08 2023
 / (Ud5dfGgug...)
SalesProspect: My state has been restored to: Ud5dfGgugCCVZ8GedRiEHQVQ58ocEq
New name, phone and budget: Testing person, 081111, 25.9522

End of program!
*/
```

#### When To Use

TODO

### 😎 Observer

#### Overview

Real world example:

> A good example would be the job seekers where they subscribe to some job
> posting site and they are notified whenever there is a matching job opportunity.

In plain words:

> Defines a dependency between objects so that whenever an object changes its
> state, all its dependents are notified.

Wikipedia says:

> The observer pattern is a software design pattern in which an object, called
> the subject, maintains a list of its dependents, called observers, and notifies
> them automatically of any state changes, usually by calling one of their
> methods.

#### Programmatic Example

```cpp
/**
 * Investor Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the IBM is also called the
 * Publisher and the Investor is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

#include <iostream>
#include <list>
#include <string>

class Stock;

// Observer interface
class IInvestor {
	public:
		virtual ~IInvestor(){};
		//virtual void Update(const std::string &message_from_subject) = 0;
		virtual void Update(Stock* stock) = 0;
};

// Subject interface
class Stock {
	public:
		virtual ~Stock(){};
		virtual void Attach(IInvestor *observer) = 0;
		virtual void Detach(IInvestor *observer) = 0;
		virtual void Notify() = 0;
		virtual void CreateMessage(std::string msg) = 0;
		virtual double getPrice() const = 0;
		virtual void setPrice(double newPrice) = 0;
};

/**
 * The IBM owns some important state and notifies observers when the state
 * changes.
 */

class IBM : public Stock {
	public:
		virtual ~IBM() {
			std::cout << "Goodbye, I was IBM (Subject / Stock).\n";
		}

		/**
		 * The subscription management methods.
		 */
		void Attach(IInvestor *observer) override {
			list_observer_.push_back(observer);
		}
		void Detach(IInvestor *observer) override {
			list_observer_.remove(observer);
		}
		void Notify() override {
			std::list<IInvestor *>::iterator iterator = list_observer_.begin();
			HowManyObserver();
			while (iterator != list_observer_.end()) {
				//(*iterator)->Update(message_);
				(*iterator)->Update(this);
				++iterator;
			}
		}

		void CreateMessage (std::string message = "Empty") override {
			// Change price
			price += 20;
			this->message_ = message;
			Notify();
		}
		void HowManyObserver() {
			std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
		}

		/**
		 * Usually, the subscription logic is only a fraction of what a Subject can
		 * really do. Subjects commonly hold some important business logic, that
		 * triggers a notification method whenever something important is about to
		 * happen (or after it).
		 */
		void SomeBusinessLogic() {
			this->message_ = "change message message";
			Notify();
			std::cout << "I'm about to do some thing important\n";
		}

		double getPrice() const override {
			return price;
		}

		void setPrice(double newPrice) override {
			this->price = newPrice;
		}


	private:
		std::list<IInvestor *> list_observer_;
		std::string message_;
		double price;
};

class Investor : public IInvestor {
	public:
		Investor(Stock &subject) : subject_(subject) {
			this->subject_.Attach(this);
			std::cout << "Hi, I'm the Investor \"" << ++Investor::static_number_ << "\".\n";
			this->number_ = Investor::static_number_;
		}
		virtual ~Investor() {
			std::cout << "Goodbye, I was the Investor \"" << this->number_ << "\".\n";
		}

		//void Update(const std::string &message_from_subject) override {
		void Update(Stock* stock) override {
			std::cout << "Notified Investor " << this->number_ << " of stock price change to " << stock->getPrice() << std::endl;
			//PrintInfo();
		}
		void RemoveMeFromTheList() {
			subject_.Detach(this);
			std::cout << "Investor \"" << number_ << "\" removed from the list.\n";
		}
		void PrintInfo() {
			std::cout << "Investor \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
		}

	private:
		std::string message_from_subject_;
		Stock &subject_;
		static int static_number_;
		int number_;
};

int Investor::static_number_ = 0;

void ClientCode() {
	Stock *ibm = new IBM;
	ibm->setPrice(50.35);
	Investor *observer1 = new Investor(*ibm);
	Investor *observer2 = new Investor(*ibm);
	Investor *observer3 = new Investor(*ibm);
	Investor *observer4;
	Investor *observer5;

	ibm->CreateMessage("Hello World! :D");
	observer3->RemoveMeFromTheList();

	ibm->CreateMessage("New computer released!");
	observer4 = new Investor(*ibm);

	observer2->RemoveMeFromTheList();
	observer5 = new Investor(*ibm);

	ibm->CreateMessage("My new computer is great! ;)");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete ibm;
}

int main() {
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}


// Output:
/**
Hi, I'm the Investor "1".
Hi, I'm the Investor "2".
Hi, I'm the Investor "3".
There are 3 observers in the list.
Notified Investor 1 of stock price change to 70.35
Notified Investor 2 of stock price change to 70.35
Notified Investor 3 of stock price change to 70.35

Investor "3" removed from the list.
There are 2 observers in the list.
Notified Investor 1 of stock price change to 90.35
Notified Investor 2 of stock price change to 90.35

Hi, I'm the Investor "4".
Investor "2" removed from the list.
Hi, I'm the Investor "5".
There are 3 observers in the list.
Notified Investor 1 of stock price change to 110.35
Notified Investor 4 of stock price change to 110.35
Notified Investor 5 of stock price change to 110.35

Investor "5" removed from the list.
Investor "4" removed from the list.
Investor "1" removed from the list.

Goodbye, I was the Investor "5".
Goodbye, I was the Investor "4".
Goodbye, I was the Investor "3".
Goodbye, I was the Investor "2".
Goodbye, I was the Investor "1".
Goodbye, I was IBM (Subject / Stock).

End of program!
*/
```

#### When To Use

TODO

### 🏃 Visitor

#### Overview

Real world example:

> Consider someone visiting Dubai. They just need a way (i.e. visa) to enter
> Dubai. After arrival, they can come and visit any place in Dubai on their own
> without having to ask for permission or to do some leg work in order to visit
> any place here; just let them know of a place and they can visit it. Visitor
> pattern lets you do just that, it helps you add places to visit so that they can
> visit as much as they can without having to do any legwork.

In plain words:

> Visitor pattern lets you add further operations to objects without having to
> modify them.

Wikipedia says:

> In object-oriented programming and software engineering, the visitor design
> pattern is a way of separating an algorithm from an object structure on which it
> operates. A practical result of this separation is the ability to add new
> operations to existing object structures without modifying those structures. It
> is one way to follow the open/closed principle.

#### Programmatic Example

```cpp
#include <iostream>
#include <array>

/**
 * The IVisitor Interface declares a set of visiting methods that correspond to
 * component classes. The signature of a visiting method allows the visitor to
 * identify the exact class of the component that it's dealing with.
 */
class Employee;

class IVisitor {
	public:
		virtual void Visit(Employee* const element) = 0;
};

/**
 * The Element interface declares an `accept` method that should take the base
 * visitor interface as an argument.
 */
class Element {
	public:
		virtual ~Element() {}
		virtual void Accept(IVisitor* const visitor) = 0;
};

/**
 * Each Concrete Element must implement the `Accept` method in such a way that
 * it calls the visitor's method corresponding to the component's class.
 */
class Employee : public Element {
	protected:
		std::string name_;
		double income_;
		unsigned int vacationDays_;

	public:
		Employee(std::string name, double income, unsigned int vacationDays) : name_(name), income_(income), vacationDays_(vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		/**
		 * Concrete Components may have special methods that don't exist in their base
		 * class or interface. The IVisitor is still able to use these methods since
		 * it's aware of the component's concrete class.
		 */
		std::string GetInfo() const {
			return "Employee info: " + name_ + ", " + std::to_string(income_) + ", " + std::to_string(vacationDays_);
		}

		// Getters and setters
		const std::string name() const { return name_; } 
		void name(const std::string& name) { name_ = name; }

		const double income() const { return income_; } 
		void income(double income) { income_ = income; }

		const unsigned int vacationDays() const { return vacationDays_; } 
		void vacationDays(unsigned int vacationDays) { vacationDays_ = vacationDays; }
		
};

// Three employee types
class Clerk : public Employee {
	public:
		Clerk(std::string name, double income, unsigned int vacationDays) : Employee(name, income, vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		std::string SpecialMethodOfClerk() const {
			return "Clerk";
		}
};

class Director : public Employee {
	public:
		Director(std::string name, double income, unsigned int vacationDays) : Employee(name, income, vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		std::string SpecialMethodOfDirector() const {
			return "Director";
		}
};

class President : public Employee {
	public:
		President(std::string name, double income, unsigned int vacationDays) : Employee(name, income, vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		std::string SpecialMethodOfPresident() const {
			return "President";
		}
};

/**
 * Concrete Visitors implement several versions of the same algorithm, which can
 * work with all concrete component classes.
 *
 * You can experience the biggest benefit of the IVisitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 */
class IncomeVisitor : public IVisitor {
	public:
		void Visit(Employee* const element) override {
			std::cout << "IncomeVisitor providing income increase for " << element->name() << std::endl;
			std::cout << "Prev income: " << element->income() << std::endl;
			// Provide 10 % pay raise
			element->income(element->income() * 1.10);
			std::cout << "New income: " << element->income() << std::endl;
		}
};

class VacationVisitor : public IVisitor {
	public:
		void Visit(Employee* const element) override {
			std::cout << "VacationVisitor providing income increase for " << element->name() << std::endl;
			std::cout << "Prev vacationDays: " << element->vacationDays() << std::endl;
			// Provide 10 % pay raise
			element->vacationDays(element->vacationDays() + 3);
			std::cout << "New vacationDays: " << element->vacationDays() << std::endl;
		}
};

/**
 * The client code can run visitor operations over any set of elements without
 * figuring out their concrete classes. The accept operation directs a call to
 * the appropriate operation in the visitor object.
 */
void ClientCode(std::array<Element* const, 3> components, IVisitor *visitor) {
	// ...
	for (Element* const comp : components) {
		comp->Accept(visitor);
	}
	// ...
}

int main() {
	std::array<Element* const, 3> components = {new Clerk("Jonas", 2000.5, 5), new Director("John", 3000.99, 6), new President("Buster", 4000.0, 8)};

	std::cout << "The client code works with all visitors via the base IVisitor interface:\n";

	IncomeVisitor *visitor1 = new IncomeVisitor;
	ClientCode(components, visitor1);
	std::cout << "\n";

	std::cout << "It allows the same client code to work with different types of visitors:\n";
	VacationVisitor *visitor2 = new VacationVisitor;
	ClientCode(components, visitor2);

	for (Element *comp : components) {
		delete comp;
	}
	delete visitor1;
	delete visitor2;
	std::cout << "\nEnd of program!" << std::endl;

	return 0;
}

// Output:
/**
The client code works with all visitors via the base IVisitor interface:
IncomeVisitor providing income increase for Jonas
Prev income: 2000.5
New income: 2200.55
IncomeVisitor providing income increase for John
Prev income: 3000.99
New income: 3301.09
IncomeVisitor providing income increase for Buster
Prev income: 4000
New income: 4400

It allows the same client code to work with different types of visitors:
VacationVisitor providing income increase for Jonas
Prev vacationDays: 5
New vacationDays: 8
VacationVisitor providing income increase for John
Prev vacationDays: 6
New vacationDays: 9
VacationVisitor providing income increase for Buster
Prev vacationDays: 8
New vacationDays: 11

End of program!
*/
```

#### When To Use

TODO

### 💡 Strategy

#### Overview

Real world example:

> Consider the example of sorting, we implemented bubble sort but the data
> started to grow and bubble sort started getting very slow. In order to tackle
> this we implemented Quick sort. But now although the quick sort algorithm was
> doing better for large datasets, it was very slow for smaller datasets. In order
> to handle this we implemented a strategy where for small datasets, bubble sort
> will be used and for larger, quick sort.

In plain words:

> Strategy pattern allows you to switch the algorithm or strategy based upon the
> situation.

Wikipedia says:

> In computer programming, the strategy pattern (also known as the policy
> pattern) is a behavioural software design pattern that enables an algorithm's
> behavior to be selected at runtime.

#### Programmatic Example

```cpp
#include <iostream>
#include <string_view> // Requires C++ 17

/**
 * The Strategy interface declares operations common to all supported versions
 * of some algorithm.
 *
 * The Context uses this interface to call the algorithm defined by Concrete
 * Strategies.
 */
class Strategy
{
	public:
		virtual ~Strategy() = default;
		virtual std::string doAlgorithm(std::string_view data) const = 0;
};

/**
 * The Context defines the interface of interest to clients.
 */

class Context
{
	/**
	 * @var Strategy The Context maintains a reference to one of the Strategy
	 * objects. The Context does not know the concrete class of a strategy. It
	 * should work with all strategies via the Strategy interface.
	 */
	private:
		std::unique_ptr<Strategy> strategy_;
		/**
		 * Usually, the Context accepts a strategy through the constructor, but also
		 * provides a setter to change it at runtime.
		 */
	public:
		explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy))
	{
	}
		/**
		 * Usually, the Context allows replacing a Strategy object at runtime.
		 */
		void set_strategy(std::unique_ptr<Strategy> &&strategy)
		{
			strategy_ = std::move(strategy);
		}
		/**
		 * The Context delegates some work to the Strategy object instead of
		 * implementing +multiple versions of the algorithm on its own.
		 */
		void doSomeBusinessLogic() const
		{
			if (strategy_) {
				std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
				std::string result = strategy_->doAlgorithm("aecbd");
				std::cout << result << "\n";
			} else {
				std::cout << "Context: Strategy isn't set\n";
			}
		}
};

/**
 * Concrete Strategies implement the algorithm while following the base Strategy
 * interface. The interface makes them interchangeable in the Context.
 */
class ConcreteStrategyA : public Strategy
{
	public:
		std::string doAlgorithm(std::string_view data) const override
		{
			std::string result(data);
			std::sort(std::begin(result), std::end(result));

			return result;
		}
};
class ConcreteStrategyB : public Strategy
{
	std::string doAlgorithm(std::string_view data) const override
	{
		std::string result(data);
		std::sort(std::begin(result), std::end(result), std::greater<>());

		return result;
	}
};
/**
 * The client code picks a concrete strategy and passes it to the context. The
 * client should be aware of the differences between strategies in order to make
 * the right choice.
 */

void clientCode()
{
	Context context(std::make_unique<ConcreteStrategyA>());
	std::cout << "Client: Strategy is set to normal sorting.\n";
	context.doSomeBusinessLogic();
	std::cout << "\n";
	std::cout << "Client: Strategy is set to reverse sorting.\n";
	context.set_strategy(std::make_unique<ConcreteStrategyB>());
	context.doSomeBusinessLogic();
}

int main()
{
	clientCode();
	return 0;
}

// Output:
/**
Client: Strategy is set to normal sorting.
Context: Sorting data using the strategy (not sure how it'll do it)
abcde

Client: Strategy is set to reverse sorting.
Context: Sorting data using the strategy (not sure how it'll do it)
edcba
*/
```

#### When To Use

TODO

### 💢 State

#### Overview

Real world example:

> Imagine you are using some drawing application, you choose the paint brush to
> draw. Now the brush changes its behavior based on the selected color i.e. if you
> have chosen red color it will draw in red, if blue then it will be in blue etc.

In plain words:

> It lets you change the behavior of a class when the state changes.

Wikipedia says:

> The state pattern is a behavioral software design pattern that implements a
> state machine in an object-oriented way. With the state pattern, a state machine
> is implemented by implementing each individual state as a derived class of the
> state pattern interface, and implementing state transitions by invoking methods
> defined by the pattern's superclass. The state pattern can be interpreted as a
> strategy pattern which is able to switch the current strategy through
> invocations of methods defined in the pattern's interface.

#### Programmatic Example

```cpp
#include <iostream>
#include <typeinfo>

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Account object, associated
 * with the State. This backreference can be used by States to transition the
 * Account to another State.
 */
class Account;

class State {
	/**
	 * @var Account
	 */
	protected:
		Account *context_;
		double balance_;
		double interest;
		double lowerLimit;
		double upperLimit;

	public:
		virtual ~State() {
		}

		// Constructor
		State(const double balance) {
			this->balance_ = balance;
		}

		void set_context(Account *context) {
			this->context_ = context;
		}

		const virtual double balance() const {
			return balance_;
		}

		virtual void deposit(const double amount) = 0;
		virtual void withdraw(const double amount) = 0;
		virtual void payInterest() = 0;
		virtual void stateChangeCheck() = 0;
};

/**
 * The Account defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Account.
 */
class Account {
	/**
	 * @var State A reference to the current state of the Account.
	 */
	private:
		State *state_;
		std::string owner_;

	public:
		Account(const std::string owner) : owner_(owner) {
			this->state_ = nullptr;
			std::cout << "New account created! Owner: " << owner_ << std::endl; 
		}
		~Account() {
			delete state_;
		}
		/**
		 * The Account allows changing the State object at runtime.
		 */
		void TransitionTo(State *state) {
			std::cout << "Account: Transition to " << typeid(*state).name() << ".\n";
			if (this->state_ != nullptr)
				delete this->state_;
			this->state_ = state;
			this->state_->set_context(this);
		}

		double getBalance() {
			return state_->balance();
		}

		void deposit(const double amount) {
			this->state_->deposit(amount);

			std::cout << "Deposited: " << amount << std::endl;
			std::cout << "Balance: " << getBalance() << std::endl;
			std::cout << "Status: " << typeid(*this->state_).name() << std::endl;
		}

		void withdraw(const double amount) {
			this->state_->withdraw(amount);

			std::cout << "Withdrew: " << amount << std::endl;
			std::cout << "Balance: " << getBalance() << std::endl;
			std::cout << "Status: " << typeid(*this->state_).name() << std::endl;
		}

		void payInterest() {
			this->state_->payInterest();

			std::cout << "Interest paid: " << std::endl;
			std::cout << "Balance: " << getBalance() << std::endl;
			std::cout << "Status: " << typeid(*this->state_).name() << std::endl;
		}
};

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Account.
 */
class RedState : public State {

	private:
		double serviceFee;

	public:
		RedState(const double balance) : State(balance) {
			// Initiliaze
			interest = 0.0;
			lowerLimit = -100.0;
			upperLimit = 0.0;
			serviceFee = 15.00;
		}

		void deposit(double amount) override {
			balance_ += amount;
			stateChangeCheck();
		}

		void withdraw(const double amount) override {
			//amount = amount - serviceFee;
			std::cout << "No funds available for withdrawal!" << std::endl;
			stateChangeCheck();
		}

		void payInterest() override {
			std::cout << "payInterest()" << std::endl;
			stateChangeCheck();
		}

		void stateChangeCheck() override;

};

class SilverState : public State {
	public:
		SilverState(const double balance) : State(balance) {
			// Initiliaze
			interest = 0.0;
			lowerLimit = 0.0;
			upperLimit = 1000.0;
		}

		void deposit(const double amount) override {
			balance_ += amount;
			stateChangeCheck();
		}

		void withdraw(const double amount) override {
			balance_ -= amount;
			stateChangeCheck();
		}

		void payInterest() override {
			balance_ += interest * balance_;
			stateChangeCheck();
		}

		void stateChangeCheck() override;
};

class GoldState : public State {
	public:
		GoldState(const double balance) : State(balance) {
			// Initiliaze
			interest = 0.05;
			lowerLimit = 1000.0;
			upperLimit = 10000000.0;
		}

		void deposit(const double amount) override {
			balance_ += amount;
			stateChangeCheck();
		}

		void withdraw(const double amount) override {
			balance_ -= amount;
			stateChangeCheck();
		}

		void payInterest() override {
			balance_ += interest * balance_;
			stateChangeCheck();
		}

		void stateChangeCheck() override;

};

void RedState::stateChangeCheck() {
	if (balance_ > upperLimit)
		this->context_->TransitionTo(new SilverState(this->balance_));
}

void SilverState::stateChangeCheck() {
	if (balance_ < lowerLimit)
		this->context_->TransitionTo(new RedState(this->balance_));
	else if (balance_ > upperLimit)
		this->context_->TransitionTo(new GoldState(this->balance_));
}

void GoldState::stateChangeCheck() {
	if (balance_ < 0.0)
		this->context_->TransitionTo(new RedState(this->balance_));
	else if (balance_ < lowerLimit)
		this->context_->TransitionTo(new SilverState(this->balance_));
}

/**
 * The client code.
 */
void ClientCode() {
	Account *context = new Account("Jonas");
	// New accounts are 'Silver' by default
	context->TransitionTo(new SilverState(0.0));

	// Apply financial transactions
	context->deposit(500.0);
	std::cout << "\n";
	context->deposit(300.0);
	std::cout << "\n";
	context->deposit(550.0);
	std::cout << "\n";
	context->payInterest();
	std::cout << "\n";
	context->withdraw(2000.00);
	std::cout << "\n";
	context->withdraw(1100.00);
	std::cout << "\n";

	delete context;
}

int main() {
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}

// Output:
/**
New account created! Owner: Jonas
Account: Transition to 11SilverState.
Deposited: 500
Balance: 500
Status: 11SilverState

Deposited: 300
Balance: 800
Status: 11SilverState

Account: Transition to 9GoldState.
Deposited: 550
Balance: 1350
Status: 9GoldState

Interest paid:
Balance: 1417.5
Status: 9GoldState

Account: Transition to 8RedState.
Withdrew: 2000
Balance: -582.5
Status: 8RedState

No funds available for withdrawal!
Withdrew: 1100
Balance: -582.5
Status: 8RedState

End of program!
*/
```

#### When To Use

TODO

### 📒 Template Method

#### Overview

Real world example:

> Suppose we are getting some house built. The steps for building might look
> like:
>
> - Prepare the base of house
> - Build the walls
> - Add roof
> - Add other floors
>
> The order of these steps could never be changed i.e. you can't build the roof
> before building the walls etc but each of the steps could be modified for
> example walls can be made of wood or polyester or stone.

In plain words:

> Template method defines the skeleton of how a certain algorithm could be
> performed, but defers the implementation of those steps to the children classes.

Wikipedia says:

> In software engineering, the template method pattern is a behavioral design
> pattern that defines the program skeleton of an algorithm in an operation,
> deferring some steps to subclasses. It lets one redefine certain steps of an
> algorithm without changing the algorithm's structure.

#### Programmatic Example

```cpp
#include <iostream>
#include <list>
#include <string>

/**
 * The Abstract Class defines a template method that contains a skeleton of some
 * algorithm, composed of calls to (usually) abstract primitive operations.
 *
 * Concrete subclasses should implement these operations, but leave the template
 * method itself intact.
 */
class DataAccessor {
	/**
	 * The template method defines the skeleton of an algorithm.
	 */
	public:
		void TemplateMethod() {
			this->Connect();
			this->Select();
			this->Hook1();
			this->Process();
			this->Disconnect();
			this->Hook2();
		}
		/**
		 * These operations already have implementations.
		 */
	protected:
		//void Connect() const {
		//	std::cout << "DataAccessor says: I am doing the bulk of the work\n But I let subclasses override some operations...\n";
		//}

		/**
		 * These operations have to be implemented in subclasses.
		 */
		virtual void Connect() const = 0;
		virtual void Select() = 0;
		virtual void Process() = 0;
		virtual void Disconnect() = 0;
		/**
		 * These are "hooks." Subclasses may override them, but it's not mandatory
		 * since the hooks already have default (but empty) implementation. Hooks
		 * provide additional extension points in some crucial places of the
		 * algorithm.
		 */
		virtual void Hook1() const {}
		virtual void Hook2() const {}
};

/**
 * Concrete classes have to implement all abstract operations of the base class.
 * They can also override some operations with a default implementation.
 */
class Categories : public DataAccessor {
	protected:
		std::list<std::string> categories;

		void Connect() const override {
			std::cout << "Categories says: Connected. Initiliazing stuff...\n";
		}

		void Select() override {
			categories.push_back("Red");
            categories.push_back("Green");
            categories.push_back("Blue");
            categories.push_back("Yellow");
            categories.push_back("Purple");
            categories.push_back("White");
            categories.push_back("Black");
		}

		void Hook1() const override {
			std::cout << "Categories says: Overridden Hook1\n";
		}

		void Process() override {
			std::cout << "Processing categories:" << std::endl;
			std::list<std::string>::iterator it = categories.begin();
			while (it != categories.end()) {
				std::cout << "categories: " << (*it) << std::endl;
				++it;
			}
		}

		void Disconnect() override {
			std::cout << "Clearing categories";
			categories.clear();
		}
};
/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
class Products : public DataAccessor {
	protected:
		std::list<std::string> products;

		void Connect() const override {
			std::cout << "Products says: Connected. Initiliazing stuff...\n";
		}

		void Select() override {
            products.push_back("Car");
            products.push_back("Bike");
            products.push_back("Boat");
            products.push_back("Truck");
            products.push_back("Moped");
            products.push_back("Rollerskate");
            products.push_back("Stroller");
		}

		void Hook1() const override {
			std::cout << "Products says: Overridden Hook1\n";
		}

		void Process() override {
			std::cout << "Processing products:" << std::endl;
			std::list<std::string>::iterator it = products.begin();
			while (it != products.end()) {
				std::cout << "product: " << (*it) << std::endl;
				++it;
			}
		}

		void Disconnect() override {
			std::cout << "Clearing products:" << std::endl;
			products.clear();
		}

		void Hook2() const override {
			std::cout << "Products says: Overridden Hook2\n";
		}
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void ClientCode(DataAccessor *class_) {
	// ...
	class_->TemplateMethod();
	// ...
}

int main() {
	std::cout << "Same client code can work with different subclasses:\n\n";
	Categories *concreteClass1 = new Categories;
	ClientCode(concreteClass1);
	std::cout << "\n\n";

	std::cout << "Same client code can work with different subclasses:\n\n";
	Products *concreteClass2 = new Products;
	ClientCode(concreteClass2);

	delete concreteClass1;
	delete concreteClass2;
	
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}

// Output:
/**
Same client code can work with different subclasses:

Categories says: Connected. Initiliazing stuff...
Categories says: Overridden Hook1
Processing categories:
categories: Red
categories: Green
categories: Blue
categories: Yellow
categories: Purple
categories: White
categories: Black
Clearing categories

Same client code can work with different subclasses:

Products says: Connected. Initiliazing stuff...
Products says: Overridden Hook1
Processing products:
product: Car
product: Bike
product: Boat
product: Truck
product: Moped
product: Rollerskate
product: Stroller
Clearing products:
Products says: Overridden Hook2

End of program!
*/
```

#### When To Use

TODO

## 🚦 Wrap Up

And that about wraps it up. I will continue to improve this, so you might want
to watch/star this repository to revisit. Also, I have plans on writing the same
about the architectural patterns, stay tuned for it.

## 👬 Contribution

- Report issues
- Open pull request with improvements
- Spread the word

## Other sources

- https://refactoring.guru/design-patterns/cpp

- https://github.com/Junzhuodu/design-patterns

- https://github.com/JakubVojvoda/design-patterns-cpp

- https://www.dofactory.com/net/facade-design-pattern

- https://github.com/ornfelt/DesignPatterns_C-

## License

All content of this file, unless otherwise noted, is licensed as follows:

- All provided source code examples are covered by the
  [MIT License](https://github.com/idinwoodie/cpp-design-patterns-for-humans/blob/master/LICENSE).
- The C++ badge that appears in the banner image was created by
  [Jeremy Kratz](https://jeremykratz.com/) and is licensed by
  [The Standard C++ Foundation](https://isocpp.org/home/terms-of-use).
- Other content, including images, is released under the
  [Creative Common Attribution 4.0 International License](https://creativecommons.org/licenses/by/4.0/).
