using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Reflection;
using System.IO;

namespace mine
{
    
    public partial class MainForm :  Form
    {
        const int primary_Grade = 1;
        const int secondry_Grade = 2;
        const int advance_Grade = 3;
        public MainForm()
        {
            InitializeComponent();
   
            switch (Properties.Settings.Default.GAME_GRADE)
            {
                case primary_Grade:
                    this.Width = 100;
                    this.Height = 100;
                    break;
                case secondry_Grade:
                    this.Width = 200;
                    this.Height = 200;
                    break;
                case advance_Grade:
                    this.Width = 300;
                    this.Height = 300;
                    break;
            }      
        }

        private void secondery_ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.GAME_GRADE = secondry_Grade;
            Properties.Settings.Default.Save();
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            Image image = images.BITMAP10;

            Graphics g;
            g.DrawImage(image, )

            //Assembly asm = this.GetType().Assembly;
           // Stream stream = asm.GetManifestResourceStream(mine.images.BITMAP10);
            //foreach(string resName in asm.GetManifestResourceNames())
            //{
            //    MessageBox.Show(resName);
            //}
        }
    }
}
