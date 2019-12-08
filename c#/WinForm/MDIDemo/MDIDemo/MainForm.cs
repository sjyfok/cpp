using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Notepad;
namespace MDIDemo
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void newNToolStripMenuItem_Click(object sender, EventArgs e)
        {

            frmTxt MDIChild = new frmTxt();
            MDIChild.MdiParent = this;
            
            MDIChild.Show();
        }

        private void vlayoutVToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void CascadeCToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }

        private void hlayoutHToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void closeallLToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach(Form childform in MdiChildren)
            {
                childform.Close();
            }
        }
    }
}
