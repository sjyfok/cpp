namespace StudentReg
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
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textStudentNum = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textSpecialty = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textPhoneNum = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textZip = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textAddress = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.radioFemale = new System.Windows.Forms.RadioButton();
            this.radioMale = new System.Windows.Forms.RadioButton();
            this.textBirthday = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textIDNumber = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.textStudentName = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.checkProfessional = new System.Windows.Forms.CheckBox();
            this.checkNum = new System.Windows.Forms.CheckBox();
            this.btnRegister = new System.Windows.Forms.Button();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.labRegTime = new System.Windows.Forms.Label();
            this.lsvStudentInfo = new System.Windows.Forms.ListView();
            this.columnNameHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnNumHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnMaleHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnDepartHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnProfessionalHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnClassHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.cboDepartmant = new System.Windows.Forms.ComboBox();
            this.cboProfessional = new System.Windows.Forms.ComboBox();
            this.cboClass = new System.Windows.Forms.ComboBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cboClass);
            this.groupBox1.Controls.Add(this.cboProfessional);
            this.groupBox1.Controls.Add(this.cboDepartmant);
            this.groupBox1.Controls.Add(this.textStudentNum);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(566, 43);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 131);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            // 
            // textStudentNum
            // 
            this.textStudentNum.Location = new System.Drawing.Point(93, 90);
            this.textStudentNum.Name = "textStudentNum";
            this.textStudentNum.Size = new System.Drawing.Size(100, 21);
            this.textStudentNum.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 95);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "学    号";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 71);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "班    级";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "专    业";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "系    部";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textSpecialty);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.textPhoneNum);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.textZip);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.textAddress);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Location = new System.Drawing.Point(300, 43);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 131);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            // 
            // textSpecialty
            // 
            this.textSpecialty.Location = new System.Drawing.Point(93, 90);
            this.textSpecialty.Name = "textSpecialty";
            this.textSpecialty.Size = new System.Drawing.Size(100, 21);
            this.textSpecialty.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 6;
            this.label5.Text = "特    长";
            // 
            // textPhoneNum
            // 
            this.textPhoneNum.Location = new System.Drawing.Point(93, 66);
            this.textPhoneNum.Name = "textPhoneNum";
            this.textPhoneNum.Size = new System.Drawing.Size(100, 21);
            this.textPhoneNum.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 71);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "电    话";
            // 
            // textZip
            // 
            this.textZip.Location = new System.Drawing.Point(93, 42);
            this.textZip.Name = "textZip";
            this.textZip.Size = new System.Drawing.Size(100, 21);
            this.textZip.TabIndex = 3;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 47);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 2;
            this.label7.Text = "邮    编";
            // 
            // textAddress
            // 
            this.textAddress.Location = new System.Drawing.Point(93, 18);
            this.textAddress.Name = "textAddress";
            this.textAddress.Size = new System.Drawing.Size(100, 21);
            this.textAddress.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 23);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "地    址";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.radioFemale);
            this.groupBox3.Controls.Add(this.radioMale);
            this.groupBox3.Controls.Add(this.textBirthday);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.textIDNumber);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.textStudentName);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Location = new System.Drawing.Point(34, 43);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(200, 131);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            // 
            // radioFemale
            // 
            this.radioFemale.AutoSize = true;
            this.radioFemale.Location = new System.Drawing.Point(151, 44);
            this.radioFemale.Name = "radioFemale";
            this.radioFemale.Size = new System.Drawing.Size(35, 16);
            this.radioFemale.TabIndex = 9;
            this.radioFemale.Text = "女";
            this.radioFemale.UseVisualStyleBackColor = true;
            this.radioFemale.CheckedChanged += new System.EventHandler(this.radioFemale_CheckedChanged);
            // 
            // radioMale
            // 
            this.radioMale.AutoSize = true;
            this.radioMale.Checked = true;
            this.radioMale.Location = new System.Drawing.Point(99, 44);
            this.radioMale.Name = "radioMale";
            this.radioMale.Size = new System.Drawing.Size(35, 16);
            this.radioMale.TabIndex = 8;
            this.radioMale.TabStop = true;
            this.radioMale.Text = "男";
            this.radioMale.UseVisualStyleBackColor = true;
            this.radioMale.CheckedChanged += new System.EventHandler(this.radioMale_CheckedChanged);
            // 
            // textBirthday
            // 
            this.textBirthday.Location = new System.Drawing.Point(93, 90);
            this.textBirthday.Name = "textBirthday";
            this.textBirthday.Size = new System.Drawing.Size(100, 21);
            this.textBirthday.TabIndex = 7;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(8, 95);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 12);
            this.label9.TabIndex = 6;
            this.label9.Text = "出生年月";
            // 
            // textIDNumber
            // 
            this.textIDNumber.Location = new System.Drawing.Point(93, 66);
            this.textIDNumber.Name = "textIDNumber";
            this.textIDNumber.Size = new System.Drawing.Size(100, 21);
            this.textIDNumber.TabIndex = 5;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(8, 71);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(53, 12);
            this.label10.TabIndex = 4;
            this.label10.Text = "身份证号";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(8, 47);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(53, 12);
            this.label11.TabIndex = 2;
            this.label11.Text = "性    别";
            // 
            // textStudentName
            // 
            this.textStudentName.Location = new System.Drawing.Point(93, 18);
            this.textStudentName.Name = "textStudentName";
            this.textStudentName.Size = new System.Drawing.Size(100, 21);
            this.textStudentName.TabIndex = 1;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(8, 23);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 12);
            this.label12.TabIndex = 0;
            this.label12.Text = "姓    名";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(34, 403);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(53, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "注册时间";
            // 
            // checkProfessional
            // 
            this.checkProfessional.AutoSize = true;
            this.checkProfessional.Checked = true;
            this.checkProfessional.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkProfessional.Location = new System.Drawing.Point(265, 404);
            this.checkProfessional.Name = "checkProfessional";
            this.checkProfessional.Size = new System.Drawing.Size(72, 16);
            this.checkProfessional.TabIndex = 6;
            this.checkProfessional.Text = "显示专业";
            this.checkProfessional.UseVisualStyleBackColor = true;
            this.checkProfessional.CheckedChanged += new System.EventHandler(this.checkProfessional_CheckedChanged);
            // 
            // checkNum
            // 
            this.checkNum.AutoSize = true;
            this.checkNum.Checked = true;
            this.checkNum.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkNum.Location = new System.Drawing.Point(357, 404);
            this.checkNum.Name = "checkNum";
            this.checkNum.Size = new System.Drawing.Size(72, 16);
            this.checkNum.TabIndex = 7;
            this.checkNum.Text = "显示学号";
            this.checkNum.UseVisualStyleBackColor = true;
            this.checkNum.CheckedChanged += new System.EventHandler(this.checkNum_CheckedChanged);
            // 
            // btnRegister
            // 
            this.btnRegister.Location = new System.Drawing.Point(524, 404);
            this.btnRegister.Name = "btnRegister";
            this.btnRegister.Size = new System.Drawing.Size(75, 23);
            this.btnRegister.TabIndex = 8;
            this.btnRegister.Text = "注册";
            this.btnRegister.UseVisualStyleBackColor = true;
            this.btnRegister.Click += new System.EventHandler(this.btnRegister_Click);
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.dateTimePicker1.Location = new System.Drawing.Point(103, 426);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(205, 21);
            this.dateTimePicker1.TabIndex = 9;
            this.dateTimePicker1.Visible = false;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // labRegTime
            // 
            this.labRegTime.AutoSize = true;
            this.labRegTime.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.labRegTime.Location = new System.Drawing.Point(107, 403);
            this.labRegTime.Name = "labRegTime";
            this.labRegTime.Size = new System.Drawing.Size(2, 14);
            this.labRegTime.TabIndex = 10;
            // 
            // lsvStudentInfo
            // 
            this.lsvStudentInfo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnNameHeader,
            this.columnNumHeader,
            this.columnMaleHeader,
            this.columnDepartHeader,
            this.columnProfessionalHeader,
            this.columnClassHeader});
            this.lsvStudentInfo.Location = new System.Drawing.Point(34, 194);
            this.lsvStudentInfo.Name = "lsvStudentInfo";
            this.lsvStudentInfo.Size = new System.Drawing.Size(725, 171);
            this.lsvStudentInfo.TabIndex = 0;
            this.lsvStudentInfo.UseCompatibleStateImageBehavior = false;
            this.lsvStudentInfo.View = System.Windows.Forms.View.Details;
            // 
            // columnNameHeader
            // 
            this.columnNameHeader.Text = "姓    名";
            this.columnNameHeader.Width = 120;
            // 
            // columnNumHeader
            // 
            this.columnNumHeader.Text = "学    号";
            this.columnNumHeader.Width = 120;
            // 
            // columnMaleHeader
            // 
            this.columnMaleHeader.Text = "性    别";
            this.columnMaleHeader.Width = 120;
            // 
            // columnDepartHeader
            // 
            this.columnDepartHeader.Text = "院    系";
            this.columnDepartHeader.Width = 120;
            // 
            // columnProfessionalHeader
            // 
            this.columnProfessionalHeader.Text = "专    业";
            this.columnProfessionalHeader.Width = 120;
            // 
            // columnClassHeader
            // 
            this.columnClassHeader.Text = "班    级";
            this.columnClassHeader.Width = 120;
            // 
            // cboDepartmant
            // 
            this.cboDepartmant.FormattingEnabled = true;
            this.cboDepartmant.Location = new System.Drawing.Point(93, 18);
            this.cboDepartmant.Name = "cboDepartmant";
            this.cboDepartmant.Size = new System.Drawing.Size(100, 20);
            this.cboDepartmant.TabIndex = 8;
            // 
            // cboProfessional
            // 
            this.cboProfessional.FormattingEnabled = true;
            this.cboProfessional.Location = new System.Drawing.Point(93, 42);
            this.cboProfessional.Name = "cboProfessional";
            this.cboProfessional.Size = new System.Drawing.Size(100, 20);
            this.cboProfessional.TabIndex = 9;
            // 
            // cboClass
            // 
            this.cboClass.FormattingEnabled = true;
            this.cboClass.Location = new System.Drawing.Point(93, 66);
            this.cboClass.Name = "cboClass";
            this.cboClass.Size = new System.Drawing.Size(100, 20);
            this.cboClass.TabIndex = 10;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.lsvStudentInfo);
            this.Controls.Add(this.labRegTime);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.btnRegister);
            this.Controls.Add(this.checkNum);
            this.Controls.Add(this.checkProfessional);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "学生注册";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textStudentNum;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textSpecialty;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textPhoneNum;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textZip;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textAddress;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBirthday;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textIDNumber;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textStudentName;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.RadioButton radioFemale;
        private System.Windows.Forms.RadioButton radioMale;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.CheckBox checkProfessional;
        private System.Windows.Forms.CheckBox checkNum;
        private System.Windows.Forms.Button btnRegister;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label labRegTime;
        private System.Windows.Forms.ListView lsvStudentInfo;
        private System.Windows.Forms.ColumnHeader columnNumHeader;
        private System.Windows.Forms.ColumnHeader columnMaleHeader;
        private System.Windows.Forms.ColumnHeader columnDepartHeader;
        private System.Windows.Forms.ColumnHeader columnProfessionalHeader;
        private System.Windows.Forms.ColumnHeader columnClassHeader;
        private System.Windows.Forms.ColumnHeader columnNameHeader;
        private System.Windows.Forms.ComboBox cboClass;
        private System.Windows.Forms.ComboBox cboProfessional;
        private System.Windows.Forms.ComboBox cboDepartmant;
    }
}

