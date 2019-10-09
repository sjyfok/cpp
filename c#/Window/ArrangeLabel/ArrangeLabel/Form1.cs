using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArrangeLabel
{
    public partial class Form1 : Form
    {
        const int N = 4;
        Button[,] buttons = new Button[N, N];

        public Form1()
        {
            InitializeComponent();
            GenerateAllButtons();
        }
        void GenerateAllButtons()
        {
            int x0 = 100, y0 = 10, w = 45, d = 50;
            for(int r = 0; r < N; r ++)
                for(int c = 0; c < N; c++)
                {
                    int num = r * N + c;
                    Button btn = new Button();
                    btn.Text = (num + 1).ToString();
                    btn.Top = y0 + r * d;
                    btn.Left = x0 + c * d;
                    btn.Width = w;
                    btn.Height = w;
                    btn.Visible = true;
                    btn.Tag = r * N + c;
                    btn.Click += new EventHandler(btn_Click);
                    buttons[r, c] = btn;
                    this.Controls.Add(btn);
                }
            buttons[N - 1, N - 1].Visible = false;
        }

        void btn_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;
            Button blank = FindHiddenButton();
            if(IsNeighbor(btn, blank))
            {
                Swap(btn, blank);
                blank.Focus();
            }
            if (ResultIsOk())
            {
                MessageBox.Show("ok");
            }
        }

        Button FindHiddenButton()
        {
            for(int r = 0; r < N; r++)
                for(int c = 0; c < N; c ++)
                {
                    if (!buttons[r, c].Visible)
                        return buttons[r, c];
                }
            return null;
        }

        bool IsNeighbor(Button btnA, Button btnB)
        {
            int a = (int)btnA.Tag;
            int b = (int)btnB.Tag;
            int r1 = a / N, c1 = a % N;
            int r2 = b / N, c2 = b % N;

            if (r1 == r2 && (c1 == c2 - 1 || c1 == c2 + 1)
                || c1 == c2 && (r1 == r2 - 1 || r1 == r2 + 1))
                return true;
            return false;
        }

        bool ResultIsOk()
        {
            for(int r = 0; r<N; r++)
                for(int c = 0; c<N; c++)
                {
                    if (buttons[r, c].Text != (r * N + c+1).ToString())
                        return false;

                }
            return true;
        }

        void Shuffle()
        {
            Random rnd = new Random();
            for(int i = 0; i < 100; i ++)
            {
                int a = rnd.Next(N);
                int b = rnd.Next(N);
                int c = rnd.Next(N);
                int d = rnd.Next(N);
                Swap(buttons[a, b], buttons[c, d]);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Shuffle();
        }

        //按钮的位置一直没有改变 只改变按钮上面的文本和可见属性
        void Swap(Button btna, Button btnb)
        {
            string t = btna.Text;
            btna.Text = btnb.Text;
            btnb.Text = t;

            bool v = btna.Visible;
            btna.Visible = btnb.Visible;
            btnb.Visible = v;
        }
    }
}
