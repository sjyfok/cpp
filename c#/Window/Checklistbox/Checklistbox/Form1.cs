using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Checklistbox
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            chkliboxNum.Items.Add("one");
            chkliboxNum.Items.Add("two");
            chkliboxNum.Items.Add("three");
            chkliboxNum.Items.Add("four");
            chkliboxNum.Items.Add("five");
            chkliboxNum.Items.Add("six");
            chkliboxNum.Items.Add("seven");
            chkliboxNum.Items.Add("eight");
            chkliboxNum.Items.Add("nine");
            chkliboxNum.Items.Add("ten");
        }

        private void btnMove_Click(object sender, EventArgs e)
        {
            if(chkliboxNum.CheckedItems.Count > 0)
            {
                listBox1.Items.Clear();
                foreach (string item in chkliboxNum.CheckedItems)
                    listBox1.Items.Add(item.ToString());

                for(int i = 0; i < chkliboxNum.Items.Count; i ++)
                {
                    chkliboxNum.SetItemChecked(i, false);
                }
            }
        }
    }
}
