using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MySecondApp
{
    public partial class ResourceForm : Form
    {
        public ResourceForm()
        {
            InitializeComponent();
        }

        private void ResourceForm_Load(object sender, EventArgs e)
        {
            this.BackgroundImage = Properties.Resources.dlgbmp;
        }
    }
}
