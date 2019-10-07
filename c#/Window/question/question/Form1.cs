using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace question
{
    public partial class Form1 : Form
    {
        int a;
        int b;
        string op;
        int result;
        Random rnd = new Random();

        public Form1()
        {
            InitializeComponent();
        }

        private void btnQuestion_Click(object sender, EventArgs e)
        {
            a = rnd.Next(9) + 1;
            b = rnd.Next(9) + 1;
            int c = rnd.Next(4);
            switch(c)
            {
                default:
                    break;
                case 0:
                    op = "+";
                    result = a + b;
                    break;
                case 1:
                    op = "-";
                    result = a - b;
                    break;
                case 2:
                    op = "*";
                    result = a * b;
                    break;
                case 3:
                    op = "/";
                    result = a / b;
                    break;
            }
            labA.Text = a.ToString();
            labB.Text = b.ToString();
            labOp.Text = op;
            txtRsl.Text = "";
        }

        private void btnJudge_Click(object sender, EventArgs e)
        {
            string str = txtRsl.Text;
            double d = double.Parse(str);
            string disp = "" + a + op + b + "=" + str + " ";
            if (d == result)
                disp += "v";
            else
                disp += "x";

            lisDisp.Items.Add(disp);
        }
    }
    

}
