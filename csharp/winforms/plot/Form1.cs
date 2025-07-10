using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace CSharp_lab5
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();

			graphics = pictureBox1.CreateGraphics();
			pen = new Pen(Color.Black, 3f);

			var column1 = new DataGridViewColumn
			{
				HeaderText = "x, аргумент",
				Width = 192,
				CellTemplate = new DataGridViewTextBoxCell()
			};
			var column2 = new DataGridViewColumn
			{
				HeaderText = "y, функция",
				Width = 192,
				CellTemplate = new DataGridViewTextBoxCell()
			};
			dataGridView1.Columns.Add(column1);
			dataGridView1.Columns.Add(column2);
		}

		private Graphics graphics;
		private Pen pen;
		private double from, to, step, argument, sum;

		private void button3_Click(object sender, EventArgs e)
		{
			try
			{
				graphics.Clear(Color.White);
				Point[] points = new Point[lastPointsLoaded.Count];
				double x_range = Math.Abs(lastPointsLoaded.Max(x => x.Item1) - lastPointsLoaded.Min(x => x.Item1));
				double y_range = Math.Abs(lastPointsLoaded.Max(x => x.Item2) - lastPointsLoaded.Min(x => x.Item2));
				for (int i = 0; i < lastPointsLoaded.Count; ++i)
				{
					//(int)((lastPointsLoaded[i].Item1 + (x_range / 2)) / x_range * pictureBox1.Width)
					points[i] = new Point((int)((double)i / lastPointsLoaded.Count * pictureBox1.Width), (int)((lastPointsLoaded[i].Item2 + (y_range / 2)) / y_range * pictureBox1.Height));
				}
				graphics.DrawLines(pen, points);
				richTextBox1.Text += "\nГрафик построен\n";
				label7.Text = "График построен";

				//points = new Point[pictureBox1.Height];
				//for (int i = 0; i < pictureBox1.Height; ++i)
				//{
				//	points[i] = new Point(i, i);
				//}
				//graphics.DrawLines(pen, points);
			}
			catch
			{
				richTextBox1.Text += "\n[!] ОШИБКА построения графика\n";
				label7.Text = "[!] ОШИБКА построения графика";
			}
		}

		private void button2_Click(object sender, EventArgs e)
		{
			try
			{
				string[] tempList = File.ReadAllLines(@"IN.txt");
				if (tempList.Length == 0) { throw new Exception(); }
				string[] tempTuple = new string[2];
				lastPointsLoaded = new List<Tuple<double, double>>(tempList.Length);
				richTextBox1.Text += "\n\tНачало чтения IN.txt\n";
				foreach(string item in tempList)
				{
					tempTuple = item.Split(' ');
					richTextBox1.Text += string.Format("x = {0}; y = {1}\n", tempTuple[0], tempTuple[1]);
					lastPointsLoaded.Add(new Tuple<double, double>(double.Parse(tempTuple[0]), double.Parse(tempTuple[1])));
				}
				lastPointsLoaded = lastPointsLoaded.OrderBy(point => point.Item1).ToList();
				dataGridView1.Rows.Clear();
				for (int i = 0; i < lastPointsLoaded.Count; ++i)
				{
					dataGridView1.Rows.Add(lastPointsLoaded[i].Item1, lastPointsLoaded[i].Item2);
				}
				richTextBox1.Text += "\tIN.txt прочитан\n";
				label6.Text = "IN.txt прочитан";
			}
			catch
			{
				richTextBox1.Text += "[!] ОШИБКА чтения\n";
				label6.Text = "[!] ОШИБКА чтения";
			}
		}

		private uint number;
		private List<Tuple<double, double>> lastPointsLoaded;

		private async void button1_Click(object sender, EventArgs e)
		{
			try
			{
				double[] raw = { Double.Parse(textBox1.Text), Double.Parse(textBox2.Text) };
				number = uint.Parse(textBox3.Text);
				if (number < 2) { throw new Exception(); }
				from = raw.Min();
				to = raw.Max();
			}
			catch
			{
				richTextBox1.Text += "\n[!] Ошибка интерпретации значения аргументов\n";
				label5.Text = "\n[!] Ошибка входных значений\n";
				return;
			}
			
			argument = from;
			if (number > pictureBox1.Width) {
				number = (uint)pictureBox1.Width;
				richTextBox1.Text += "\nКоличество точек слишком велико и было изменено на значение ширины холста графика\n";
			}
			step = (to - from) / (number - 1);
			lastPointsLoaded = new List<Tuple<double, double>>((int)number);
			richTextBox1.Text += string.Format("\tНачало вычисления функции\nС аргументами от {0} до {1} в {2} точках с шагом {3}", from, to, number, step);
			for (int i = 0; (i < number) & (argument <= to); ++i)
			{
				sum = 0;
				for (int j = 1; j <= 10; ++j)
				{
					sum += 1 / (j * Math.Pow(argument, j));
				}
				lastPointsLoaded.Add(new Tuple<double, double>(argument, sum));
				richTextBox1.Text += string.Format("\nx={0}; f(x)={1}", argument, sum);
				argument += step;
			}
			richTextBox1.Text += "\n\tКонец вычисления функции\nРезультат записан в IN.txt и в локальную переменную\n\n";

			try
			{
				using (StreamWriter sw = new StreamWriter(@"IN.txt", true, Encoding.Default))
				{
					string[] towrite = new string[lastPointsLoaded.Count];
					for (int i = 0; i < lastPointsLoaded.Count; ++i)
					{
						towrite[i] = string.Format("{0} {1}", lastPointsLoaded[i].Item1, lastPointsLoaded[i].Item2);
					}
					await sw.WriteLineAsync(string.Join("\n", towrite));
				}
				label5.Text = "IN.txt записан";
			}
			catch
			{
				label5.Text = "[!] ОШИБКА записи";
			}
		}
	}
}
