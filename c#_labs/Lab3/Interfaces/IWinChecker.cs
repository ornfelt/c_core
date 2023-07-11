using System.Collections.Generic;

namespace Lab3
{
    // Interface of WinChecker
    interface IWinChecker
    {
        bool HasWon(HashSet<string> board, bool isSuper);
        bool HasWonSuperBoard(string playerName);
    }
}