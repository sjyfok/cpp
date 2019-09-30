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

namespace FileCopy
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string szFileName = "test.txt";
            string szFileNameCopy = "testcopy.txt";
            if(!File.Exists(szFileName))
            {
                MessageBox.Show("文件不存在!");
            }
            else
            {
              
                if (File.Exists(szFileNameCopy))
                {
                    File.Delete(szFileNameCopy);
                }
                File.Copy(szFileName, szFileNameCopy);
                MessageBox.Show("文件复制成功!");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string szFileNameCopy = "testcopy.txt";
            if (File.Exists(szFileNameCopy))
            {
                File.Delete(szFileNameCopy);
            }
            File.CreateText(szFileNameCopy);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string szFileNameCopy = "testcopy.txt";
            if(File.Exists(szFileNameCopy))
            {
                File.Delete(szFileNameCopy);
                MessageBox.Show("文件删除成功");
            }
        }
    }
}
