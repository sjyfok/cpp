﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsDemo
{
    public partial class FormOpacity : Form
    {
        public FormOpacity()
        {
            InitializeComponent();
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            this.Opacity += 0.1;
        }

        private void btnSub_Click(object sender, EventArgs e)
        {
            if (this.Opacity > 0.2)
                this.Opacity -= 0.1;
            else
                this.Opacity = 1;
        }
    }
}
