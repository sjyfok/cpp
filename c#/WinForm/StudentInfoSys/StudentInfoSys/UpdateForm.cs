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
    public partial class UpdateForm : Form
    {
        public static string path;
        public static string info;

        public UpdateForm()
        {
            InitializeComponent();
            path = @"E:\cpp\c#\WinForm\StudentInfoSys\picture\index.jpg";
            pictureBox1.Image = Image.FromFile(path);
        }

        private void mySubmitBtn_Click(object sender, EventArgs e)
        {
            info = "学号: " + tbxId.Text + "\r\n";
            info += "姓名: " + tbxName.Text + "\r\n";

            foreach(Control control in gbxSex.Controls)
            {
                if((control as RadioButton).Checked)
                {
                    info += "性别:" + (control as RadioButton).Text;
                }
            }

            Welcome.browserform = new BrowserForm();
            Welcome.browserform.Show();
            this.Opacity = 0;
        }
    }
}
