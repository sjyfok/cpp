using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HelloWindowForm
{
    public partial class myFirstForm : Form
    {
        public myFirstForm()
        {
            this.Text = "Hello Windows Forms!";
            Button button = new Button();
            button.Text = "Click Me!";
            button.Click += new EventHandler(button_Click);
            this.Controls.Add(button);
           // InitializeComponent();
        }

        void button_Click(Object sender, EventArgs e)
        {
            MessageBox.Show("That's a strong, confident click you have");
        }
    }

   
}
