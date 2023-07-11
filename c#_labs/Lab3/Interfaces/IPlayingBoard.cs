using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    // Interface of Playing board object
    interface IPlayingBoard
    {
        HashSet<string> GetUpdatedBoardSet(String value);
        string GetName();
    }
}
