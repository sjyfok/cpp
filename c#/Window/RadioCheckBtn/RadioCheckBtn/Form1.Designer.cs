namespace RadioCheckBtn
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtName = new System.Windows.Forms.TextBox();
            this.txtClass = new System.Windows.Forms.TextBox();
            this.btnDisplay = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtResult = new System.Windows.Forms.TextBox();
            this.rdoMale = new System.Windows.Forms.RadioButton();
            this.rdoFemale = new System.Windows.Forms.RadioButton();
            this.ckbTravel = new System.Windows.Forms.CheckBox();
            this.ckbShop = new System.Windows.Forms.CheckBox();
            this.ckbGame = new System.Windows.Forms.CheckBox();
            this.ckbComputer = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(41, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "姓名";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(43, 74);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "班级";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(109, 19);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(100, 21);
            this.txtName.TabIndex = 2;
            // 
            // txtClass
            // 
            this.txtClass.Location = new System.Drawing.Point(109, 70);
            this.txtClass.Name = "txtClass";
            this.txtClass.Size = new System.Drawing.Size(100, 21);
            this.txtClass.TabIndex = 3;
            // 
            // btnDisplay
            // 
            this.btnDisplay.ForeColor = System.Drawing.Color.Red;
            this.btnDisplay.Location = new System.Drawing.Point(301, 70);
            this.btnDisplay.Name = "btnDisplay";
            this.btnDisplay.Size = new System.Drawing.Size(75, 23);
            this.btnDisplay.TabIndex = 4;
            this.btnDisplay.Text = "显示";
            this.btnDisplay.UseVisualStyleBackColor = true;
            this.btnDisplay.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rdoFemale);
            this.groupBox1.Controls.Add(this.rdoMale);
            this.groupBox1.Location = new System.Drawing.Point(45, 112);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(164, 87);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "性别";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.ckbComputer);
            this.groupBox2.Controls.Add(this.ckbGame);
            this.groupBox2.Controls.Add(this.ckbShop);
            this.groupBox2.Controls.Add(this.ckbTravel);
            this.groupBox2.Location = new System.Drawing.Point(215, 112);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(225, 87);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "爱好";
            // 
            // txtResult
            // 
            this.txtResult.Location = new System.Drawing.Point(45, 234);
            this.txtResult.Multiline = true;
            this.txtResult.Name = "txtResult";
            this.txtResult.Size = new System.Drawing.Size(395, 62);
            this.txtResult.TabIndex = 7;
            // 
            // rdoMale
            // 
            this.rdoMale.AutoSize = true;
            this.rdoMale.Checked = true;
            this.rdoMale.Location = new System.Drawing.Point(6, 27);
            this.rdoMale.Name = "rdoMale";
            this.rdoMale.Size = new System.Drawing.Size(35, 16);
            this.rdoMale.TabIndex = 0;
            this.rdoMale.TabStop = true;
            this.rdoMale.Text = "男";
            this.rdoMale.UseVisualStyleBackColor = true;
            // 
            // rdoFemale
            // 
            this.rdoFemale.AutoSize = true;
            this.rdoFemale.Location = new System.Drawing.Point(6, 54);
            this.rdoFemale.Name = "rdoFemale";
            this.rdoFemale.Size = new System.Drawing.Size(35, 16);
            this.rdoFemale.TabIndex = 1;
            this.rdoFemale.Text = "女";
            this.rdoFemale.UseVisualStyleBackColor = true;
            // 
            // ckbTravel
            // 
            this.ckbTravel.AutoSize = true;
            this.ckbTravel.Location = new System.Drawing.Point(7, 27);
            this.ckbTravel.Name = "ckbTravel";
            this.ckbTravel.Size = new System.Drawing.Size(48, 16);
            this.ckbTravel.TabIndex = 0;
            this.ckbTravel.Text = "旅游";
            this.ckbTravel.UseVisualStyleBackColor = true;
            // 
            // ckbShop
            // 
            this.ckbShop.AutoSize = true;
            this.ckbShop.Location = new System.Drawing.Point(122, 27);
            this.ckbShop.Name = "ckbShop";
            this.ckbShop.Size = new System.Drawing.Size(48, 16);
            this.ckbShop.TabIndex = 1;
            this.ckbShop.Text = "逛街";
            this.ckbShop.UseVisualStyleBackColor = true;
            // 
            // ckbGame
            // 
            this.ckbGame.AutoSize = true;
            this.ckbGame.Location = new System.Drawing.Point(7, 54);
            this.ckbGame.Name = "ckbGame";
            this.ckbGame.Size = new System.Drawing.Size(48, 16);
            this.ckbGame.TabIndex = 2;
            this.ckbGame.Text = "游戏";
            this.ckbGame.UseVisualStyleBackColor = true;
            // 
            // ckbComputer
            // 
            this.ckbComputer.AutoSize = true;
            this.ckbComputer.Location = new System.Drawing.Point(122, 54);
            this.ckbComputer.Name = "ckbComputer";
            this.ckbComputer.Size = new System.Drawing.Size(48, 16);
            this.ckbComputer.TabIndex = 3;
            this.ckbComputer.Text = "电脑";
            this.ckbComputer.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(479, 308);
            this.Controls.Add(this.txtResult);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnDisplay);
            this.Controls.Add(this.txtClass);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.TextBox txtClass;
        private System.Windows.Forms.Button btnDisplay;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rdoFemale;
        private System.Windows.Forms.RadioButton rdoMale;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox ckbComputer;
        private System.Windows.Forms.CheckBox ckbGame;
        private System.Windows.Forms.CheckBox ckbShop;
        private System.Windows.Forms.CheckBox ckbTravel;
        private System.Windows.Forms.TextBox txtResult;
    }
}

