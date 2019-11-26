using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HelloWindowForm
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            //MessageBox.Show("Hello Windows forms!");
            Form form = new myFirstForm();
            //form.ShowDialog() ;
           // form.Text = "Hello Windows Forms!";
            Application.Run(form); //将form作为主窗体
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());
        }
    }
}
