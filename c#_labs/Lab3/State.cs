using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    // Abstract state class that can be inherited from game state classes
    public abstract class State
    {
        public abstract void HandleGameState(String input, GameStarter gameStarter);
    }
}
