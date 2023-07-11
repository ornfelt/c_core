using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    class InvalidGameState : State
    {
        // This method handles the game when the game input is invalid
        public override void HandleGameState(string input, GameStarter gameStarter)
        {
            Console.WriteLine("Invalid input");
            //Console.WriteLine("Invalid input. Wanna continue with standard input? (y/n)");
            //String userInput = Console.ReadLine().ToLower();
            //if (userInput.Contains("y") || userInput.Contains("yes"))
            //{
            //    input = "NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.CC, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE";
            //    gameStarter.ChangeState(input, new GameLoopState());
            //}
            //else
            //{
            //    Console.WriteLine("\nGoodbye!");
            //}
        }
    }
}
