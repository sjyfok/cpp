using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VisualGraph;


namespace MyCfgEdit
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.tabMain.Region = new Region(new RectangleF(this.tabPage1.Left,
                this.tabPage1.Top, this.tabPage1.Width, this.tabPage1.Height));

            NewPage("Page1", Color.White, 549, 387);
            this.treeView1.ExpandAll();
           
            
        }

        private void NewPage(string pagename, Color back, int width, int height)
        {
            int count = tabMain.TabPages.Count;
            for (int j = count - 1; j >= 1; j--)
                tabMain.TabPages.RemoveAt(j);

            VisualGraph.VisualGraph vs = new VisualGraph.VisualGraph();
            vs.Name = pagename;
            vs.Width = width;
            vs.Height = height;
            vs.BackGroundColor = back;
            vs.MouseClick += new MouseEventHandler(vs_MouseClick);

            TabPage page = new TabPage();
            page.Name = pagename;
            page.Text = pagename;
            page.Tag = pagename;
            page.Controls.Add(vs);
           
            tabMain.TabPages.Add(page);
            tabMain.SelectTab(pagename);
          
        }

        void vs_MouseClick(object sender, MouseEventArgs e)
        {
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)sender;
            if(e.Button == MouseButtons.Left)
            {
                if (drawArea.ObjList.SelectionCount > 0)
                {
                    DrawObject obj = drawArea.ObjList.GetSelectedObject(0);
                    this.propertyGrid1.SelectedObject = obj;
                }
                else
                    this.propertyGrid1.SelectedObject = drawArea;
            }
        }

        private void treeView1_MouseDown(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left)
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = treeView1.GetNodeAt(ClickPoint);
                if (CurrentNode != null)
                    treeView1.SelectedNode = CurrentNode;
            }
        }

        private void treeView1_ItemDrag(object sender, ItemDragEventArgs e)
        {
            if (e.Button == MouseButtons.Right) return;

            string str = treeView1.SelectedNode.Text;
            if (str == "")
                return;
            GetActivedObjectType(str);
            treeView1.DoDragDrop(str, DragDropEffects.Copy | DragDropEffects.Move);
        }

        protected void GetActivedObjectType(String s)
        {
            TabPage page = tabMain.SelectedTab;

            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            if (s == null) drawArea.ActivedObjType = Global.DrawType.POINTER;
            if (s == "Line") drawArea.ActivedObjType = Global.DrawType.DrawLine;
            if (s == "Rectangle") drawArea.ActivedObjType = Global.DrawType.DrawRectangle;
            if (s == "Ellipse") drawArea.ActivedObjType = Global.DrawType.DrawEllipse;
            if (s == "Text") drawArea.ActivedObjType = Global.DrawType.DrawText;
            if (s == "Picture") drawArea.ActivedObjType = Global.DrawType.DrawPic;
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.AlignLeft();
            drawArea.Invalidate();
        }

        private void toolStripButton6_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.AlignVCenter();
            drawArea.Invalidate();
        }

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.AlignRight();
            drawArea.Invalidate();
        }

        private void toolStripButton8_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.AlignTop();
            drawArea.Invalidate();
        }

        private void toolStripButton9_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.AlignHCenter();
            drawArea.Invalidate();
        }

        private void toolStripButton10_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.AlignBottom();
            drawArea.Invalidate();
        }

        private void toolStripButton11_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.MoveSelectionToFront();
            drawArea.Invalidate();
        }

        private void toolStripButton12_Click(object sender, EventArgs e)
        {
            TabPage page = tabMain.SelectedTab;
            VisualGraph.VisualGraph drawArea = (VisualGraph.VisualGraph)page.Controls[0];
            drawArea.ObjList.MoveSelectionToBack();
            drawArea.Invalidate();
        }
    }
}

