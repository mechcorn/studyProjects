using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace obstCreate
{
    public class InitialData
    {
        public String k { get; set; }//ki - i-ый ключ
        public float p { get; set; }//pi - вероятность того, что аргументом поиска является ki
        public float q { get; set; }//qi - вероятность того, что аргумент поиска лежит между ki и ki+1
    }
}
