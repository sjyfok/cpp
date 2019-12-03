using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudentInfoSys
{
    public partial class BrowserForm : Form
    {
        public BrowserForm()
        {
            InitializeComponent();
            pictureBox1.Image = Image.FromFile(UpdateForm.path);
            rtbxStudentInfo.Text = UpdateForm.info;
        }
    }
}
