using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace obstCreate
{
    public partial class Form1 : Form
    {
        List<InitialData> source;//источник с данными, для построения оптимального дерева поиска
        Tree obst;//дерево
        List<VisibleData> list;//список, используется для постепенной визуализации дерева
        List<String> listTime;//список, в котором отражена зависимость времени работы алгоритма от n
        int listCounter=1;
        Timer makingTreeTimer;
        bool showLinks = false;//режим отрисовки связей между узлами

        Font drawFont = new Font("Arial", 5);
        Pen ellipsePen = new Pen(Color.Red, 1);
        Pen linkPen = new Pen(Color.Black, 1);
        int ellipseSize = 1;//размер узла дерева для визуализации

        public Form1()
        {
            InitializeComponent();
            CenterToScreen();
            source = new List<InitialData>();
            list = new List<VisibleData>();
            listTime = new List<String>();
            button1.Enabled = false;//делаем кнопку start недоступной
            buttonShow.Enabled = false;
            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //добавление обработчика события Paint
            Paint += new PaintEventHandler(Form1_Paint);
            DoubleBuffered = true;//двойная буфферизация, чтобы уменьшить или предотвратить мерцание
            makingTreeTimer = new Timer();
            makingTreeTimer.Interval = 5/*100*/;//период возникновения события Tick задаётся свойством Interval в миллисекундах
            makingTreeTimer.Tick += makingTreeTimer_Tick;
            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            MouseMove+=Form1_MouseMove;
        }

        void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            foreach(var node in list)
            {
                if ((node.point.X > e.X - 5 && node.point.X < e.X + 5) && (node.point.Y > e.Y - 5 && node.point.Y < e.Y + 5))
                {
                    labelBigText.Text = node.k;
                }
            }
        }

        void makingTreeTimer_Tick(object sender, EventArgs e)
        {
            makingTreeTimer.Stop();
            if (listCounter < obst.vData.Length)
            {
                list.Add(obst.vData[listCounter]);//добавляем очередной элемент массива в список
                listCounter++;
            }
            else
            {//когда все узлы дерева отобразятся, отобразим связи между узлами
                showLinks = true;
            }
            makingTreeTimer.Enabled = true;
            Refresh();
        }

        void Form1_Paint(object sender, PaintEventArgs e)
        {
                Graphics g = e.Graphics;//объект типа Graphics инкапсулирует  поверхность для рисования,
                //связанную с элементом управления

                foreach (var node in list)
                {
                    g.DrawEllipse(ellipsePen, node.point.X, node.point.Y, ellipseSize, ellipseSize);
                    g.DrawString(node.k, drawFont, Brushes.Black, node.point.X, node.point.Y - 15);
                }

                if (showLinks)
                {
                    foreach (var link in obst.linkData)
                    {
                        if (link[1] != null)//есть "наследующий" узел
                        {
                            Point[] points = new Point[2];

                            foreach (var point in obst.vData)
                            {
                                if (point.k == link[0])
                                {
                                    points[0] = point.point;
                                }
                                else if (point.k == link[1])
                                {
                                    points[1] = point.point;
                                }
                            }
                            g.DrawCurve(linkPen, points);
                        }
                    }
                }
        }       

        private void button1_Click(object sender, EventArgs e)
        {//построить дерево
            obst = new Tree();
            obst.makeObst(source);
            labelWorkingTime.Text = labelWorkingTime.Text + obst.workingTime;
            obst.showTree(ClientSize.Width);//---------------------------------------------|||||||||||||||||||||||

            listTime.Add(obst.workingTime + " " + (source.Count - 1));

            buttonShow.Enabled = true;
        }

        private void buttonShow_Click(object sender, EventArgs e)
        {//отобразить дерево
            ellipseSize = ClientSize.Width / source.Count - 1;//изменяем размер узла в зависимости от размера экрана и числа узлов
            ellipseSize = ellipseSize < 7 ? 7 : ellipseSize > 20 ? 20 : ellipseSize;
            makingTreeTimer.Start();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {//загружаем данные для источника из текстового файла
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.InitialDirectory="C:\\cSharp\\obstCreate\\obstCreate\\bin\\Debug\\data\\";
            openFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.RestoreDirectory = true;
            String fileName = null;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                fileName = openFileDialog1.FileName;
            }
            String[] lines = System.IO.File.ReadAllLines(fileName);
            //Read each line of the file into a string array. Each elementof the array is one line of the file.
            String[] items;

            source.Add(new InitialData() { k = "", p = 0, q = float.Parse(lines[0])});//считываем q0 из первой строки файла

            for (int i = 1; i < lines.Length; i++)
            {//считываем остальные данные - ключ, p, q
                items=lines[i].Split(' ');
                float pp = float.Parse(items[1]);
                float qq = float.Parse(items[2]);
                source.Add(new InitialData() { k = items[0], p = pp, q = qq });
            }
            button1.Enabled = true;//делаем кнопку start доступной
            labelFileName.Text = labelFileName.Text + fileName;
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            makingTreeTimer.Stop();
            button1.Enabled = false;
            buttonShow.Enabled = false;
            labelWorkingTime.Text = "Время работы алгоритма";
            labelFileName.Text = "Имя файла";
            source.Clear();
            list.Clear();
            listCounter = 1;
            showLinks = false;
            Refresh();
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            System.IO.File.WriteAllLines("C:\\cSharp\\obstCreate\\obstCreate\\bin\\Debug\\data\\logfile.txt", listTime);
        }
    }
}
