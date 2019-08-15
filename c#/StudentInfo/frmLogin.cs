using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudentInfo
{
    public partial class frmLogin : Form
    {
        public frmLogin()
        {
            InitializeComponent();
        }

        private bool CheckPsw()
        {
            string sUser = txtUser.Text.ToString();
            string sPsw = txtPsw.Text.ToString();
            if (sUser == "Admin" && sPsw == "12345")
                return true;
            else
                return false;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string sUser = txtUser.Text.ToString();
            string sPsw = txtPsw.Text.ToString();

            if(CheckPsw() == true)
            {
                frmMain mainFrm = new frmMain();
                mainFrm.Show();
                this.Hide();
            }
            else
                lblLoginError.Text = "用户名或密码错误，请重新输入!";


            //if (sUser == "Admin" && sPsw == "12345")
            //{
            //    frmMain mainFrm = new frmMain();
            //    mainFrm.Show();
            //    this.Hide();
            //}
            //else
            //{
            //    lblLoginError.Text = "用户名或密码错误，请重新输入!";
            //}
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
