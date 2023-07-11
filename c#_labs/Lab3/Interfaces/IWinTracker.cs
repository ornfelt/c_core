using System.Collections.Generic;

namespace Lab3
{
    // Interface of WinTracker
    public interface IWinTracker
    {
        void AddWinningBoards(string wins);
        void AddWinToDict(string board, string playerName);
        string GetEndResult();
        List<string> GetWinningBoards();
        Dictionary<string, string> GetWinsDict();
        bool HasWonSmallBoard(string board);
        void SetEndResult(string res);
        void ResetTracker();
    }
}