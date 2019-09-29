using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Status
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnProgress_Click(object sender, EventArgs e)
        {
            this.toolStripProgressBar1.ProgressBar.Value = this.toolStripProgressBar1.ProgressBar.Value % 100 + 10;
        }

        private void btnOperator_Click(object sender, EventArgs e)
        {
            this.toolStripStatusLabel1.Text = textBox1.Text;
            this.toolStripProgressBar1.ProgressBar.Value = 0;
        }
    }
}
