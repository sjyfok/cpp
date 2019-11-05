using System;
using System.Windows.Forms;
using System.Reflection;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using Microsoft.Win32;
using System.Diagnostics;

using ICIDECode.Core;

namespace ICIDECode.Develop.Gui
{
    public partial class AboutSharpDevelopTabPage : UserControl
    {
        Label buildLabel = new Label();
        TextBox buildTextBox = new TextBox();

        Label versionLabel = new Label();
        TextBox versionTextBox = new TextBox();

        Label sponsorLabel = new Label();
        TextBox versionInfoTextBox = new TextBox();

        public AboutSharpDevelopTabPage()
        {
            versionTextBox.Text = "1.0.0";//RevisionClass.Major + "." + RevisionClass.Minor + "." + RevisionClass.Build;
            buildTextBox.Text = "1.0.0";//RevisionClass.Revision;


            versionLabel.Location = new System.Drawing.Point(8, 8);
            versionLabel.Text = ResourceService.GetString("Dialog.About.label1Text");
            versionLabel.Size = new System.Drawing.Size(64, 16);
            versionLabel.TabIndex = 1;
            Controls.Add(versionLabel);

            versionTextBox.Location = new System.Drawing.Point(64 + 8 + 4, 8);
            versionTextBox.ReadOnly = true;
            versionTextBox.TabIndex = 4;
            versionTextBox.Size = new System.Drawing.Size(48, 20);
            Controls.Add(versionTextBox);

            buildLabel.Location = new System.Drawing.Point(64 + 12 + 48 + 4, 8);
            buildLabel.Text = ResourceService.GetString("Dialog.About.label2Text");
            buildLabel.Size = new System.Drawing.Size(48, 16);
            buildLabel.TabIndex = 2;
            Controls.Add(buildLabel);

            buildTextBox.Location = new System.Drawing.Point(64 + 12 + 48 + 4 + 48 + 4, 8);
            buildTextBox.ReadOnly = true;
            buildTextBox.TabIndex = 3;
            buildTextBox.Size = new System.Drawing.Size(72, 20);
            Controls.Add(buildTextBox);

            sponsorLabel.Location = new System.Drawing.Point(8, 34);
            sponsorLabel.Text = LicenseSentence;
            sponsorLabel.Size = new System.Drawing.Size(362, 24);
            sponsorLabel.TabIndex = 8;
            Controls.Add(sponsorLabel);

            versionInfoTextBox.Location = new System.Drawing.Point(8, 34 + 28);
            versionInfoTextBox.Size = new System.Drawing.Size(362, 100);
            versionInfoTextBox.Multiline = true;
            versionInfoTextBox.ReadOnly = true;
            versionInfoTextBox.WordWrap = false;
            versionInfoTextBox.Text = GetVersionInformationString();
            versionInfoTextBox.ScrollBars = ScrollBars.Both;
            versionInfoTextBox.TabIndex = 9;
            versionInfoTextBox.Font = SD.WinForms.LoadFont("Courier New", 8);
            versionInfoTextBox.KeyDown += new KeyEventHandler(versionInfoTextBox_KeyDown);
            versionInfoTextBox.RightToLeft = RightToLeft.No;
            Controls.Add(versionInfoTextBox);

            Dock = DockStyle.Fill;
        }

        void versionInfoTextBox_KeyDown(object sender, KeyEventArgs e)
        {
#if DEBUG
            if (e.KeyData == (Keys.Control | Keys.Shift | Keys.E))
            {
                throw new ClownFishException();
            }
            else if (e.KeyData == (Keys.Control | Keys.Shift | Keys.A))
            {
                Trace.Fail("Trace failure");
            }
            else if (e.KeyData == (Keys.Control | Keys.Shift | Keys.G))
            {
                GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced);
                GC.WaitForPendingFinalizers();
                GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced);
                versionInfoTextBox.Text = GetVersionInformationString();
            }
#endif
        }

        [Serializable]
        class ClownFishException : Exception { }

        [SuppressMessage("Microsoft.Design", "CA1031:DoNotCatchGeneralExceptionTypes")]
        public static string GetVersionInformationString()
        {
            string str = "";
            object[] attr = typeof(AboutSharpDevelopTabPage).Assembly.GetCustomAttributes(typeof(AssemblyInformationalVersionAttribute), false);
            if (attr.Length == 1)
            {
                AssemblyInformationalVersionAttribute aiva = (AssemblyInformationalVersionAttribute)attr[0];
                str += "SharpDevelop Version : " + aiva.InformationalVersion + Environment.NewLine;
            }
            try
            {
                string version = null;
                using (var key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full"))
                {
                    if (key != null)
                        version = key.GetValue("Version") as string;
                }
                if (string.IsNullOrWhiteSpace(version))
                    version = Environment.Version.ToString();
                str += ".NET Version         : " + version + Environment.NewLine;
            }
            catch { }
            str += "OS Version           : " + Environment.OSVersion.ToString() + Environment.NewLine;
            string cultureName = null;
            try
            {
                cultureName = CultureInfo.CurrentCulture.Name;
                str += "Current culture      : " + CultureInfo.CurrentCulture.EnglishName + " (" + cultureName + ")" + Environment.NewLine;
            }
            catch { }
            try
            {
                if (cultureName == null || !cultureName.StartsWith(ResourceService.Language, StringComparison.Ordinal))
                {
                    str += "Current UI language  : " + ResourceService.Language + Environment.NewLine;
                }
            }
            catch { }
            try
            {
                if (IntPtr.Size != 4)
                {
                    str += "Running as " + (IntPtr.Size * 8) + " bit process" + Environment.NewLine;
                }
                string PROCESSOR_ARCHITEW6432 = Environment.GetEnvironmentVariable("PROCESSOR_ARCHITEW6432");
                if (!string.IsNullOrEmpty(PROCESSOR_ARCHITEW6432))
                {
                    if (PROCESSOR_ARCHITEW6432 == "AMD64")
                        PROCESSOR_ARCHITEW6432 = "x86-64";
                    str += "Running under WOW6432, processor architecture: " + PROCESSOR_ARCHITEW6432 + Environment.NewLine;
                }
            }
            catch { }
            try
            {
                if (SystemInformation.TerminalServerSession)
                {
                    str += "Terminal Server Session" + Environment.NewLine;
                }
                if (SystemInformation.BootMode != BootMode.Normal)
                {
                    str += "Boot Mode            : " + SystemInformation.BootMode + Environment.NewLine;
                }
            }
            catch { }
            str += "Working Set Memory   : " + (Environment.WorkingSet / 1024) + "kb" + Environment.NewLine;
            str += "GC Heap Memory       : " + (GC.GetTotalMemory(false) / 1024) + "kb" + Environment.NewLine;
            return str;
        }

        public static string LicenseSentence
        {
            get
            {
                return StringParser.Parse("${res:Dialog.About.License}",
                                          new StringTagPair("License", "MIT License"));
            }
        }
    }
}
