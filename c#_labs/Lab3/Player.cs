using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Lab3
{
    // This class handles the player specific functionality
    class Player : IPlayer
    {
        // Assignment to readonly can only occur as part of the declaration or in a constructor in the same class
        // Queue that will track all player moves
        private readonly Queue<String> playerQueue;
        // Hash sets that will keep track of every play on each board
        private BoardComposite boardComposite;
        private readonly String[] boardNames = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
        private readonly IWinTracker winTracker;
        private readonly IWinChecker wc;
        private String playerName;

        public Player(String name, IWinChecker wc, IWinTracker winTracker)
        {
            // Init values
            playerQueue = new Queue<String>();
            InitBoards();
            playerName = name;
            this.wc = wc;
            this.winTracker = winTracker;
        }

        // Create composite of playing boards 
        private void InitBoards()
        {
            boardComposite = new BoardComposite(playerName);
            foreach (String boardString in boardNames)
            {
                IPlayingBoard board = new PlayingBoard(boardString);
                boardComposite.AddPlayingBoard(board);
            }
        }

        // Add new play to hash set and queue, also check if this player has won the current board
        public bool HasWonBoard(String newPlay)
        {
            //Console.WriteLine("Adding " + newPlay + " to " + playerName + " queue...");
            AddToQueue(newPlay);
            try
            {
                String boardPos = newPlay.Split(".")[0];
                if (wc.HasWon(boardComposite.GetUpdatedBoardSet(newPlay), false))
                {
                    winTracker.AddWinToDict(boardPos, playerName);
                    return true;
                }
            }
            catch(NullReferenceException e) {
                Console.WriteLine("NullReferenceException: {0}", e.Message);
             }
            return false;
        }

        // Check if play can be added to board (it can't have a winner already)
        public bool CanBeAdded(String board)
        {
            return (!winTracker.HasWonSmallBoard(board));
            //if (winTracker.HasWonSmallBoard(board))
            //    return false;
            //else
            //    return true;
        }

        // This method is called if this player wins the super board
        public void PrintEndResults()
        {
            // *** Output Line 1 ***
            List<String> winningBoards = winTracker.GetWinningBoards();
            Console.WriteLine("\nPlayer: " + playerName + " wins. Winning boards of super board: " + string.Join(", ", winningBoards));

            // *** Output Line 2 ***
            // Use queue to print all winning plays
            String winningPlays = "";
            int counter = 0;
            while (counter < GetQueueSize())
            {
                String play = GetFirstValueInQueue().ToUpper();
                String[] playSplit = play.Split(".");
                String boardPos = playSplit[0];
                String boardPlay = playSplit[1];
                if (winningBoards.Contains(boardPos))
                    winningPlays += boardPos + "." + boardPlay + ", ";
                //else Console.WriteLine("Value not part of winning boards: " + boardPos + "." + boardPlay);
            }
            // Remove last comma and space
            winningPlays = winningPlays.Remove(winningPlays.Length - 2, 1);
            Console.WriteLine("\nWinning plays in order: " + winningPlays);

            // *** Output Line 3 ***
            // Print score for players 1 and 2
            Dictionary<string, string> boardWinsDict = winTracker.GetWinsDict();
            // Get this player score
            int playerWins = boardWinsDict.Values.Count(x => x.Equals(playerName));
            int otherPlayerWins = 0;
            String finalScoreString = "\nFinal score (p1, p2): ";

            if (playerName == "p1")
            {
                // Print this player's score first:
                otherPlayerWins = boardWinsDict.Values.Count(x => x.Equals("p2"));
                finalScoreString += "1." + playerWins + ", 0." + otherPlayerWins;
            }
            else
            {
                // Print this player's score second:
                otherPlayerWins = boardWinsDict.Values.Count(x => x.Equals("p1"));
                finalScoreString += "0." + otherPlayerWins + ", 1." + playerWins;
            }
            // Save the final score string to a variable in the WinTracker class
            winTracker.SetEndResult(finalScoreString.Replace("\nFinal score (p1, p2): ", ""));
            // Print final score
            Console.WriteLine(finalScoreString);
        }

        // This method is called if this player wins a small board where depth is 1
        public void PrintEndResults(bool hasDepthOne)
        {
            // *** Output Line 1 ***
            List<String> winningBoards = winTracker.GetWinningBoards();
            Console.WriteLine("\nPlayer: " + playerName + " wins a single board.");

            // *** Output Line 2 ***
            // Use queue to print all winning plays
            String winningPlays = "";
            int counter = 0;
            while (counter < GetQueueSize())
            {
                String play = GetFirstValueInQueue().ToUpper();
                winningPlays += play + ",";
                //else Console.WriteLine("Value not part of winning boards: " + boardPos + "." + boardPlay);
            }
            // Remove last comma
            winningPlays = winningPlays.Remove(winningPlays.Length - 1, 1);
            Console.WriteLine("\nWinning plays in order: " + winningPlays);

            // *** Output Line 3 ***
            // Print score for players 1 and 2
            Dictionary<string, string> boardWinsDict = winTracker.GetWinsDict();
            // Get this player score
            int playerWins = 1;
            int otherPlayerWins = 0;
            String finalScoreString = "\nFinal score (p1, p2): ";

            if (playerName == "p1")
            {
                // Print this player's score first:
                otherPlayerWins = 0;
                finalScoreString += playerWins + ", " + otherPlayerWins;
            }
            else
            {
                // Print this player's score second:
                otherPlayerWins = 0;
                finalScoreString += otherPlayerWins + ", " + playerWins;
            }
            // Save the final score string to a variable in the WinTracker class
            winTracker.SetEndResult(finalScoreString.Replace("\nFinal score (p1, p2): ", ""));
            // Print final score
            Console.WriteLine(finalScoreString);
        }

        // Add new value to queue
        public void AddToQueue(String newPlay)
        {
            playerQueue.Enqueue(newPlay);
        }

        // Set the player name
        public void SetPlayerName(String newName)
        {
            playerName = newName;

        }

        // Get the player name
        public string GetPlayerName()
        {
            return playerName;
        }

        // Get the player queue size
        public int GetQueueSize()
        {
            return playerQueue.Count;
        }

        // Get the first value in queue
        public String GetFirstValueInQueue()
        {
            return playerQueue.Dequeue();
        }
    }
}
