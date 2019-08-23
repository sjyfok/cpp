namespace StudentInfo
{
    partial class frmClass
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblClassName = new System.Windows.Forms.Label();
            this.lblUserID = new System.Windows.Forms.Label();
            this.lstClass = new System.Windows.Forms.ListBox();
            this.cboUser = new System.Windows.Forms.ComboBox();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnDel = new System.Windows.Forms.Button();
            this.btnSeach = new System.Windows.Forms.Button();
            this.btnModify = new System.Windows.Forms.Button();
            this.btnStatistics = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.lblClassNum = new System.Windows.Forms.Label();
            this.txtClassName = new System.Windows.Forms.TextBox();
            this.txtClassCount = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // lblClassName
            // 
            this.lblClassName.AutoSize = true;
            this.lblClassName.Location = new System.Drawing.Point(24, 13);
            this.lblClassName.Name = "lblClassName";
            this.lblClassName.Size = new System.Drawing.Size(29, 12);
            this.lblClassName.TabIndex = 0;
            this.lblClassName.Text = "班名";
            // 
            // lblUserID
            // 
            this.lblUserID.AutoSize = true;
            this.lblUserID.Location = new System.Drawing.Point(206, 13);
            this.lblUserID.Name = "lblUserID";
            this.lblUserID.Size = new System.Drawing.Size(77, 12);
            this.lblUserID.TabIndex = 1;
            this.lblUserID.Text = "选择用户身份";
            // 
            // lstClass
            // 
            this.lstClass.FormattingEnabled = true;
            this.lstClass.ItemHeight = 12;
            this.lstClass.Location = new System.Drawing.Point(51, 86);
            this.lstClass.Name = "lstClass";
            this.lstClass.Size = new System.Drawing.Size(120, 124);
            this.lstClass.TabIndex = 2;
            // 
            // cboUser
            // 
            this.cboUser.FormattingEnabled = true;
            this.cboUser.Location = new System.Drawing.Point(312, 10);
            this.cboUser.Name = "cboUser";
            this.cboUser.Size = new System.Drawing.Size(121, 20);
            this.cboUser.TabIndex = 3;
            this.cboUser.SelectedIndexChanged += new System.EventHandler(this.cboUser_SelectedIndexChanged);
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(208, 84);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(75, 23);
            this.btnAdd.TabIndex = 4;
            this.btnAdd.Text = "添加";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnDel
            // 
            this.btnDel.Location = new System.Drawing.Point(349, 84);
            this.btnDel.Name = "btnDel";
            this.btnDel.Size = new System.Drawing.Size(75, 23);
            this.btnDel.TabIndex = 5;
            this.btnDel.Text = "删除";
            this.btnDel.UseVisualStyleBackColor = true;
            this.btnDel.Click += new System.EventHandler(this.btnDel_Click);
            // 
            // btnSeach
            // 
            this.btnSeach.Location = new System.Drawing.Point(208, 130);
            this.btnSeach.Name = "btnSeach";
            this.btnSeach.Size = new System.Drawing.Size(75, 23);
            this.btnSeach.TabIndex = 6;
            this.btnSeach.Text = "查找";
            this.btnSeach.UseVisualStyleBackColor = true;
            this.btnSeach.Click += new System.EventHandler(this.btnSeach_Click);
            // 
            // btnModify
            // 
            this.btnModify.Location = new System.Drawing.Point(349, 129);
            this.btnModify.Name = "btnModify";
            this.btnModify.Size = new System.Drawing.Size(75, 23);
            this.btnModify.TabIndex = 7;
            this.btnModify.Text = "修改";
            this.btnModify.UseVisualStyleBackColor = true;
            this.btnModify.Click += new System.EventHandler(this.btnModify_Click);
            // 
            // btnStatistics
            // 
            this.btnStatistics.Location = new System.Drawing.Point(208, 187);
            this.btnStatistics.Name = "btnStatistics";
            this.btnStatistics.Size = new System.Drawing.Size(75, 23);
            this.btnStatistics.TabIndex = 8;
            this.btnStatistics.Text = "统计";
            this.btnStatistics.UseVisualStyleBackColor = true;
            this.btnStatistics.Click += new System.EventHandler(this.btnStatistics_Click);
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(349, 186);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 9;
            this.btnClear.Text = "清空";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // lblClassNum
            // 
            this.lblClassNum.AutoSize = true;
            this.lblClassNum.Location = new System.Drawing.Point(206, 248);
            this.lblClassNum.Name = "lblClassNum";
            this.lblClassNum.Size = new System.Drawing.Size(77, 12);
            this.lblClassNum.TabIndex = 10;
            this.lblClassNum.Text = "目前班级数为";
            // 
            // txtClassName
            // 
            this.txtClassName.Location = new System.Drawing.Point(71, 10);
            this.txtClassName.Name = "txtClassName";
            this.txtClassName.Size = new System.Drawing.Size(100, 21);
            this.txtClassName.TabIndex = 11;
            // 
            // txtClassCount
            // 
            this.txtClassCount.Location = new System.Drawing.Point(312, 245);
            this.txtClassCount.Name = "txtClassCount";
            this.txtClassCount.Size = new System.Drawing.Size(100, 21);
            this.txtClassCount.TabIndex = 12;
            // 
            // frmClass
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 282);
            this.Controls.Add(this.txtClassCount);
            this.Controls.Add(this.txtClassName);
            this.Controls.Add(this.lblClassNum);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnStatistics);
            this.Controls.Add(this.btnModify);
            this.Controls.Add(this.btnSeach);
            this.Controls.Add(this.btnDel);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.cboUser);
            this.Controls.Add(this.lstClass);
            this.Controls.Add(this.lblUserID);
            this.Controls.Add(this.lblClassName);
            this.Name = "frmClass";
            this.Text = "班级信息管理";
            this.Load += new System.EventHandler(this.frmClass_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblClassName;
        private System.Windows.Forms.Label lblUserID;
        private System.Windows.Forms.ListBox lstClass;
        private System.Windows.Forms.ComboBox cboUser;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnDel;
        private System.Windows.Forms.Button btnSeach;
        private System.Windows.Forms.Button btnModify;
        private System.Windows.Forms.Button btnStatistics;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Label lblClassNum;
        private System.Windows.Forms.TextBox txtClassName;
        private System.Windows.Forms.TextBox txtClassCount;
    }
}