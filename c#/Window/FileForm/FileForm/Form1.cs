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

namespace FileForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnCreateFile_Click(object sender, EventArgs e)
        {
            //string target = @"C:\temp\2.txt";
            //FILE 静态方法
            //if (File.Exists(target))
            //{
            //    File.Delete(target);
            //}
            //File.CreateText(target);

            //FileInfo类
            string fileinfos = @"C:\temp\fileinfotests.txt";
            FileInfo myfile = new FileInfo(fileinfos);
            if(!myfile.Exists)
            {
                myfile.CreateText();
            }
        }

        private void btnCopyFile_Click(object sender, EventArgs e)
        {
            //string source = @"C:\temp\2.txt";
            //string target = @"C:\temp\3.txt";

            //FILE 静态方法
            //if (!File.Exists(source))
            //{
            //    MessageBox.Show("文件不存在");
            //}
            //else
            //{
            //    if(File.Exists(target))
            //    {
            //        File.Delete(target);
            //    }
            //    File.Copy(source, target);
            //    MessageBox.Show("文件复制成功!");
            //}

            //FileInfo
            string fileinfos = @"C:\temp\fileinfotests.txt";
            string fileinfot = @"C:\temp\fileinfotestt.txt";
            FileInfo myfiles = new FileInfo(fileinfos);
            if(!myfiles.Exists)
            {
                MessageBox.Show("文件不存在");
            }
            else
            {
                FileInfo myfilet = new FileInfo(fileinfot);
                if (myfilet.Exists)
                    myfilet.Delete();
                myfiles.CopyTo(fileinfot);
            }
        }

        private void btnDelFile_Click(object sender, EventArgs e)
        {
            //string source = @"C:\temp\2.txt";
            //string target = @"C:\temp\3.txt";
            //FILE 静态方法
            //操作一段时间后 删除文件会出现异常，提示文件正在被使用
            //if(File.Exists(source))
            //{               
            //    File.Delete(source);
            //}
            //if (File.Exists(target))
            //    File.Delete(target);

            string fileinfos = @"C:\temp\fileinfotests.txt";
            string fileinfot = @"C:\temp\fileinfotestt.txt";

            FileInfo myfiles = new FileInfo(fileinfos);
            FileInfo myfilet = new FileInfo(fileinfot);

            //如果刚刚被copy过 不能删除文件 提示其他进程占用文件
            //需要留意如何解决
            if (myfiles.Exists)               
                myfiles.Delete();
         
            if (myfilet.Exists)
                myfilet.Delete();
        }
    }
}
