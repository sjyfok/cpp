using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComboBoxExam
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cboSelecte.Items.Add("左对齐");
            cboSelecte.Items.Add("右对齐");
            cboSelecte.Items.Add("居中对齐");
           
            textBox1.Text = "对其字符";
        }

        private void cboSelecte_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch(cboSelecte.SelectedIndex)
            {
                case 0:
                    textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Left;
                    break;
                case 1:
                    textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
                    break;
                case 2:
                    textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
                    break;
                default:
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
