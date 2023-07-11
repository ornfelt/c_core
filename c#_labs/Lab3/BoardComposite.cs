using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    // Class that uses the composite design pattern
    class BoardComposite : IPlayingBoard
    {
        // Dictionary of different playingBoards that can be used to add new plays to the correct "small board"
        private Dictionary<string, IPlayingBoard> playingBoards = new Dictionary<string, IPlayingBoard>();
        private readonly string name;

        // Public constructor
        public BoardComposite(String name)
        {
            // The name of the composite will simply be the same as the player name
            this.name = name;
        }

        // Add new playing board to set of playingBoards
        public void AddPlayingBoard(IPlayingBoard playingBoard)
        {
            playingBoards.Add(playingBoard.GetName(), playingBoard);
        }

        // Add value to the correct board and return it
        public HashSet<String> GetUpdatedBoardSet(String value)
        {
            // If depth is 1, then just use 1 board
            if (!value.Contains(".")) return playingBoards["nw"].GetUpdatedBoardSet(value);
            String[] newPlaySplit = value.Split(".");
            String boardPos = newPlaySplit[0];
            String boardPlay = newPlaySplit[1];

            // Add value to the correct board
            return playingBoards[boardPos].GetUpdatedBoardSet(boardPlay);
        }

        // Get name
        public string GetName()
        {
            return name;
        }
    }
}
