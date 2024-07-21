using System;

// https://www.geeksforgeeks.org/c-sharp-literals/?ref=lbp

// Note: By default, every floating-point literal is of double type and hence
// we can’t assign directly to float variable. But we can specify
// floating-point literal as float type by suffixed with f or F. We can specify
// explicitly floating-point literal as the double type by suffixed with d or
// D, of course, this convention is not required.
// 
// Character Literals: For character data types we can specify literals in 3 ways: 
// 
// Single quote: We can specify literal to char data type as single 
// character within single quote.
// char ch = 'a';

// Unicode Representation: We can specify char literals in Unicode representation ‘\uxxxx’. 
// Here xxxx represents 4 hexadecimal numbers.

// char ch = '\u0061';// Here /u0061 represent a.

// Escape Sequence: Every escape character can be specified as char literals.

// char ch = '\n';

class Test {
    public static void Main(String[] args)
    {
        // decimal-form literal
        int a = 101;

        // Hexa-decimal form literal
        int c = 0xFace;

        // binary-form literal
        int x = 0b101;

        Console.WriteLine(a);
        Console.WriteLine(c);
        Console.WriteLine(x);

        // decimal-form literal
        double da = 101.230;

        // It also acts as decimal literal
        double db = 0123.222;

        Console.WriteLine(da);
        Console.WriteLine(db);

        // character literal within single quote
        char ch = 'a';

        // Unicode representation
        char uc = '\u0061';

        Console.WriteLine(ch);
        Console.WriteLine(uc);

        // Escape character literal
        Console.WriteLine("Hello\n\nGeeks\t!");

        String s = "Hello Geeks!";
        String s2 = @"Hello 
            fellow
            Geeks!";

        Console.WriteLine(s);
        Console.WriteLine(s2);
    }
}
