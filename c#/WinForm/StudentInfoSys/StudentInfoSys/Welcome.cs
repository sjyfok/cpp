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
    public partial class Welcome : Form
    {
        public static LoginForm loginform;
        public static UpdateForm updateform;
        public static BrowserForm browserform;
        public Welcome()
        {
            InitializeComponent();
            loginform = new LoginForm();
            updateform = new UpdateForm();
        }

        private void linkLabel1_Click(object sender, EventArgs e)
        {
            linkLabel1.LinkVisited = true;
            loginform.Show();
            this.Hide();  //隐藏当前窗口
        }
    }
}
