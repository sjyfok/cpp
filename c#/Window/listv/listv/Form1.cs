using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace listv
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < 5; i++)
            {
                ListViewItem lstvitem = new ListViewItem();
                lstvitem.Text = i.ToString();
                lstvitem.SubItems.Add(i.ToString());
                listView1.Items.Add(lstvitem);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ListViewItem lstvitem = new ListViewItem();
            lstvitem.Text = textBox1.Text;
            lstvitem.SubItems.Add(textBox2.Text);
            listView1.Items.Add(lstvitem);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string msg = "";
            foreach (ListViewItem vitem in listView1.SelectedItems)
                msg += "[" + vitem.SubItems[0].Text + "," + vitem.SubItems[1].Text + "]";

            if (msg == "")
                MessageBox.Show("没有项被选中!");
            else
                MessageBox.Show(msg + "被选中!");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem vi in listView1.SelectedItems)
                listView1.Items.Remove(vi);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listView1.Items.Clear();
        }
    }
}
