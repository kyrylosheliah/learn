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
	public partial class ParentForm : Form
	{
		public ParentForm()
		{
			InitializeComponent();
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void cascadeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			LayoutMdi(MdiLayout.Cascade);
		}

		private void tileToolStripMenuItem_Click(object sender, EventArgs e)
		{
			LayoutMdi(MdiLayout.TileHorizontal);
		}

		private int openedDocumentsCounter = 0;

		private void newToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ChildForm newChild = new ChildForm();
			newChild.MdiParent = this;
			newChild.Text = newChild.Text + " " + ++openedDocumentsCounter;
			newChild.Show();
		}
	}
}
