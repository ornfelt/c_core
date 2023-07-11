using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    class RandomPlaysGenerator
    {
        private String[] boardNames = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
        private List<String> superBoardNames = new List<String>();
        private Random rnd = new Random();

        public String GetRandomPlays()
        {
            List<String> randomList = new List<String>();
            InitBoardNames();
            int r;
            int superBoardNamesCount = superBoardNames.Count;
            for (int i = 0; i < superBoardNamesCount; i++)
            {
                r = rnd.Next(superBoardNames.Count);
                randomList.Add(superBoardNames[r]);
                superBoardNames.RemoveAt(r);
            }
            //randomList.ForEach(p => Console.WriteLine(p));

            return string.Join(",", randomList);
        }

        // Get random plays but only play 1 board at a time
        public String GetRandomPlaysSameBoard()
        {
            List<String> randomList = new List<String>();
            int r, r2;
            List<String> randBoardNames = new List<String>{ "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
            for (int i = 0; i < boardNames.Length; i++)
            {
                List<String> tempBoardNames = new List<String>{ "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
                r = rnd.Next(randBoardNames.Count);

                for (int j = 0; j < boardNames.Length; j++)
                {
                    r2 = rnd.Next(tempBoardNames.Count);
                    //Console.WriteLine("Added random ele: " + randBoardNames[r] + "." + tempBoardNames[r2]);
                    randomList.Add(randBoardNames[r] + "." + tempBoardNames[r2]);
                    tempBoardNames.RemoveAt(r2);
                }
                randBoardNames.RemoveAt(r);
            }
            //randomList.ForEach(p => Console.WriteLine(p));

            return string.Join(",", randomList);
        }


        // Add values to superBoardNames, like this:
        // boardNames[0] = "NW.NW"
        // boardNames[1] = "NW.NC"
        // boardNames[2] = "NW.NE"
        private void InitBoardNames()
        {
            for (int i = 0; i < boardNames.Length; i++)
            {
                for (int j = 0; j < boardNames.Length; j++)
                {
                    superBoardNames.Add(boardNames[i] + "." + boardNames[j]);
                }
            }

            var superBoardPrint = string.Join(", ", superBoardNames);
            //Console.WriteLine(superBoardPrint);
        }
    }
}
