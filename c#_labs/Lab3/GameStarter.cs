using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    public class GameStarter
    {
        // Private variables
        private State state;
        private String input;

        // Constructor
        public GameStarter(String input)
        {
            this.input = input;
        }

        // Start the game
        // We first validate the data and then choose the appropriate state
        public void StartGame()
        {
            // Validate input etc
            ValidateInput validateInput = new ValidateInput();
            bool inputIsValid = false;
            try
            {
                inputIsValid = validateInput.InputIsValid(input);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            if (inputIsValid)
                this.state = new GameLoopState();
            else
                this.state = new InvalidGameState();

            HandleGameState();
        }

        // Start handling the game state
        private void HandleGameState()
        {
            state.HandleGameState(input, this);
        }

        // Change the game state
        public void ChangeState(String input, State state)
        {
            this.input = input;
            this.state = state;
            HandleGameState();
        }

        // Fetch the current state
        public State GetState()
        {
            return state;
        }
    }
}
