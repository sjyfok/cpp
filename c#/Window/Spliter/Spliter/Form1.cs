using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Spliter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            treeView1.Nodes.Add(new TreeNode("windows应用改程序"));
            treeView1.Nodes[0].Nodes.Add("第一章 windows 窗体和控件的使用");
            treeView1.Nodes[0].Nodes[0].Nodes.Add("窗体介绍");
            treeView1.Nodes[0].Nodes[0].Nodes.Add("创建一个新的windows程序");
            treeView1.Nodes[0].Nodes[0].Nodes.Add("多文档界面设计");
            treeView1.Nodes[0].Nodes[0].Nodes.Add("常用控件的使用");
            treeView1.Nodes[0].Nodes.Add("第二章 创建控件");
            treeView1.Nodes[0].Nodes[1].Nodes.Add("创建复合控件");
            treeView1.Nodes[0].Nodes[1].Nodes.Add("扩展控件");
            treeView1.Nodes[0].Nodes[1].Nodes.Add("自定义控件");

            listView1.View = View.Details;
            listView1.Columns.Add("编号", 100, HorizontalAlignment.Left);
            listView1.Columns.Add("标题", 200, HorizontalAlignment.Left);
            listView1.Columns.Add("描述", 400, HorizontalAlignment.Left);
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            listView1.Items.Clear();
            TreeNode tn = e.Node;
            if(tn.Nodes.Count > 0)
            {
                foreach (TreeNode node in tn.Nodes)
                {
                    ListViewItem lv = new ListViewItem();
                    lv.SubItems[0].Text = "第" + (node.Index + 1) + "项";
                    lv.SubItems.Add(node.Text);
                    listView1.Items.Add(lv);
                }
            }
        }
    }
}
