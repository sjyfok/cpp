using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace StudentReg
{
    public partial class Form1 : Form
    {
        private DateTime g_d;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnRegister_Click(object sender, EventArgs e)
        {
            //   listboxStudents.Items.Add("姓名 性别");
            string strFileName = "data.txt";
            using (StreamWriter sw = new StreamWriter(strFileName, true))
            {
                string male;
                
                //姓名
                sw.WriteLine(textStudentName.Text);
                //性别
                if (radioFemale.Checked == true)
                    male = "女";

                else if (radioMale.Checked == true)
                    male = "男";
                else
                    male = " ";              
                sw.WriteLine(male);
                //身份证号
                sw.WriteLine(textIDNumber.Text);
                //出生年月
                sw.WriteLine(textBirthday.Text);
                //地址
                sw.WriteLine(textAddress.Text);
                //邮编
                sw.WriteLine(textZip.Text);
                //电话
                sw.WriteLine(textPhoneNum.Text);
                //特长
                sw.WriteLine(textSpecialty.Text);
                //系部
                sw.WriteLine(cboDepartmant.Text);
                //专业
                sw.WriteLine(cboProfessional.Text);
                //班级
                sw.WriteLine(cboClass.Text);
                //学号
                sw.WriteLine(textStudentNum.Text);

                ListViewItem lvi = new ListViewItem();
                lvi.Text = textStudentName.Text;
                if (checkNum.Checked == true)
                    lvi.SubItems.Add(textStudentNum.Text);
                lvi.SubItems.Add(male);
                lvi.SubItems.Add(cboDepartmant.Text);
                if (checkProfessional.Checked == true)
                    lvi.SubItems.Add(cboProfessional.Text);
                lvi.SubItems.Add(cboClass.Text);
                lsvStudentInfo.Items.Add(lvi);
            }               
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cboDepartmant.Items.Add("计算机系");
            cboDepartmant.Items.Add("经济系");
            cboProfessional.Items.Add("计算机科学");
            cboProfessional.Items.Add("网络技术");
            cboProfessional.Items.Add("经济管理");
            cboProfessional.Items.Add("商务合同管理");
            cboClass.Items.Add("201982");
            cboClass.Items.Add("201983");

            string curPath  = System.Environment.CurrentDirectory;
            //判断存放数据的文件是否存在
            string strFileName = "data.txt";
            FileInfo fi = new FileInfo(strFileName);
            if (fi.Exists == false)
            {
                fi.Create();
            }
            
            using (StreamReader sr = new StreamReader("data.txt"))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    string[] record = new string[12];
                    record[0] = line;
                    for(int i= 1; i < 12;i ++)
                        record[i] = sr.ReadLine();
                    ListViewItem lvi = new ListViewItem();
                    lvi.Text = record[0];                    
                    if (checkNum.Checked == true)
                        lvi.SubItems.Add(record[11]);
                    lvi.SubItems.Add(record[1]);
                    lvi.SubItems.Add(record[8]);
                    if (checkProfessional.Checked == true)
                        lvi.SubItems.Add(record[9]);
                    lvi.SubItems.Add(record[10]);
                    lsvStudentInfo.Items.Add(lvi);
                }
            }
           

            if (checkProfessional.Checked == false)
                {
                    int i = 0;
                    foreach (var v in lsvStudentInfo.Columns)
                    {
                        if (((ColumnHeader)v).Text == "专    业")
                            lsvStudentInfo.Columns.RemoveAt(i);
                        i++;
                    }
                }
            if(checkNum.Checked == false)
            {
                int i = 0;
                foreach (var v in lsvStudentInfo.Columns)
                {
                    if (((ColumnHeader)v).Text == "学    号")
                        lsvStudentInfo.Columns.RemoveAt(i);
                    i++;
                }
            }

            g_d = dateTimePicker1.Value.ToLocalTime();
            labRegTime.Text = Convert.ToString(g_d);
            timer1.Start();            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //赋值必须要有 否则时间不更新 AddSeconds 返回了一个新的对象
            g_d = g_d.AddSeconds(1);
            labRegTime.Text = Convert.ToString(g_d);
        }

        private void checkProfessional_CheckedChanged(object sender, EventArgs e)
        {
            int i = 0;
            if (checkProfessional.Checked == false)
            {
               
                foreach (var v in lsvStudentInfo.Columns)
                {
                    if (((ColumnHeader)v).Text == "专    业")
                        lsvStudentInfo.Columns.RemoveAt(i);
                    i++;
                }
            }
            else
            {
                lsvStudentInfo.Items.Clear();
                ColumnHeader cheader = new ColumnHeader();
                cheader.Text = "专    业";
                cheader.Width = 120;
                lsvStudentInfo.Columns.Insert(4, cheader);
                using (StreamReader sr = new StreamReader("data.txt"))
                {
                    string line;
                    
                    while ((line = sr.ReadLine()) != null)
                    {
                        string[] record = new string[12];
                        record[0] = line;
                        for (int j = 1; j < 12; j++)
                            record[j] = sr.ReadLine();
                        ListViewItem lvi = new ListViewItem();
                        lvi.Text = record[0];
                        if (checkNum.Checked == true)
                            lvi.SubItems.Add(record[11]);
                        lvi.SubItems.Add(record[1]);
                        lvi.SubItems.Add(record[8]);
                        if (checkProfessional.Checked == true)
                            lvi.SubItems.Add(record[9]);
                        lvi.SubItems.Add(record[10]);
                        lsvStudentInfo.Items.Add(lvi);
                    }
                }
            }
        }

        private void radioFemale_CheckedChanged(object sender, EventArgs e)
        {
            this.Select();
        }

        private void radioMale_CheckedChanged(object sender, EventArgs e)
        {
            this.Select();
        }

        private void checkNum_CheckedChanged(object sender, EventArgs e)
        {
            int i = 0;
            if (checkNum.Checked == false)
            {

                foreach (var v in lsvStudentInfo.Columns)
                {
                    if (((ColumnHeader)v).Text == "学    号")
                        lsvStudentInfo.Columns.RemoveAt(i);
                    i++;
                }
            }
            else
            {
                lsvStudentInfo.Items.Clear();
                ColumnHeader cheader = new ColumnHeader();
                cheader.Text = "学    号";
                cheader.Width = 120;
                lsvStudentInfo.Columns.Insert(4, cheader);
                using (StreamReader sr = new StreamReader("data.txt"))
                {
                    string line;

                    while ((line = sr.ReadLine()) != null)
                    {
                        string[] record = new string[12];
                        record[0] = line;
                        for (int j = 1; j < 12; j++)
                            record[j] = sr.ReadLine();
                        ListViewItem lvi = new ListViewItem();
                        lvi.Text = record[0];
                        if (checkNum.Checked == true)
                            lvi.SubItems.Add(record[11]);
                        lvi.SubItems.Add(record[1]);
                        lvi.SubItems.Add(record[8]);
                        if (checkProfessional.Checked == true)
                            lvi.SubItems.Add(record[9]);
                        lvi.SubItems.Add(record[10]);
                        lsvStudentInfo.Items.Add(lvi);
                    }
                }
            }
        }
    }
}
