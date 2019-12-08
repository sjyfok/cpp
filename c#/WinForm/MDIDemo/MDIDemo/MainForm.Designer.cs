namespace MDIDemo
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新建NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关闭CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.窗口WToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.垂直平铺VToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.层叠CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.水平平铺HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.全部关闭LToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件FToolStripMenuItem,
            this.窗口WToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.MdiWindowListItem = this.窗口WToolStripMenuItem;
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件FToolStripMenuItem
            // 
            this.文件FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建NToolStripMenuItem,
            this.关闭CToolStripMenuItem});
            this.文件FToolStripMenuItem.Name = "文件FToolStripMenuItem";
            this.文件FToolStripMenuItem.Size = new System.Drawing.Size(58, 21);
            this.文件FToolStripMenuItem.Text = "文件(F)";
            // 
            // 新建NToolStripMenuItem
            // 
            this.新建NToolStripMenuItem.Name = "新建NToolStripMenuItem";
            this.新建NToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.新建NToolStripMenuItem.Text = "新建(N)";
            this.新建NToolStripMenuItem.Click += new System.EventHandler(this.newNToolStripMenuItem_Click);
            // 
            // 关闭CToolStripMenuItem
            // 
            this.关闭CToolStripMenuItem.Name = "关闭CToolStripMenuItem";
            this.关闭CToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.关闭CToolStripMenuItem.Text = "关闭(C)";
            // 
            // 窗口WToolStripMenuItem
            // 
            this.窗口WToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.垂直平铺VToolStripMenuItem,
            this.层叠CToolStripMenuItem,
            this.水平平铺HToolStripMenuItem,
            this.全部关闭LToolStripMenuItem});
            this.窗口WToolStripMenuItem.Name = "窗口WToolStripMenuItem";
            this.窗口WToolStripMenuItem.Size = new System.Drawing.Size(64, 21);
            this.窗口WToolStripMenuItem.Text = "窗口(W)";
            // 
            // 垂直平铺VToolStripMenuItem
            // 
            this.垂直平铺VToolStripMenuItem.Name = "垂直平铺VToolStripMenuItem";
            this.垂直平铺VToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.垂直平铺VToolStripMenuItem.Text = "垂直平铺(V)";
            this.垂直平铺VToolStripMenuItem.Click += new System.EventHandler(this.vlayoutVToolStripMenuItem_Click);
            // 
            // 层叠CToolStripMenuItem
            // 
            this.层叠CToolStripMenuItem.Name = "层叠CToolStripMenuItem";
            this.层叠CToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.层叠CToolStripMenuItem.Text = "层叠(C)";
            this.层叠CToolStripMenuItem.Click += new System.EventHandler(this.CascadeCToolStripMenuItem_Click);
            // 
            // 水平平铺HToolStripMenuItem
            // 
            this.水平平铺HToolStripMenuItem.Name = "水平平铺HToolStripMenuItem";
            this.水平平铺HToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.水平平铺HToolStripMenuItem.Text = "水平平铺(H)";
            this.水平平铺HToolStripMenuItem.Click += new System.EventHandler(this.hlayoutHToolStripMenuItem_Click);
            // 
            // 全部关闭LToolStripMenuItem
            // 
            this.全部关闭LToolStripMenuItem.Name = "全部关闭LToolStripMenuItem";
            this.全部关闭LToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.全部关闭LToolStripMenuItem.Text = "全部关闭(L）";
            this.全部关闭LToolStripMenuItem.Click += new System.EventHandler(this.closeallLToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "多文档记事本";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新建NToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关闭CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 窗口WToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 垂直平铺VToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 层叠CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 水平平铺HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 全部关闭LToolStripMenuItem;
    }
}

