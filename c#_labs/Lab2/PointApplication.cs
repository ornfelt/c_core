using System;
using System.Collections.Generic;
using System.Text;

namespace Lab2
{
    // This class uses the Facade design pattern to organize the application
    // @author: Jonas Örnfelt
    class PointApplication
    {
        public void StartApplication(String pointInput, String shapesListInput)
        {
            // Start with validating the input data
            ValidateData vd = new ValidateData();
            if (vd.pointInputIsValid(pointInput) && vd.shapesInputIsValid(shapesListInput)){
                // Use the HandleInput class that will return a list of shapes and point coordinates
                // The list and coordinates can be used for calculating points
                HandleInput handleInput = new HandleInput();
                int[] pointCords = handleInput.extractPointInputs(pointInput);
                List<Shape> shapesList = handleInput.extractShapesList(shapesListInput);
                // Calculate points via PointCalculator class
                PointCalculator pointCalculator = new PointCalculator();
                pointCalculator.calcAndPrintPoints(pointCords, shapesList);
            }
        }
    }
}
