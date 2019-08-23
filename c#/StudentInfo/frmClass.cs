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
    public partial class frmClass : Form
    {
        public frmClass()
        {
            InitializeComponent();
        }

        private void frmClass_Load(object sender, EventArgs e)
        {
            cboUser.Items.Add("管理员");
            cboUser.Items.Add("学生");
            cboUser.Items.Add("教师");
            cboUser.SelectedIndex = 0;
            lstClass.Items.Add("计算机31501");
            lstClass.Items.Add("软件31631");
        }

        private void cboUser_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(cboUser.Text == "管理员")
            {
                btnAdd.Enabled = true;
                btnDel.Enabled = true;
                btnModify.Enabled = true;
                btnSeach.Enabled = true;
                btnStatistics.Enabled = true;
                btnClear.Enabled = true;
            }
            if(cboUser.Text == "教师")
            {
                btnDel.Enabled = false;
                btnModify.Enabled = true;
                btnClear.Enabled = false;
            }
            if(cboUser.Text == "学生")
            {
                btnDel.Enabled = false;
                btnModify.Enabled = false;
                btnClear.Enabled = false;
            }

        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            if(txtClassName.Text != "")
            {
                lstClass.Items.Add(txtClassName.Text);
            }
            txtClassName.Text = "";
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            lstClass.Items.Remove(lstClass.SelectedItem);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            lstClass.Items.Clear();
        }

        private void btnSeach_Click(object sender, EventArgs e)
        {
            int nIndex = lstClass.FindString(txtClassName.Text);
            if (nIndex != -1)
                lstClass.SetSelected(nIndex, true);
        }

        private void btnModify_Click(object sender, EventArgs e)
        {
            if (txtClassName.Text != "")
            {
                int index = lstClass.SelectedIndex;
                lstClass.Items.RemoveAt(index);
                lstClass.Items.Insert(index, txtClassName.Text);
                txtClassName.Text = "";
            }
        }

        private void btnStatistics_Click(object sender, EventArgs e)
        {
            txtClassCount.Text = lstClass.Items.Count.ToString();
        }
    }
}
