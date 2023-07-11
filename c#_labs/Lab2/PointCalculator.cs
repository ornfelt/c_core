using System;
using System.Collections.Generic;
using System.Text;

namespace Lab2
{
    class PointCalculator
    {
        private double finalScore;
        private int guessX, guessY;

        // Loop every shape in shapesList and calculate points
        public void calcAndPrintPoints(int[] pointCords, List<Shape> shapesList)
        {
            guessX = pointCords[0];
            guessY = pointCords[1];
            foreach (Shape s in shapesList)
            {
                finalScore += calcPoints(s);
            }
            //Console.WriteLine("Final score: " + Math.Round(finalScore, 4));
            Console.WriteLine("Final score: " + (int)Math.Round(finalScore, 4));
        }

        private double calcPoints(Shape shape)
        {
            // Set score to 0 initially 
            double score = 0.0;
            int shapeLength = shape.Length;
            int shapeX = shape.X;
            int shapeY = shape.Y;
            int shapePoints = shape.Point;

            if (shape.TypeOfShape.Equals("circle"))
            {
                double rad = (Convert.ToDouble(shapeLength) / (Math.PI * 2));
                //Console.WriteLine("Rad: " + rad);
                // Base score is 2 for circle
                score = 2.0;
                // Calculate area of circle
                double area = Math.PI * rad * rad;
                //area = (shapeLength * shapeLength) / (4 * Math.PI);
                //Console.WriteLine("area: " + area);

                if (isInsideCircle(shapeX, shapeY, rad, guessX, guessY))
                {
                    // Calculate points
                    score = (score * shapePoints) / area;
                    //Console.WriteLine("Inside circle. Score: " + score);
                } else
                {
                    score = -0.25 * ((score * shapePoints) / area);
                    //Console.WriteLine("Not inside circle. Score: " + score);
                }
            }else if (shape.TypeOfShape.Equals("square"))
            {
                // Base score is 1 for square
                score = 1.0;
                // Calculate area of square
                double area = (shapeLength / 4) * (shapeLength / 4);

                // Call function for checking if point is in square
                //if (FindPoint(shapeX, shapeY, shapeX+shapeLength, shapeY+shapeLength, guessX, guessY))
                double bottomLeftX, bottomLeftY, topRightX, topRightY;
                // Calculate half the width / height of the square
                double halfSide = Convert.ToDouble(shapeLength) / 8;
                bottomLeftX = shapeX - halfSide;
                bottomLeftY = shapeY - halfSide;
                topRightX = shapeX + halfSide;
                topRightY = shapeY + halfSide;
                // Print bottom-left and top-right coordinates for the square
                //Console.WriteLine("x1, y1, x2, y2: " + bottomLeftX + ", " + bottomLeftY + ", " + topRightX + ", " + topRightY);

                if (isInsideSquare(bottomLeftX, bottomLeftY, topRightX, topRightY, guessX, guessY))
                {
                    score = (score * shapePoints) / area;
                    //Console.WriteLine("Inside square. Score: " + score);
                } else
                {
                    score = -0.25 * ((score * shapePoints) / area);
                    //Console.WriteLine("Not inside square. Score: " + score);
                }
            }
            else
            {
                // This should never happen
                Console.WriteLine("Shape not recognized...");
            }

            return score;
        }

        // Bool that returns true if the point (x,y) is inside the square
        private bool isInsideSquare(double x1, double y1, double x2, double y2, int x, int y)
        {
            return (x > x1 && x < x2 && y > y1 && y < y2);
        }

        // Bool that returns true if the point (x,y) is inside the circle
        private bool isInsideCircle(int circle_x, int circle_y, double rad, int x, int y)
        {
            // Return true / false by comparing the distance between given point and radius of circle 
            //Console.WriteLine("Circle calculation: " + ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y)) + " <= " + rad * rad);
            return (((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y)) <= rad * rad);
        }
    }
}
