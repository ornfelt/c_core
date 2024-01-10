#include <iostream>
#include <cstring>

// g++ .\pointers_trim_double.cpp; .\a.exe

void removeSpaces(char** s) {
	std::cout << "Altering string: " << *s << std::endl;
    int i = 0, j = 0;
    while ((*s)[i]) {
        if ((*s)[i] != ' ') {
            (*s)[j++] = (*s)[i];
        }
        i++;
    }
    (*s)[j] = '\0';
}

void removeSpacesAlternative(char** s) {
	std::cout << "Altering string (alternative function): " << *s << std::endl;
    int writeIndex = 0;
    for (int readIndex = 0; (*s)[readIndex] != '\0'; readIndex++) {
        if ((*s)[readIndex] != ' ') {
            (*s)[writeIndex++] = (*s)[readIndex];
        }
    }
    (*s)[writeIndex] = '\0'; // Null-terminate the modified string
}

int main() {
    char str[] = "Remove spaces from this string";
	str[0] = 'r';
    char* ptr = str;

    removeSpaces(&ptr);
	std::cout << "Changed: " << ptr << std::endl;
	strncpy(str, "  New String ", sizeof(str) - 1);
    str[sizeof(str) - 1] = '\0'; // Ensuring null termination
	removeSpacesAlternative(&ptr);
	std::cout << "Changed: " << ptr << std::endl;
	
	// Dynamic version
	std::cout << "------Testing dynamic string version------" << std::endl;
	char* dynamic_str = new char[strlen(" Remove spaces  from this string ") + 1];
    strcpy(dynamic_str, "Remove spaces from this string");
	ptr = dynamic_str;
	removeSpaces(&ptr);
    std::cout << "Changed: " << ptr << std::endl;
	
	// Deallocate old string and allocate new memory
    delete[] dynamic_str;
    dynamic_str = new char[strlen("  Remove spaces from this string alternative   ") + 1];
    strcpy(dynamic_str, "  Remove spaces  from this string  alternative   ");
	removeSpacesAlternative(&ptr);
    std::cout << "Changed: " << ptr << std::endl;

    return 0;
}