using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    class GameOverState : State
    {
        // This method handles the game over state
        public override void HandleGameState(string input, GameStarter gameStarter)
        {
            String gameOverString = "\nGame over... ";
            if (input == "tie")
                Console.WriteLine(gameOverString + "No more plays can be made. No player won the super board.");
            else if (input == "unfinished")
                Console.WriteLine("Unfinished game. No player won the super board.");
            else if (input == "single")
                Console.WriteLine(gameOverString + "The single board was won!");
            else
                Console.WriteLine(gameOverString + input + " won the super board!");
                // One could use the memento design pattern to restore player objects to the initial states and start a new game afterwards
        }
    }
}
