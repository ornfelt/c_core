using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    // OBS! This class uses two static keyword since it is a singleton class. I asked Anton Backe about this and he said it was ok.
    // Singleton class that keeps track of winners
    // Class that keeps track of winners
    public sealed class WinTracker : IWinTracker
    {
        // A dictionary that will contain wins
        private Dictionary<string, string> boardWinsDict;
        // List that will hold values of the winning small boards when a player wins the super board
        private List<String> winningBoards;
        private static WinTracker instance = null;
        private String[] boardNames = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
        private String endResult = null;

        // Public constructor that gets the current instance or creates a new one
        public static WinTracker GetInstance()
        {
            if (instance == null)
            {
                instance = new WinTracker();
            }
            return instance;
        }

        // Private constructor
        private WinTracker()
        {
            // Init values for dictionary
            boardWinsDict = new Dictionary<string, string>();
            winningBoards = new List<String>();

            foreach (String boardString in boardNames)
            {
                boardWinsDict.Add(boardString, string.Empty);
            }
        }

        // Fetch the winningBoards list
        public List<String> GetWinningBoards()
        {
            return winningBoards;
        }

        // Add winning boards for the player that wins the super board
        public void AddWinningBoards(String wins)
        {
            String[] winsSplit = wins.Split(",");
            foreach (string win in winsSplit)
            {
                winningBoards.Add(win.ToUpper());
            }
        }

        // Add new win to dictionary
        public void AddWinToDict(String board, String playerName)
        {
            boardWinsDict[board] = playerName;
        }

        // Public method for fetching the winsDict
        public Dictionary<string, string> GetWinsDict()
        {
            return boardWinsDict;
        }

        // Return true if the board has a winner
        public bool HasWonSmallBoard(String board)
        {
            //return (boardWinsDict[board] == String.Empty ? false : true);
            return (boardWinsDict[board] != String.Empty);
        }

        // Get the end result
        public string GetEndResult()
        {
            return endResult;
        }

        // Set the end result
        public void SetEndResult(String res)
        {
            endResult = res;
        }

        public void ResetTracker()
        {
            instance = null;
        }
    }
}
