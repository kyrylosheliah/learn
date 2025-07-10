using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSarp_srs1_mdi
{
	public partial class ChildForm : Form
	{
		public ChildForm()
		{
			InitializeComponent();
		}

		private void toggleForegroundToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (toggleForegroundToolStripMenuItem.Checked)
			{
				toggleForegroundToolStripMenuItem.Checked = false;
				richTextBox1.ForeColor = System.Drawing.Color.Black;
			}
			else
			{
				toggleForegroundToolStripMenuItem.Checked = true;
				richTextBox1.ForeColor = System.Drawing.Color.Blue;
			}
		}
	}
}
