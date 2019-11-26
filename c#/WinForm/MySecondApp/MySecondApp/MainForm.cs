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
    public partial class MainFrom : Form
    {
        public MainFrom()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            //Setting class 自动生成
            decimal pi = Properties.Settings.Default.Pi;
            //Properties.Settings.Default.Pi = 3.142; //编译错误
            Properties.Settings.Default.WindowLoaction = this.Location;

            //保存用户设置
            Properties.Settings.Default.Save();

            //恢复保存上次设置
            Properties.Settings.Default.Reload();
            //恢复出厂设置
            Properties.Settings.Default.Reset();
        }
    }
}
