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

namespace CSharp_lab2
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		async private void button2_Click(object sender, EventArgs e)
		{
			label7.Text = "";
			try
			{
				using (StreamWriter sw = new StreamWriter(@"OUT.txt", true, Encoding.Default))
				{
					await sw.WriteLineAsync(string.Format("\n>>> Начало записи {0}\n{1}\n>>> Конец записи {0}", DateTime.Today.ToString(), richTextBox1.Text));
				}
			}
			catch
			{
				label7.Text = "ОШИБКА записи";
			}
		}

		private double from, to, step, argument, sum;

		private void button1_Click(object sender, EventArgs e)
		{
			try
			{
				double[] raw = { Double.Parse(textBox1.Text), Double.Parse(textBox2.Text) };
				from = raw.Min();
				to = raw.Max();
			}
			catch
			{
				richTextBox1.Text += "\n[!] Ошибка интерпретации значения аргументов\n";
				return;
			}

			argument = from;
			step = (to - from) / 10;
			richTextBox1.Text += string.Format("\tНачало вычисления функции\nС аргументами от {0} до {1} в {2} точках с шагом {3}", from, to, 10, step);
			do
			{
				sum = 0;
				for (int i = 1; i <= 10; ++i)
				{
					sum += 1 / (i * Math.Pow(argument, i));
				}
				richTextBox1.Text += string.Format("\nx={0}\t|\tf(x)={1}", argument, sum);

				argument += step;
			} while (argument <= to);
			richTextBox1.Text += "\n\tКонец вычисления функции\n\n";
		}

		private void button3_Click(object sender, EventArgs e)
		{
			richTextBox1.Text = "";
		}
	}
}
