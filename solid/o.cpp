#include <iostream>

using namespace std;

/*
https://www.linkedin.com/pulse/first-5-principles-oop-c-what-so-solid-abdalrahman-hesham

Open Closed Principle

This principle states that your code should generally be open for extension, yet closed
for modification. Which sounds like Gibberish and it will continue to sound so until
demystified with an example, so let's get started.

In the upcoming example, let's say we have a class named "StringAdder" that has a member
function called "AddToText" which takes two strings and appends the second to the first,
this can be seen below.

class TextAdder{
    public:
    std::string AddToText(const std::string& original,
        const std::string& new_string){
            return original + new_string;
        }
};

Now, say we want to add another functionality to the TextAdder, for example adding the
functionality of adding the new string before the original one. Extending the class
through adding another function named "AddBeforeText" is the wrong way to extend the
functionalities of the class, since we had to modify the class.

Following the Open/Closed Principle, this class should be extended making the AddToText
function take a third argument specifying what kind of string addition the user wants
done. This can be done using polymorphism. A base class is passed to the "AddToText"
function, then its own "add" function is called. Let's implement that.
*/

class TextAddType{
    public:
    virtual std::string add(const std::string& original,
        const std::string& new_string) = 0;
	virtual ~TextAddType() = default;
};

class TextAppend : public TextAddType{
    public:
    std::string add(const std::string& original,
        const std::string& new_string) override{
            return original + new_string;
        }
};

class TextPrepend : public TextAddType{
    public:
    std::string add(const std::string& original,
        const std::string& new_string) override{
            return new_string + original;
        }
};

int main()
{
	cout << "Hello World" << endl;

	TextAddType *append = new TextAppend();
	string test = "test";
	string test2 = "wow";

	string res;
	res = append->add(test, test2);
	cout << "Res: " << res << endl;

	TextAddType *prepend = new TextPrepend();
	res = prepend->add(test, test2);
	cout << "Res: " << res << endl;

	delete append;
	delete prepend;

	return 0;
}
