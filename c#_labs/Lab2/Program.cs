using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab2
{
    // @author: Jonas Örnfelt
    class Program
    {
        static void Main(string[] args)
        {
            String point = "";
            String shapes = "";

            if (args.Length == 0)
            {
                Console.WriteLine("No input from argument. Using standard inputs:");
                // Use original inputs from assignment
                point = "(  1,  0)";
                shapes = "SHAPE ,X,Y,LENGTH ,POINTS;CIRCLE ,3,1,13,100;CIRCLE ,1,-1,15,200; SQUARE\n, -1 ,0 ,20 ,300; SQUARE , -3 ,2 ,8 ,400;";
                //shapes = "POINTS ,X,Y,LENGTH , SHAPE ;300, -1 ,0 ,20 ,SQUARE;";

                // Other example inputs
                //String point = "(  3,  100)";
                //String point = "(  30,  1)";
                // Modified values input (circles have same length)
                //String shapes = "SHAPE ,X,Y,LENGTH ,POINTS;CIRCLE ,3,1,15,100;CIRCLE ,1,-1,15,200; SQUARE\n, -1 ,0 ,20 ,300; SQUARE , -3 ,2 ,8 ,400;";
                // Modified positions input (x swaps place with y)
                //String shapes = "SHAPE ,Y,LENGTH ,X,POINTS;CIRCLE ,1,13,3,100;CIRCLE ,-1,15,1,200; SQUARE, 0 ,20 ,-1 ,300; SQUARE , 2 ,8 ,-3 ,400;";
            } else if (args.Length == 1)
            {
                Console.WriteLine("Only one input string provided. Setting other input to standard input:");
                if (args[0].ToLower().Contains("shape") || args[0].ToLower().Contains("points"))
                {
                    shapes = args[0];
                    point = "(  1,  0)";
                } else
                {
                    point = args[0];
                    shapes = "SHAPE ,X,Y,LENGTH ,POINTS;CIRCLE ,3,1,13,100;CIRCLE ,1,-1,15,200; SQUARE\n, -1 ,0 ,20 ,300; SQUARE , -3 ,2 ,8 ,400;";
                }
            } else if (args.Length == 2)
            {
                // The user input might be in the wrong order (shapeListInput might be first),
                // so we first divide the inputs into the right variables
                if (args[0].ToLower().Contains("shape") || args[0].ToLower().Contains("points"))
                {
                    shapes = args[0];
                    point = args[1];
                } else
                {
                    point = args[0];
                    shapes = args[1];
                }
            } else
            {
                Console.WriteLine("Too many input arguments... Please try again.");
            }

            // With the input provided, start the program
            PointApplication pointApplication = new PointApplication();
            pointApplication.StartApplication(point, shapes);
        }
    }
}
