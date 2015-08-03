using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace obstCreate
{
    public class VisibleData
    {
        public String k { get; set; }//данные в узле дерева
        public int level { get; set; }//уровень узла в дереве
        public Point point;// { get; set; }//координаты узла дерева

        public VisibleData()
        {
            k = "";
            level = 0;
            point.X = 0;
            point.Y = 0;
        }
    }
}
