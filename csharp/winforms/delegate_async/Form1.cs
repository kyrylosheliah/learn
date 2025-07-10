using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace CSharp_lab11_testtt
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
			int[] range =  Enumerable.Range(1, 100).ToArray();
			string[] stringRange = new string[range.Length];
			for (int i = 0; i < range.Length; i++)
			{
				stringRange[i] = range[i].ToString();
			}
			comboBox1.Items.AddRange(stringRange);
			comboBox2.Items.AddRange(stringRange);
			comboBox3.Items.Add("делимые");
			comboBox3.Items.Add("четные");
			comboBox3.Items.Add("нечетные");
			comboBox3.Items.Add("больше");
			comboBox3.Items.Add("меньше");
			comboBox3.SelectedIndex = 0;
		}

		public delegate int[] IntArray___IntArray_Int(List<int> data, int what);

		public int[] dividers(List<int> data, int what)
		{
			var toreturn = new List<int>(data.Count / 2 + 1);
			foreach (var number in data)
			{
				if (number % what == 0)
				{
					toreturn.Add(number);
				}
			}
			return toreturn.ToArray();
		}

		public int[] even(List<int> data, int what)
		{
			var toreturn = new List<int>(data.Count / 2 + 1);
			foreach (var number in data)
			{
				if (number % 2 == 0)
				{
					toreturn.Add(number);
				}
			}
			return toreturn.ToArray();
		}

		public int[] odd(List<int> data, int what)
		{
			var toreturn = new List<int>(data.Count / 2 + 1);
			foreach (var number in data)
			{
				if (number % 2 != 0)
				{
					toreturn.Add(number);
				}
			}
			return toreturn.ToArray();
		}

		public int[] greater(List<int> data, int what)
		{
			var toreturn = new List<int>(data.Count / 2 + 1);
			foreach (var number in data)
			{
				if (number > what)
				{
					toreturn.Add(number);
				}
			}
			return toreturn.ToArray();
		}

		public int[] less(List<int> data, int what)
		{
			var toreturn = new List<int>(data.Count / 2 + 1);
			foreach (var number in data)
			{
				if (number < what)
				{
					toreturn.Add(number);
				}
			}
			return toreturn.ToArray();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			int count = 0;
			int number = 0;
			IntArray___IntArray_Int execute = dividers;

			try
			{
				count = int.Parse((string)comboBox1.SelectedItem);
				number = int.Parse((string)comboBox2.SelectedItem);
				switch ((string)comboBox3.SelectedItem)
				{
					case "делимые":
						execute = dividers;
						break;
					case "четные":
						execute = even;
						break;
					case "нечетные":
						execute = odd;
						break;
					case "больше":
						execute = greater;
						break;
					case "меньше":
						execute = less;
						break;
					default:
						return;
				}
			}
			catch
			{
				richTextBox1.Text += $"\n########################\n#Ошибка входных параметров#\n########################\n";
				return;
			}

			Stopwatch stopWatch = new Stopwatch();
			Random rand = new Random();
			rand.Next(DateTime.Now.Millisecond);

			var data = new List<List<int>>(count);
			for (int i = 0; i < count; ++i)
			{
				data.Add(new List<int>(count*count));
				for (int j = count*count - 1; j >= 0; --j)
				{
					data[i].Add(rand.Next(DateTime.Now.Millisecond));
				}
			}

			richTextBox1.Text += "\n######################";
			richTextBox1.Text += $"\nСинхронный вызов метода на {count} задач: \n";
			stopWatch.Start();
			for (int i = 0; i < count; i++)
			{
				richTextBox1.Text += $"[{i}]Result: {execute(data[i], number).Length}\n";
			}
			stopWatch.Stop();
			richTextBox1.Text += $"Время: {stopWatch.Elapsed.TotalMilliseconds} мс\n";

			var result = new List<IAsyncResult>(count);
			richTextBox1.Text += $"\nАсинхронный вызов метода с {count} задачами: \n";
			stopWatch.Reset();
			stopWatch.Start();
			for (int i = 0; i < count; i++)
			{
				result.Add(execute.BeginInvoke(data[i], number, null, null));
			}
			stopWatch.Stop();
			int iterator = 0;
			foreach (var returned in result)
			{
				richTextBox1.Text += $"[{iterator}]Result: {execute.EndInvoke(returned).Length}\n";
			}
			richTextBox1.Text += $"Время: {stopWatch.Elapsed.TotalMilliseconds} мс\n";
			
		}

		private void button2_Click(object sender, EventArgs e)
		{
			richTextBox1.Text = "";
		}

		private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch ((string)comboBox3.SelectedItem)
			{
				case "четные":
				case "нечетные":
					comboBox2.Visible = false;
					comboBox2.SelectedIndex = 0;
					break;
				case "делимые":
				case "больше":
				case "меньше":
					comboBox2.Visible = true;
					break;
			}
		}
	}
}
