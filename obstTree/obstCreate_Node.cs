using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace obstCreate
{
    public class Node
    {//объект этого класса представляет собой (внутренний) узел дерева
        public String data { get; set; }//ключ узла
        public int level { get; set; }//уровень узла в дереве
        public Node left { get; set; }//левое поддерево
        public Node right { get; set; }//правое поддерево

        public Node(string outerData)
        {
            data = outerData;
        }
    }
}
