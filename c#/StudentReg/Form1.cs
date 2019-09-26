using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudentReg
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnRegister_Click(object sender, EventArgs e)
        {
         //   listboxStudents.Items.Add("姓名 性别");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            listboxStudents.Items.Add("姓名 性别");
            DateTime d = dateTimePicker1.Value.ToLocalTime();
            textTime.Text = Convert.ToString(d);          
        }
    }
}
