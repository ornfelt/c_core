using System;
using System.Collections.Generic;
using System.Text;

namespace Lab3
{
    interface IResultVisualizer
    {
        void VisualizePlays(List<String> finalValidPlays, Boolean HasDepthOne);
    }
}
