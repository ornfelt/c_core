using System;
using System.Collections.Generic;
using System.Text;

namespace Lab2
{
    // This class represents a Shape object
    class Shape
    {
        // Variables
        private String typeOfShape;
        private int x;
        private int y;
        private int length;
        private int point;

        // Getters and setters
        public string TypeOfShape { get => typeOfShape; set => typeOfShape = value; }
        public int X { get => x; set => x = value; }
        public int Y { get => y; set => y = value; }
        public int Length { get => length; set => length = value; }
        public int Point { get => point; set => point = value; }
    }
}
