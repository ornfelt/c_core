using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Lab3
{
    class WinChecker : IWinChecker
    {
        // Assignment to WinTracker can only occur as part of the declaration or in a constructor in the same class
        private readonly IWinTracker winTracker;

        // Constructor
        public WinChecker(IWinTracker winTracker)
        {
            this.winTracker = winTracker;
        }

        // Check if the player has won the super board (won everything)
        public bool HasWonSuperBoard(String playerName)
        {
            Dictionary<string, string> boardWinsDict = winTracker.GetWinsDict();
            // If player name appears three times or more in the sub board win dictionary, check if the super game is won
            if (boardWinsDict.Values.Count(x => x.Equals(playerName)) > 2)
            {
                var playerWins = boardWinsDict.Where(x => x.Value == playerName).Select(x => x.Key);
                var playerWinsHashSet = new HashSet<String>(boardWinsDict.Where(x => x.Value == playerName).Select(x => x.Key));
                return HasWon(playerWinsHashSet, true);
            }
            return false;
        }

        // Check if player has won board using hashset since it enables fast lookups
        // This function will work for checking small boards, and also the super board
        public bool HasWon(HashSet<String> board, bool isSuper)
        {
            // Guard clause
            if (board == null) throw new ArgumentNullException(nameof(board));

            // Check top horizontal row
            if (board.Contains("nw") && board.Contains("nc") && board.Contains("ne"))
            {
                if (isSuper) winTracker.AddWinningBoards("nw,nc,ne");
                return true;
            }
            // Check south horizontal row
            else if (board.Contains("sw") && board.Contains("sc") && board.Contains("se"))
            {
                if (isSuper) winTracker.AddWinningBoards("sw,sc,se");
                return true;
            }
            // Check center horizontal row
            else if (board.Contains("cw") && board.Contains("cc") && board.Contains("ce"))
            {
                if (isSuper) winTracker.AddWinningBoards("cw,cc,ce");
                return true;
            }
            // Check first vertical column
            else if (board.Contains("nw") && board.Contains("cw") && board.Contains("sw"))
            {
                if (isSuper) winTracker.AddWinningBoards("nw,cw,sw");
                return true;
            }
            // Check second vertical column
            else if (board.Contains("cc") && board.Contains("nc") && board.Contains("sc"))
            {
                if (isSuper) winTracker.AddWinningBoards("cc,nc,sc");
                return true;
            }
            // Check third vertical column
            else if (board.Contains("ne") && board.Contains("ce") && board.Contains("se"))
            {
                if (isSuper) winTracker.AddWinningBoards("ne,ce,se");
                return true;
            }
            // Check diagonally
            else if (board.Contains("nw") && board.Contains("cc") && board.Contains("se"))
            {
                if (isSuper) winTracker.AddWinningBoards("nw,cc,se");
                return true;
            }
            // Check diagonally
            else if (board.Contains("sw") && board.Contains("cc") && board.Contains("ne"))
            {
                if (isSuper) winTracker.AddWinningBoards("sw,cc,ne");
                return true;
            }

            return false;
        }
    }
}
