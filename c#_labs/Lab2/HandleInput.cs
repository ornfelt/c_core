using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Lab2
{
    class HandleInput
    {
        // Private variables
        private List<Shape> shapesList = new List<Shape>();
        private int pointInputX;
        private int pointInputY;
        // Create lists that will store the csv values
        private List<String> listShape = new List<string>();
        private List<String> listX = new List<string>();
        private List<String> listY = new List<string>();
        private List<String> listLength = new List<string>();
        private List<String> listPoint = new List<string>();

        // Extract an array of x,y based on the pointsInput
        public int[] extractPointInputs(String point)
        {
            point = String.Concat(point.Where(c => !Char.IsWhiteSpace(c)));
            Console.WriteLine("Point input:" + point);
            point = point.Replace("(", "").Replace(")", "");
            pointInputX = Int32.Parse(point.Split(",")[0]);
            pointInputY = Int32.Parse(point.Split(",")[1]);
            //Console.WriteLine("pointX: " + pointInputX + ", pointY: " + pointInputY);
            return new int[] { pointInputX, pointInputY };
        }

        // Extract a list of shapes based on the shapesInput
        public List<Shape> extractShapesList(String shapes)
        {
            shapes = String.Concat(shapes.Where(c => !Char.IsWhiteSpace(c)));
            shapes = shapes.Replace(";", ",");
            // Split the csv string based on comma
            string[] listValues = shapes.Split(',');

            // Index points that stores the order of the columns
            int shapeIndex = 0;
            int xIndex = 0;
            int yIndex = 0;
            int lengthIndex = 0;
            int pointIndex = 0;

            for (int i = 0; i < 5; i++)
            {
                string value = listValues[i].ToLower();
                switch (value)
                {
                    case "shape":
                        shapeIndex = i;
                        //Console.WriteLine("shape: " + i);
                        break;
                    case "x":
                        xIndex = i;
                        //Console.WriteLine("x: " + i);
                        break;
                    case "y":
                        yIndex = i;
                        //Console.WriteLine("y: " + i);
                        break;
                    case "length":
                        lengthIndex = i;
                        //Console.WriteLine("length: " + i);
                        break;
                    case "points":
                        pointIndex = i;
                        //Console.WriteLine("point: " + i);
                        break;
                }
            }

            // Variables for looping the listValues
            int amountOfCols = 5;
            int counter = amountOfCols;
            int valueLap = 1;
            // This is the pattern for the columns
            // 0, 1, 2, 3, 4
            // 5, 6, 7, 8, 9
            // 10, 11, 12, 13, 14
            // ...

            // Loop string values and place values in the correct lists
            while (counter <= listValues.Length-1)
            {
                string value = listValues[counter].ToLower();
                if (value != String.Empty) {
                    // Add values to the correct lists
                    if (counter == shapeIndex + amountOfCols * valueLap)
                    {
                        listShape.Add(value);
                    } else if (counter == xIndex + amountOfCols * valueLap)
                    {
                        listX.Add(value);
                    } else if (counter == yIndex + amountOfCols * valueLap)
                    {
                        listY.Add(value);
                    } else if (counter == lengthIndex + amountOfCols * valueLap)
                    {
                        listLength.Add(value);
                    } else if (counter == pointIndex + amountOfCols * valueLap)
                    {
                        listPoint.Add(value);
                    } else
                    {
                        // This should never happen
                        Console.WriteLine("Error when extracing values...");
                    }
                }

                counter++;
                // Check if valueLap needs to be increased
                if (counter == amountOfCols * (valueLap + 1)) valueLap++;
            }

            Console.WriteLine("Shapes input: " + shapes + "\n");
            //printExtractedValues();

            // Add the extracted values to a shape list
            for (int i = 0; i < listShape.Count(); i++)
            {
                // Create new temporary shape object that will be added to shapesList
                Shape shape = new Shape();
                shape.TypeOfShape = listShape[i];
                // Convert strings to ints
                shape.X = Int32.Parse(listX[i]);
                shape.Y = Int32.Parse(listY[i]);
                shape.Length = Int32.Parse(listLength[i]);
                shape.Point = Int32.Parse(listPoint[i]);
                // Object to string method
                //Console.WriteLine("Shape: " + shape.TypeOfShape + ", x: " + shape.X + ", y: " + shape.Y + 
                    //", length: " + shape.Length + ", point: " + shape.Point);
                shapesList.Add(shape);
            }
            return shapesList;
        }

        /* Print the extracted values: */ 
        private void printExtractedValues()
        {
            Console.WriteLine("Shapes:");
            foreach (string s in listShape)
            {
                Console.WriteLine(s);
            }

            Console.WriteLine("\nx:");
            foreach (string s in listX)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("\ny:");
            foreach (string s in listY)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("\nlengths:");
            foreach (string s in listLength)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("\npoints:");
            foreach (string s in listPoint)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("");
        }
    }
}
