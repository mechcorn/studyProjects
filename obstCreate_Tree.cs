using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Diagnostics;

namespace obstCreate
{
    class Tree//Абстрактный тип даных
    {//объект этого класса представляют собой дерево
        Node root;//корень дерева
        float[,] c;//цена дерева t(i,j)
        float[,] w;//общий вес t(i,j)
        int[,] r;//корень t(i,j)
        InitialData[] idata;//массив для хранения исходных данных
 public VisibleData[] vData;//массив для визуализации дерева
 public List<String[]> linkData;//список со связями между узлами
        int indexForVisible = 1;//индекс, используемый при наполнении массива координатами узлов дерева

        Stopwatch sw = new Stopwatch();//создаём объект класса Stopwatch, класс Stopwatch предоставляет набор методов и средств,
                                       //которые можно использовать для точного измерения затраченного времени
        public String workingTime { get; set; }//время работы алгоритма

        void fillArrays(List<InitialData> source)
        {//алгоритм строит бинарные деревья t(i,j), имеющие минимальную цену для весов
                                                        //(p от i+1 до j; q от i до j)
            //результаты работы алгоритма определяются массивом r: при i=j t(i,j) пуст;
            //в противном случае левое поддерево - t(i, r[i,j]-1),
            //а правое поддерево - t(r[i,j],j)

            int n = source.Count-1;//количество элементов в источнике(один из элементов имеет значимое поле только q0)
            //q0 - представляет собой вероятность того, что аргумент поиска меньше, чем k1
            //кстати, qn - вероятность того, что аргумент поиска больше, чем kn

            //перемещаем исходные данные из списка в массив, для удобства обработки
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            idata = new InitialData[source.Count];
            int index = 0;
            foreach (var item in source)
            {
                idata[index] = item;
                index++;
            }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            sw.Start();//Begin timing
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            c = new float[n+1, n+1];
            w = new float[n+1, n+1];
            r = new int[n+1, n+1];
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //эти действия определяют все оптимальные деревья из одного узла
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            for (int i = 0; i <= n; i++)
              {
                  for (int j = 0; j <= n; j++)
                  {
                      c[i, j] = 0;
                      w[i, j] = 0;
                      r[i, j] = 0;//обнуляем массивы
                  }
              }

            for (int i = 0; i <= n; i++)
            {
                w[i, i] = idata[i].q;

                for (int j = i + 1; j <= n; j++)
                {
                    w[i, j] = w[i, j - 1] + idata[j].p + idata[j].q;
                }
            }
            for (int j = 1; j <= n; j++)
            {
                c[j - 1, j] = w[j - 1, j];
                r[j - 1, j] = j;
            }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++           
            //на данном шаге определяются все оптимальные деревья с d узлами
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            for (int d = 2; d <= n; d++)
            {//к этому моменту уже определены оптимальные деревья с менее чем d узлами
                //find an optimal tree with d number of nodes
                for (int j = d; j <= n; j++)
                {
                    int i = j - d;

                    //find c[i][j] by selecting the minimum
                    int k = find(r, c, i, j);
                    c[i, j] = w[i, j] + c[i, k - 1] + c[k, j];
                    r[i, j] = k;//присваиваем значение k, для которого достигается минимум
                }
            }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            sw.Stop();//Stop timing
            workingTime = "" + sw.Elapsed;
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            vData = new VisibleData[source.Count];//размер массива число узлов в дереве + 1 технический элемент
            vData[0] = new VisibleData();
            vData[0].point.X = 10;
            //технический элемент массива
        }

        int find(int[,] r, float[,] c, int i, int j)
        {
            int m = r[i, j - 1];
            float min = c[i, m - 1] + c[m, j];

            for (int k = m + 1; k <= r[i + 1, j]; k++)
            {
                if (c[i, k - 1] + c[k, j] < min)
                {
                    min = c[i, k - 1] + c[k, j];
                    m = k;
                }
            }
            return m;
        }

        Node make(int i, int j, int outerLevel)//создаёт узлы и связывает их с их левыми и правыми поддеревьями
        {
            Node node = null;
            if (r[i, j] == 0)
            {
                return null;
            }
            else
            {
                node = new Node(idata[r[i, j]].k);
                node.level = outerLevel;
                int nextLevel = outerLevel + 1;
                node.left = make(i, r[i, j] - 1, nextLevel);
                node.right = make(r[i, j], j, nextLevel);
                return node;
            }
        }

        void showNode(Node node, int width)//---------------------------------------------|||||||||||||||||||||||
        {//наполнение данными массива для визуализации дерева
            if (node != null)
            {
                showNode(node.left, width);//---------------------------------------------|||||||||||||||||||||||
                
                VisibleData vd = new VisibleData();
                //vData[0].point.X = vData[0].point.X + 30;//смещаем по x, чтобы узлы в кучу не сливались
                int offset = (width-10)/idata.Length;//величина смещения
                offset = offset == 0 ? 1 : offset;
                
                vData[0].point.X = vData[0].point.X + offset;
                vd.k = node.data;
                vd.level = node.level;
                vd.point.X = vData[0].point.X;
                //vd.point.Y = node.level * 50+50;
                vd.point.Y = node.level * 25 + 50;

                //свяжем узлы через ключи
                String[] leftLink = new String[2];
                leftLink[0] = node.data;
                leftLink[1] = node.left != null ? node.left.data : null;
                linkData.Add(leftLink);

                String[] rightLink = new String[2];
                rightLink[0] = node.data;
                rightLink[1] = node.right != null ? node.right.data : null;
                linkData.Add(rightLink);


                vData[indexForVisible] = vd;
                indexForVisible++;

                showNode(node.right, width);//---------------------------------------------|||||||||||||||||||||||
            }
        }

        //операторы----------------АТД дерева---------------------------------
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        public void makeObst(List<InitialData> outerSource)//делает из пустого дерева оптимальное дерево поиска
        {
            fillArrays(outerSource);
            root = make(0, outerSource.Count - 1, 0);//outerSource.Count - 1, т.к. в первом элементе из значащих полей только q0
        }
        public void showTree(int width)//показывает дерево поиска
        {
            linkData = new List<String[]>();
            showNode(root, width);//вызывается метод showNode по отношению к своему корню, 0 метка, что отправлен корень//---------------------------------------------|||||||||||||||||||||||
        }
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }
}
