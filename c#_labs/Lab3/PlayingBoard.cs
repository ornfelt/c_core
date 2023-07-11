using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    class PlayingBoard : IPlayingBoard
    {
        // Private variables
        private readonly HashSet<String> boardSet;
        private readonly string BoardName;

        // Public constructor that sets the name of the board (either nw, nc, ne, cw etc...)
        public PlayingBoard(String name)
        {
            BoardName = name;
            boardSet = new HashSet<String>();
        }

        // Fetches this board set
        private HashSet<String> GetBoardSet()
        {
            return boardSet;
        }

        // Add new value to board set and return the board set
        public HashSet<String> GetUpdatedBoardSet(String value)
        {
            boardSet.Add(value);
            return GetBoardSet();
        }

        // Get name of this board
        public string GetName()
        {
            return BoardName;
        }
    }
}
