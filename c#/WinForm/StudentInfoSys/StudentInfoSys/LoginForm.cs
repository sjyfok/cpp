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
    public partial class LoginForm : Form
    {
        public LoginForm()
        {
            InitializeComponent();
        }

        private void myDefaultBtn_Click(object sender, EventArgs e)
        {
            if(tbxUsr.Text == string.Empty || tbxPwd.Text == string.Empty)
            {
                MessageBox.Show("信息不完整!", "提示");
                return;
            }
            if(!tbxUsr.Text.Equals("admin")||!tbxPwd.Text.Equals("admin"))
            {
                MessageBox.Show("用户名或密码不正确!", "提示");
            }
            else
            {
                Welcome.updateform.Show();
                this.Close();
            }
        }

        private void myCancelBtn_Click(object sender, EventArgs e)
        {
            tbxPwd.Clear();
            tbxUsr.Clear();
        }
    }
}
