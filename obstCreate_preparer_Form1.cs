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
using System.Net;

namespace preparer
{
    public partial class Form1 : Form
    {
        Dictionary<String, int> stringDic = new Dictionary<string, int>();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int outerCount = Int32.Parse(textBox1.Text);
            char[] delimiters = Enumerable.Range(0, 256).Select(i => (char)i)
                .Where(c => Char.IsWhiteSpace(c) || Char.IsPunctuation(c)).ToArray();//delimiters - массив возможных разделителей слов
            //(white-символы, знаки пунктуации)

            var files = Directory.EnumerateFiles("C:\\Books", "*.txt");//получаем список файлов в виде перечислимой структуры
            String[] temp;//массив строк файла
            String[] words;//массив слов файла

            foreach (var path in files)
            {
                temp = File.ReadAllLines(path);

                foreach (String str in temp)
                {
                    words = str.Split(delimiters);
                    foreach (String word in words)
                    {
                        if (stringDic.ContainsKey(word))
                        {
                            stringDic[word]++;
                        }
                        else
                        {
                            stringDic.Add(word, 1);
                        }
                    }
                }
            }

            String[] strArray = new String[/*stringDic.Count*/outerCount];
            int count = 0;
            foreach (var pair in stringDic)
            {
                if (count >= outerCount)
                {
                    break;
                }
                strArray[count] = pair.Key + " " + pair.Value + " 0";
                count++;
            }

            String fileName = "C:\\cSharp\\bigData" + outerCount + ".txt";
            System.IO.File.WriteAllLines(fileName, strArray);
        }

        private void buttonSite_Click(object sender, EventArgs e)
        {
            String address = textBox1.Text;
            WebClient client = new WebClient();
            //client.Encoding = System.Text.Encoding.Default;
            String str = client.DownloadString(address);
            //String decodedStr = WebUtility.HtmlDecode(str);
            String newStr = str.Replace("<div style='min-height:40px'><i>", "|").Replace("<span style=\"color: #650810\"><b>", "|").Replace("<div style='min-height:40px'><span style=\"color: #650810\"><b>", "|").Replace("<div style='min-height:40px'>", "|").Replace("</div>", "~").Replace(".push(function()", "~").Replace("</b></span>", "|");
            String result = "";
            bool text = false;

            var chars=from ch in newStr select ch;
            foreach (var item in chars)
            {
                if (item == '|')
                {
                    text = true;
                }
                else if (item == '~')
                {
                    text = false;
                }
                if (text)
                {
                    result += item;
                }
            }

            char[] delimiters = Enumerable.Range(0, 256).Select(i => (char)i)
                .Where(c => Char.IsWhiteSpace(c) || Char.IsPunctuation(c)).ToArray();//delimiters - массив возможных разделителей слов
            //(white-символы, знаки пунктуации)

            String[] res = result.Split(delimiters);
            String[] outputRes=new String[res.Length];
            int count1 = 0;
            foreach (var word in res)
            {
                    outputRes[count1] = word.Replace("<br><i>", "").Replace("<br>", "").Replace("<i>", "").Replace("<", "").Replace("|", "").Replace(">", "");
                    count1++;      
            }

            List<String> list = new List<String>();
            
            foreach(var word in outputRes)
            {
                if (!word.Equals("") && !word.Equals("—"))
                {
                    list.Add(word);
                }
            }

            //stringDic.Clear();

            foreach (String word in list)
            {
                if (stringDic.ContainsKey(word))
                {
                    stringDic[word]++;
                }
                else
                {
                    stringDic.Add(word, 1);
                }
            }

            String[] strArray = new String[stringDic.Count];
            int count = 0;
            foreach (var pair in stringDic)
            {
                if (count >= stringDic.Count)
                {
                    break;
                }
                strArray[count] = pair.Key + " " + pair.Value + " 0";
                count++;
            }

            System.IO.File.WriteAllLines("C:\\cSharp\\bigData.txt", strArray);
        }
    }
}
