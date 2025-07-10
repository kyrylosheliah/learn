using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Numerics;
using System.IO;

namespace CSharp_lab3
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private uint[] ranks_from_base1_to_base2(ref uint[] number_ranks, uint base_from, uint base_to)
		{
			if (base_from > 1 & base_to > 1 & Convert.ToBoolean(number_ranks.Length))
			{
				uint number_decimal_value = 0;
				Array.Reverse(number_ranks);
				for (int i = 0; i < number_ranks.Length; ++i)
				{
					number_decimal_value += number_ranks[i] * (uint)Math.Pow(base_from, i);
				}

				var result = new List<uint>();
				uint rank = number_decimal_value / base_to, remainder = number_decimal_value % base_to;

				while (Convert.ToBoolean(rank >= 1))
				{
					result.Insert(0, remainder);
					remainder = rank % base_to;
					rank /= base_to;
				}
				result.Insert(0, remainder);

				uint[] toreturn = new uint[result.Count];
				for (int i = result.Count - 1; i >= 0; --i)
				{
					toreturn[i] = result[i];
				}
				return toreturn;
			}
			return null;
		}

		private void button1_Click(object sender, EventArgs e)
		{
			string[] data2 = textBox1.Text.Split(' ');
			uint[] data1 = new uint[data2.Length];
			uint base_from = 0, base_to = 0;
			try
			{
				base_from = uint.Parse(textBox2.Text);
				base_to = uint.Parse(textBox3.Text);
				for (int i = data2.Length - 1; i >= 0; --i)
				{
					data1[i] = uint.Parse(data2[i]);
					if (data1[i] >= base_from)
					{
						throw new Exception(string.Format("\n[?] значение разряда {0} элемента >= его основания", i+1));
					}
				}
			}
			catch (Exception except)
			{
				richTextBox1.Text += string.Format("\n[!] ОШИБКА интерпретации чисел {0}\n", except.Message);
				return;
			}
			richTextBox1.Text += "\n\tИнициирован перевод числа с разрядами:\n";
			foreach (uint rank in data1)
			{
				richTextBox1.Text += rank + " ";
			}
			uint[] result = ranks_from_base1_to_base2(ref data1, base_from, base_to);
			richTextBox1.Text += string.Format("\nОт основания {0} к основанию {1}\nРезультат:\n", base_from, base_to);
			if (result == null)
			{
				richTextBox1.Text += "[!] ОШИБКА результат пуст";
			} 
			else
			{
				foreach (uint rank in result)
				{
					richTextBox1.Text += Convert.ToString(rank) + " ";
				}
			}
			richTextBox1.Text += "\n";
		}

		private void button2_Click(object sender, EventArgs e)
		{
			richTextBox2.Text = "";
			try
			{
				richTextBox2.Text = File.ReadAllText(@"IN.txt");
			}
			catch
			{
				richTextBox2.Text = "ОШИБКА чтения";
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			if (task_3_2_data == null)
			{
				richTextBox3.Text += string.Format("\n[!] ОШИБКА массив не заполнен\n");
			}
			else
			{
				var sum = task_3_2_data.Aggregate((temp, x) => temp + x);
				richTextBox3.Text += string.Format("\n\tСумма элементов равна {0}\n", sum);
			}
		}

		private void button4_Click(object sender, EventArgs e)
		{
			if (task_3_2_data == null)
			{
				richTextBox3.Text += string.Format("\n[!] ОШИБКА массив не заполнен\n");
			}
			else
			{
				int minValue = task_3_2_data.Min();
				int minPosition = Array.IndexOf(task_3_2_data, minValue) + 1;
				richTextBox3.Text += string.Format("\n\tМинимальный элемент - позиция {0}, значение {1}\n", minPosition, minValue);
			}
		}

		private void button5_Click(object sender, EventArgs e)
		{
			if (task_3_2_data == null)
			{
				richTextBox3.Text += string.Format("\n[!] ОШИБКА массив не заполнен\n");
			}
			else
			{
				int maxValue = task_3_2_data.Max();
				int maxPosition = Array.IndexOf(task_3_2_data, maxValue) + 1;
				richTextBox3.Text += string.Format("\n\tМаксимальный элемент - позиция {0}, значение {1}\n", maxPosition, maxValue);
			}
		}

		private int[] task_3_2_data = null;

		private void button6_Click(object sender, EventArgs e)
		{
			string[] raw_data = richTextBox2.Text.Split(' ');
			task_3_2_data = new int[raw_data.Length];
			try
			{
				label6.Text = "";
				for (int i = 0; i < raw_data.Length; ++i)
				{
					task_3_2_data[i] = int.Parse(raw_data[i]);
					label6.Text += raw_data[i] + ", ";
				}
			}
			catch
			{
				label6.Text = "___";
				richTextBox3.Text += string.Format("\n[!] ОШИБКА интерпретации чисел\n");
				return;
			}
		}

	}
}
