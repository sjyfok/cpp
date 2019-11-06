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

namespace ResourceTest.StartUp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           


            Type type = MethodBase.GetCurrentMethod().DeclaringType;

            string _namespace = type.Namespace;

            //获得当前运行的Assembly

            Assembly _assembly = Assembly.GetExecutingAssembly();

            //根据名称空间和文件名生成资源名称

            string resourceName = _namespace + ".Resource.SplashScreen.jpg";

            //根据资源名称从Assembly中获取此资源的Stream

           // Stream stream = _assembly.GetManifestResourceStream(resourceName);

           

           // Image myImage = Image.FromStream(stream);

            Bitmap bitmap = new Bitmap(typeof(Form1).Assembly.GetManifestResourceStream(resourceName));
        }
    }
}
