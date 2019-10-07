namespace question
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.labA = new System.Windows.Forms.Label();
            this.labOp = new System.Windows.Forms.Label();
            this.labB = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtRsl = new System.Windows.Forms.TextBox();
            this.btnQuestion = new System.Windows.Forms.Button();
            this.btnJudge = new System.Windows.Forms.Button();
            this.lisDisp = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // labA
            // 
            this.labA.AutoSize = true;
            this.labA.Location = new System.Drawing.Point(16, 45);
            this.labA.Name = "labA";
            this.labA.Size = new System.Drawing.Size(0, 12);
            this.labA.TabIndex = 0;
            // 
            // labOp
            // 
            this.labOp.AutoSize = true;
            this.labOp.Location = new System.Drawing.Point(90, 45);
            this.labOp.Name = "labOp";
            this.labOp.Size = new System.Drawing.Size(0, 12);
            this.labOp.TabIndex = 1;
            // 
            // labB
            // 
            this.labB.AutoSize = true;
            this.labB.Location = new System.Drawing.Point(169, 45);
            this.labB.Name = "labB";
            this.labB.Size = new System.Drawing.Size(0, 12);
            this.labB.TabIndex = 2;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(239, 49);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(11, 12);
            this.label4.TabIndex = 3;
            this.label4.Text = "=";
            // 
            // txtRsl
            // 
            this.txtRsl.Location = new System.Drawing.Point(269, 45);
            this.txtRsl.Name = "txtRsl";
            this.txtRsl.Size = new System.Drawing.Size(100, 21);
            this.txtRsl.TabIndex = 4;
            // 
            // btnQuestion
            // 
            this.btnQuestion.Location = new System.Drawing.Point(63, 106);
            this.btnQuestion.Name = "btnQuestion";
            this.btnQuestion.Size = new System.Drawing.Size(75, 23);
            this.btnQuestion.TabIndex = 5;
            this.btnQuestion.Text = "出题";
            this.btnQuestion.UseVisualStyleBackColor = true;
            this.btnQuestion.Click += new System.EventHandler(this.btnQuestion_Click);
            // 
            // btnJudge
            // 
            this.btnJudge.Location = new System.Drawing.Point(203, 106);
            this.btnJudge.Name = "btnJudge";
            this.btnJudge.Size = new System.Drawing.Size(75, 23);
            this.btnJudge.TabIndex = 6;
            this.btnJudge.Text = "判分";
            this.btnJudge.UseVisualStyleBackColor = true;
            this.btnJudge.Click += new System.EventHandler(this.btnJudge_Click);
            // 
            // lisDisp
            // 
            this.lisDisp.FormattingEnabled = true;
            this.lisDisp.ItemHeight = 12;
            this.lisDisp.Location = new System.Drawing.Point(47, 176);
            this.lisDisp.Name = "lisDisp";
            this.lisDisp.Size = new System.Drawing.Size(304, 112);
            this.lisDisp.TabIndex = 7;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(386, 313);
            this.Controls.Add(this.lisDisp);
            this.Controls.Add(this.btnJudge);
            this.Controls.Add(this.btnQuestion);
            this.Controls.Add(this.txtRsl);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.labB);
            this.Controls.Add(this.labOp);
            this.Controls.Add(this.labA);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labA;
        private System.Windows.Forms.Label labOp;
        private System.Windows.Forms.Label labB;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtRsl;
        private System.Windows.Forms.Button btnQuestion;
        private System.Windows.Forms.Button btnJudge;
        private System.Windows.Forms.ListBox lisDisp;
    }
}

