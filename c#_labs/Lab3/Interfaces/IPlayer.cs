namespace Lab3
{
    // Interface for Player objects
    interface IPlayer
    {
        void AddToQueue(string newPlay);
        bool CanBeAdded(string board);
        string GetFirstValueInQueue();
        string GetPlayerName();
        int GetQueueSize();
        bool HasWonBoard(string newPlay);
        void PrintEndResults();
        void PrintEndResults(bool hasDepthOne);
        void SetPlayerName(string newName);
    }
}