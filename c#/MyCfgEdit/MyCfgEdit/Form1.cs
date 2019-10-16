using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyCfgEdit
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.tabMain.Region = new Region(new RectangleF(this.tabPage1.Left,
                this.tabPage1.Top, this.tabPage1.Width, this.tabPage1.Height));
        }
    }
}
