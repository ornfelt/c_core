using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    class ResultVisualizer : IResultVisualizer
    {
        private static ResultVisualizer instance = null;
        List<String> finalValidPlays = new List<String>();

        private String[] boardNames = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
        //private HashSet<String> superBoardNames = new HashSet<String>();
        private List<String> superBoardNames = new List<String>();
        Dictionary<string, Tuple<int, int>> boardPositions = new Dictionary<string, Tuple<int, int>>();

        Dictionary<Tuple<int, int>, int> boardMatrix = new Dictionary<Tuple<int, int>, int>();
        // Dictionary of boardMatrix dicts...
        Dictionary<Tuple<int, int>, Dictionary<Tuple<int, int>, int>> superBoardMatrix = new Dictionary<Tuple<int, int>, Dictionary<Tuple<int, int>, int>>();

        // New for InitSuperBoardPositionsArr
        Dictionary<string, Tuple<int, int, int, int>> superBoardsDict = new Dictionary<string, Tuple<int, int, int, int>>();

        // Public constructor that gets the current instance or creates a new one
        public static ResultVisualizer GetInstance()
        {
            if (instance == null)
            {
                instance = new ResultVisualizer();
            }
            return instance;
        }
        public void VisualizePlays(List<String> finalValidPlays, Boolean HasDepthOne)
        {
            // Print input values
            this.finalValidPlays = finalValidPlays;
            //this.finalValidPlays.ForEach(p => Console.WriteLine(p));
            Console.WriteLine();

            if (HasDepthOne)
                DepthOnePrint();
            else
            {
                // Automatically fills 3x3 matrix with 0's
                //int[,] playsMatrix = new int[3,3];
                //playsMatrix[0, 0] = 1;
                //playsMatrix[0, 1] = 2;
                //Print2DArray(playsMatrix);

                //InitBoardNames();
                InitBoardPositions();
                //InitSuperBoardPositions();

                InitBoardNamesV2();
                // 3D array (array of 2D arrays)
                //int[,,] superPlaysMatrix = new int[3, 3, 9];
                //Print3DArray(superPlaysMatrix);

                // 4D array
                int[,,,] superPlaysMatrix = new int[3, 3, 3, 3];
                //Print4DArray(superPlaysMatrix);
                InitSuperBoardPositionsArr(superPlaysMatrix);
                FinalPrint(superPlaysMatrix);
            }
        }

        private void DepthOnePrint()
        {
            //Console.WriteLine("DepthOnePrint...");
        }


        // Add tuple indexes to each board name, like this:
        // NW : 0,0
        // NC : 0,1
        // NE : 0,2
        private void InitBoardPositions()
        {
            int posCountOne = 0;
            int posCountTwo = 0;
            foreach (string boardName in boardNames)
            {
                boardPositions.Add(boardName, new Tuple<int, int>(posCountOne,posCountTwo));
                posCountTwo++;
                if (posCountTwo % 3 == 0)
                {
                    posCountTwo = 0;
                    posCountOne++;
                }
            }

            // Use this for printing the values in dictionary
            //foreach (KeyValuePair<string, Tuple<int, int>> kvp in boardPositions)
            //{
            //    Console.WriteLine(string.Format("Key = {0}, Value = {1}", kvp.Key, kvp.Value));
            //}
        }

        private void InitSuperBoardPositions()
        {
            // TODO: Redo implementation with dicts?
            //Dictionary<Tuple<int, int>, int> boardMatrix = new Dictionary<Tuple<int, int>, int>();
            //Dictionary<Tuple<int, int>, Dictionary<Tuple<int, int>, int>> superBoardMatrix = new Dictionary<Tuple<int, int>, Dictionary<Tuple<int, int>, int>>();
        }

        private void InitSuperBoardPositionsArr(int[,,,] matrix)
        {
            List<Tuple<int, int, int, int>> matrixIndexes = new List<Tuple<int, int, int, int>>();

            for (int w = 0; w < matrix.GetLength(0); w++) {
                for (int x = 0; x < matrix.GetLength(1); x++)
                {
                    for (int y = 0; y < matrix.GetLength(2); y++)
                    {
                        for (int z = 0; z < matrix.GetLength(3); z++)
                        {
                            //if (z == 2)
                            //    //Console.Write(getMatrixVal(matrix[w,x,y,z]) + "\t" + "\t");
                            //    Console.Write(w + "," + x + "," + y + "," + z + "\t" + "\t");
                            //else
                            //    //Console.Write(getMatrixVal(matrix[w,x,y,z]) + "\t");
                            //    Console.Write(w + "," + x + "," + y + "," + z + "\t");

                            matrixIndexes.Add(new Tuple<int, int, int, int>(w, x, y, z));
                        }
                    }
                    //Console.WriteLine();
                }
                //Console.WriteLine();
            }

            //matrixIndexes.ForEach(p => Console.WriteLine(p));
            for (int i = 0; i < matrixIndexes.Count; i++)
            {
                superBoardsDict.Add(superBoardNames[i], matrixIndexes[i]);
            }

            // Use this for printing the values in dictionary
            //foreach (KeyValuePair<string, Tuple<int, int, int, int>> kvp in superBoardsDict)
            //{
            //    Console.WriteLine(string.Format("Key = {0}, Value = {1}", kvp.Key, kvp.Value));
            //}
        }

        private void FinalPrint(int[,,,] matrix)
        {
            // Set new values:
            for (int i = 0; i < finalValidPlays.Count; i++)
            {
                Tuple<int, int, int, int> playIdx = superBoardsDict[finalValidPlays[i].Trim().Replace("\n", "").Replace("\r", "")];
                //Console.WriteLine("Adding new play: " + i + " - " + finalValidPlays[i] + ", tuple: " + playIdx);
                if (i % 2 == 0)
                    matrix[playIdx.Item1, playIdx.Item2, playIdx.Item3, playIdx.Item4] = 1;
                else
                    matrix[playIdx.Item1, playIdx.Item2, playIdx.Item3, playIdx.Item4] = 2;

                //Console.WriteLine("matrix updated to: " + matrix[playIdx.Item1, playIdx.Item2, playIdx.Item3, playIdx.Item4]);
            }

            for (int w = 0; w < matrix.GetLength(0); w++) {
                for (int x = 0; x < matrix.GetLength(1); x++)
                {
                    for (int y = 0; y < matrix.GetLength(2); y++)
                    {
                        for (int z = 0; z < matrix.GetLength(3); z++)
                        {
                            if (z == 2)
                                Console.Write(getMatrixVal(matrix[w,x,y,z]) + "\t" + "\t");
                            else
                                Console.Write(getMatrixVal(matrix[w,x,y,z]) + "\t");
                        }
                        //Console.WriteLine();
                    }
                    Console.WriteLine();
                }
                Console.WriteLine();
            }
        }

        private String getMatrixVal(int matrixVal)
        {
            if (matrixVal == 1) return "X";
            else if (matrixVal == 2) return "O";
            //else return " ";
            else return "|";
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
            Console.WriteLine(superBoardPrint);
        }

        private void InitBoardNamesV2()
        {
            String[] boardNamesNorth = { "nw", "nc", "ne" };
            String[] boardNamesCenter = { "cw", "cc", "ce" };
            String[] boardNamesSouth = { "sw", "sc", "se" };

            // UGLY AF
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesNorth[i] + "." + boardNamesNorth[j]);
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesNorth[i] + "." + boardNamesCenter[j]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesNorth[i] + "." + boardNamesSouth[j]);
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesCenter[i] + "." + boardNamesNorth[j]);
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesCenter[i] + "." + boardNamesCenter[j]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesCenter[i] + "." + boardNamesSouth[j]);
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesSouth[i] + "." + boardNamesNorth[j]);
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesSouth[i] + "." + boardNamesCenter[j]);
                }
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    superBoardNames.Add(boardNamesSouth[i] + "." + boardNamesSouth[j]);
                }
            }

            //var superBoardPrint = string.Join(", ", superBoardNames);
            //Console.WriteLine(superBoardPrint);
        }

        // ---------------------------------------------------------------------------
        // ---------------------------------------------------------------------------
        // ---------------------------------------------------------------------------

        // Print each value of 4DArray, separated by tab
        private static void Print4DArray(int[,,,] matrix)
        {
            matrix[1, 0, 0, 0] = 1;
            for (int w = 0; w < matrix.GetLength(0); w++) {
                for (int x = 0; x < matrix.GetLength(1); x++)
                {
                    for (int y = 0; y < matrix.GetLength(2); y++)
                    {
                        for (int z = 0; z < matrix.GetLength(3); z++)
                        {
                            //Console.Write(matrix[w, x, y, z] + "\t");
                            if (z == 2)
                                //Console.Write(w + "," + x + "," + y + "," + z + "\t" + "\t");
                                Console.Write(matrix[w, x, y, z] + "\t" + "\t");
                            else
                                //Console.Write(w + "," + x + "," + y + "," + z + "\t");
                                Console.Write(matrix[w, x, y, z] + "\t");
                        }
                        //Console.WriteLine();
                    }
                    Console.WriteLine();
                }
                Console.WriteLine();
            }
        }

        // Print each value of 3DArray, separated by tab
        private static void Print3DArray(int[,,] matrix)
        {
            for (int x = 0; x < matrix.GetLength(0); x++) {
                for (int y = 0; y < matrix.GetLength(1); y++) {
                    for (int z = 0; z < matrix.GetLength(2); z++) {
                        Console.Write(matrix[x,y,z] + "\t");
                    }
                    Console.WriteLine();
                }
                Console.WriteLine();
            }
        }

        // Print each value of 2DArray, separated by tab
        //private static void Print2DArray<T>(T[,] matrix)
        private static void Print2DArray(int[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                for (int j = 0; j < matrix.GetLength(1); j++)
                {
                    if (matrix[i,j] == 1)
                        Console.Write("X" + "\t");
                    else if (matrix[i,j] == 2)
                        Console.Write("O" + "\t");
                    else
                        Console.Write(" " + "\t");
                }
                Console.WriteLine();
            }
        }
    }
}
