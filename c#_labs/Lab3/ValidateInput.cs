using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Lab3
{
    // This class validates the user input by doing the following:
    // Check if input contains dots and comma's
    // Check if validBoardCharacters contain each character in string input 
    // i.e. the letters can't be anything else then the valid playing letters from validBoardCharacters
    class ValidateInput
    {
        private String validBoardCharacters = "N" + "C" + "S" + "W" + "E";
        private String input;

        // Validate the input
        public bool InputIsValid(String userInput)
        {
            input = userInput;
            // Check if input contains the necessary seperator
            if (!input.Contains(","))
            {
                Console.WriteLine("Input doesn't contain the seperator ','...");
                return false;
            }

            if (GetDepth() > 3)
            {
                Console.WriteLine("Input contains an invalid depth...");
                return false;
            }
            else if (GetDepth() == 1) return true;
            
            // Clean the input
            input = String.Concat(input.Where(c => !Char.IsWhiteSpace(c)));
            input = input.Replace("\n", "").Replace("\r", "");
            // Check if the individual plays contains enough characters
            if (!PlaysContainEnoughChars())
            {
                return false;
            }
            // Remove dots and commas
            input = input.Replace(".", "").Replace(",", "");
            // Loop through every char and check that validBoardCharacters contain them
            foreach (char c in input)
            {
                if (!validBoardCharacters.Contains(c))
                {
                    Console.WriteLine("Invalid char: " + c);
                    Console.WriteLine("Input doesn't contain valid board characters...");
                    return false;
                }
            }
            return true;
        }

        // Return the depth amount
        public int GetDepth()
        {
            int DotCount = input.Count(c => c == '.');
            int CommaCount = input.Count(c => c == ',');
            //Console.WriteLine("Count of dots: " + DotCount);
            //Console.WriteLine("Count of commas: " + CommaCount);
            // Clarifying examples:
            // NW.CC.CC, NE.CC.CC, NE.CC.CE (DotCount = 6, CommaCount = 2)
            // NW.CC, NE.CC.CC, NE.CC, NW.SE (DotCount = 5, CommaCount = 3)
            // NW.CC, NE.CC, NE.CC, NW.SE (DotCount = 4, CommaCount = 3)
            if (!input.Contains(".")) return 1;
            // This means that the depth is 
            else if ((DotCount - CommaCount) > 1) return 3;
            else return 2;
        }
        
        // Return bool of "does individual plays contains enough characters?"
        private bool PlaysContainEnoughChars()
        {
            String[] inputSplit = input.Split(",");
            foreach (String play in inputSplit)
            {
                String[] playSplit = play.Split(".");
                if (playSplit.Length < 2) return false;
                if (playSplit[0].Length < 2 || playSplit[1].Length < 2)
                {
                    Console.WriteLine("Input doesn't contain enough characters on this play: " + playSplit[0] + "." + playSplit[1]);
                    return false;
                } else if (playSplit[0].Length > 2 || playSplit[1].Length > 2)
                {
                    Console.WriteLine("Input contains too many characters on this play: " + playSplit[0] + "." + playSplit[1]);
                    return false;
                }
            }
            return true;
        }
    }
}
