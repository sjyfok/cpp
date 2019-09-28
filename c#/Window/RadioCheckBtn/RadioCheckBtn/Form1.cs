using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RadioCheckBtn
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void switchcolor()
        {
            btnDisplay.ForeColor = Color.Blue;
            txtResult.ForeColor = Color.Red;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string szTemp;
            txtResult.Text = "姓名为:" + txtName.Text + " 班级为:" + txtClass.Text +
                " 性别为:";
            if (rdoMale.Checked == true)
                szTemp = "男";
            else
                szTemp = "女";// + rdoMale.Checked ? "男" : "女";
            txtResult.Text += szTemp;
            txtResult.Text += " 爱好为:";
            szTemp = "";
            if (ckbTravel.Checked == true)
                szTemp += "旅游";
            if (ckbShop.Checked == true)
                szTemp += "逛街";
            if (ckbGame.Checked == true)
                szTemp += "游戏";
            if (ckbComputer.Checked == true)
                szTemp += "电脑";
            txtResult.Text += szTemp;
            switchcolor();
        }
    }
}
