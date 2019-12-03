namespace mine
{
    partial class MainForm
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
            this.btnTest = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.游戏GToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.开局NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.初级BToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.中级IToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.高级EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.自定义CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.标记MToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.颜色LToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.声音SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.扫雷英雄榜TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.退出XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.使用帮助HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.关于扫雷AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnTest
            // 
            this.btnTest.Location = new System.Drawing.Point(12, 65);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(68, 28);
            this.btnTest.TabIndex = 0;
            this.btnTest.Text = "test";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.游戏GToolStripMenuItem,
            this.帮助HToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(431, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 游戏GToolStripMenuItem
            // 
            this.游戏GToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.开局NToolStripMenuItem,
            this.toolStripSeparator1,
            this.初级BToolStripMenuItem,
            this.中级IToolStripMenuItem,
            this.高级EToolStripMenuItem,
            this.自定义CToolStripMenuItem,
            this.toolStripSeparator2,
            this.标记MToolStripMenuItem,
            this.颜色LToolStripMenuItem,
            this.声音SToolStripMenuItem,
            this.toolStripSeparator3,
            this.扫雷英雄榜TToolStripMenuItem,
            this.toolStripSeparator4,
            this.退出XToolStripMenuItem});
            this.游戏GToolStripMenuItem.Name = "游戏GToolStripMenuItem";
            this.游戏GToolStripMenuItem.Size = new System.Drawing.Size(61, 21);
            this.游戏GToolStripMenuItem.Text = "游戏(&G)";
            // 
            // 开局NToolStripMenuItem
            // 
            this.开局NToolStripMenuItem.Name = "开局NToolStripMenuItem";
            this.开局NToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.开局NToolStripMenuItem.Text = "开局(&N)";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(177, 6);
            // 
            // 初级BToolStripMenuItem
            // 
            this.初级BToolStripMenuItem.Name = "初级BToolStripMenuItem";
            this.初级BToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.初级BToolStripMenuItem.Text = "初级(&B)";
            // 
            // 中级IToolStripMenuItem
            // 
            this.中级IToolStripMenuItem.Name = "中级IToolStripMenuItem";
            this.中级IToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.中级IToolStripMenuItem.Text = "中级(&I)";
            this.中级IToolStripMenuItem.Click += new System.EventHandler(this.secondery_ToolStripMenuItem_Click);
            // 
            // 高级EToolStripMenuItem
            // 
            this.高级EToolStripMenuItem.Name = "高级EToolStripMenuItem";
            this.高级EToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.高级EToolStripMenuItem.Text = "高级(&E)";
            // 
            // 自定义CToolStripMenuItem
            // 
            this.自定义CToolStripMenuItem.Name = "自定义CToolStripMenuItem";
            this.自定义CToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.自定义CToolStripMenuItem.Text = "自定义(&C)";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(177, 6);
            // 
            // 标记MToolStripMenuItem
            // 
            this.标记MToolStripMenuItem.Name = "标记MToolStripMenuItem";
            this.标记MToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.标记MToolStripMenuItem.Text = "标记(?)(&M)";
            // 
            // 颜色LToolStripMenuItem
            // 
            this.颜色LToolStripMenuItem.Name = "颜色LToolStripMenuItem";
            this.颜色LToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.颜色LToolStripMenuItem.Text = "颜色(&L)";
            // 
            // 声音SToolStripMenuItem
            // 
            this.声音SToolStripMenuItem.Name = "声音SToolStripMenuItem";
            this.声音SToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.声音SToolStripMenuItem.Text = "声音(&S)";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(177, 6);
            // 
            // 扫雷英雄榜TToolStripMenuItem
            // 
            this.扫雷英雄榜TToolStripMenuItem.Name = "扫雷英雄榜TToolStripMenuItem";
            this.扫雷英雄榜TToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.扫雷英雄榜TToolStripMenuItem.Text = "扫雷英雄榜(&T)";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(177, 6);
            // 
            // 退出XToolStripMenuItem
            // 
            this.退出XToolStripMenuItem.Name = "退出XToolStripMenuItem";
            this.退出XToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.退出XToolStripMenuItem.Text = "退出(&X)";
            // 
            // 帮助HToolStripMenuItem
            // 
            this.帮助HToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.使用帮助HToolStripMenuItem,
            this.toolStripSeparator5,
            this.关于扫雷AToolStripMenuItem});
            this.帮助HToolStripMenuItem.Name = "帮助HToolStripMenuItem";
            this.帮助HToolStripMenuItem.Size = new System.Drawing.Size(61, 21);
            this.帮助HToolStripMenuItem.Text = "帮助(&H)";
            // 
            // 使用帮助HToolStripMenuItem
            // 
            this.使用帮助HToolStripMenuItem.Name = "使用帮助HToolStripMenuItem";
            this.使用帮助HToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.使用帮助HToolStripMenuItem.Text = "使用帮助(&H)";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(138, 6);
            // 
            // 关于扫雷AToolStripMenuItem
            // 
            this.关于扫雷AToolStripMenuItem.Name = "关于扫雷AToolStripMenuItem";
            this.关于扫雷AToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.关于扫雷AToolStripMenuItem.Text = "关于扫雷(&A)";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(431, 322);
            this.Controls.Add(this.btnTest);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnTest;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 游戏GToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 开局NToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 初级BToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 中级IToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 高级EToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 自定义CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 标记MToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 颜色LToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 声音SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 扫雷英雄榜TToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出XToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 使用帮助HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于扫雷AToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
    }
}

