using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace CSharp_srs1_5_2
{
	public partial class Form2 : Form
	{
		public Form2()
		{
			InitializeComponent();
		}

		private void Form2_Load(object sender, EventArgs e)
		{
			GraphicsPath myPath = new GraphicsPath();
			myPath.AddPolygon(new Point[] {
				new Point(0, Height/2),
				new Point(Width/2, 0),
				new Point(Width, Height/2),
				new Point(Width/2, Height)
			});
			Region myRegion = new Region(myPath);
			Region = myRegion;
		}

		private Point downPoint = Point.Empty;

		private void Form2_DoubleClick(object sender, EventArgs e)
		{
			Close();
		}

		private void Form2_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				downPoint = new Point(e.X, e.Y);
			}
		}

		private void Form2_MouseMove(object sender, MouseEventArgs e)
		{
			if (downPoint != Point.Empty)
			{
				Location = new Point(Left + e.X - downPoint.X, Top + e.Y - downPoint.Y);
			}
		}

		private void Form2_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				downPoint = Point.Empty;
			}
		}
	}
}
