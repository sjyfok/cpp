using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tree
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            for(int i = 1; i <= 10; i ++)
            {
                int n = 5;
                TreeNode[] children = new TreeNode[n];
                for (int j = 1; j <= n; j++)
                    children[j - 1] = new TreeNode("Child " + j.ToString());
                TreeNode node = new TreeNode("Parent " + i.ToString(), children);
                treeView1.Nodes.Add(node);                
            }
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            MessageBox.Show(this.treeView1.SelectedNode.Text +
                " is selected!");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show(this.treeView1.SelectedNode.Text);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.treeView1.Nodes.Remove(this.treeView1.SelectedNode);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            treeView1.Nodes.Add(textBox1.Text, textBox2.Text);
        }
    }
}
