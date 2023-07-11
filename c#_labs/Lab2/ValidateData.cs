using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Lab2
{
    class ValidateData
    {

        // Validate the input of point coordinates
        public bool pointInputIsValid(String pointInput)
        {
            pointInput = pointInput.ToLower();
            if (!pointInput.Contains(","))
            {
                Console.WriteLine("Please enter point coordinates with the following format (x,y)");
                return false;
            }
            pointInput = pointInput.Replace("(", "").Replace(")", "");
            String[] pointSplit = pointInput.Split(",");
            int pointX;
            int pointY;
            if (!int.TryParse(pointSplit[0], out pointX) || !int.TryParse(pointSplit[1], out pointY)){
                // We can also use regex to only fetch digits, valid characters etc.
                Console.WriteLine("Point coordinates must be integers");
                return false;
            }
            return true;
        }

        // Check the input of shapes
        public bool shapesInputIsValid(String shapesInput)
        {
            shapesInput = shapesInput.ToLower();
            shapesInput = String.Concat(shapesInput.Where(c => !Char.IsWhiteSpace(c)));
            shapesInput = shapesInput.Replace(";", ",");
            if (!shapesInput.Contains(",")) {
                Console.WriteLine("Please enter shapes with comma (,) as separator");
                return false;
            } else if (!shapesInput.Contains("shape") || !shapesInput.Contains("x") || !shapesInput.Contains("y") || 
                !shapesInput.Contains("length") || !shapesInput.Contains("points"))
            {
                Console.WriteLine("Shapes input doesn't contain columns: shape, x, y, length, points. Try again!");
                return false;
            }

            String[] shapesSplit = shapesInput.Split(",");
            if (shapesSplit.Length <= 9)
            {
                Console.WriteLine("Shapes input doesn't contain enough information. Try again!");
                return false;
            } else if ((shapesSplit.Length-1) % 5 != 0)
            {
                Console.WriteLine("Shapes input is missing column values. Try again!");
                return false;
            }
            return true;
        }
    }
}
