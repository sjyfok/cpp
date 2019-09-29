using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace listbox
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            lstbDisplay.Items.Add("1");
            lstbDisplay.Items.Add("2");
            lstbDisplay.Items.Add("3");
            lstbDisplay.Items.Add("4");
            lstbDisplay.Items.Add("5");
            lstbDisplay.Items.Add("6");
            lstbDisplay.Items.Add("7");
            lstbDisplay.Items.Add("8");
            lstbDisplay.Items.Add("9");
            lstbDisplay.Items.Add("10");
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            int idx = lstbDisplay.SelectedIndex;
            if (idx == -1)            
                MessageBox.Show("没有选中项");
            else
                lstbDisplay.Items.RemoveAt(idx);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            lstbDisplay.Items.Clear();
        }

        private void btnSelect_Click(object sender, EventArgs e)
        {
            //string szDisp = Convert.ToString(lstbDisplay.SelectedIndex+1);
            //szDisp += "被选中";
            //MessageBox.Show(szDisp);   
            string szDisp = "";
            if (lstbDisplay.SelectedItem != null)
                szDisp += lstbDisplay.SelectedItem + " ";
            if (szDisp == "")
                MessageBox.Show("没有项被选中!");
            else
                MessageBox.Show(szDisp + "被选中");
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            lstbDisplay.Items.Add(txtAddItem.Text);
        }
    }
}
