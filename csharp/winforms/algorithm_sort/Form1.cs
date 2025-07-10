using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace CSharp_lab6
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
			toolTip1.ShowAlways = true;
			toolTip1.SetToolTip(label1, "   Створити форму проекту для реалізації алгоритмів:\n- обмінного сортування,\n- сортування вибором,\n- сортування вставками,\n- сортування злиттям(рекурсивний варіант).\n   Додати в проект функцію перевірки впорядкованості і виконати перевірку роботи кожного алгоритму.Передбачити висновок на форму результату перевірки.\n   Для кожного з реалізованих алгоритмів сортування скласти таблицю залежності часу виконання від довжини n впорядковує масиву. (n: 10, 100, 1000, 10000, 100000)");
		}

		private short[] toRndArr;
		private double[] BubbleTime = new double[4];
		private double[] SelectionTime = new double[4];
		private double[] InsertionTime = new double[4];
		private double[] MergeTime = new double[4];
		private void button1_Click(object sender, EventArgs e)
		{
			uint count;
			try
			{
				count = uint.Parse(textBox1.Text);
				label2.Text = "Кол-во эл-тов:";
			}
			catch
			{
				label2.Text = "[!] Невозможно интерпретировать количество элементов";
				return;
			}
			Random rnd = new Random();

			toRndArr = new short[count];
			for (int i = (int)count - 1; i >= 0; --i)
			{
				toRndArr[i] = Convert.ToInt16(rnd.Next(-999, 999));
			}
			richTextBox1.Text = string.Join("\n", toRndArr);
			label2.Text = string.Format("Сгенерировано {0}", count);
		}

		private void sortResultRoutine(ref short[] dataSorted, ref RichTextBox b1, ref RichTextBox b2, ref Label l1, ref Label l2, ref Stopwatch time, ref double[] timeMemory)
		{
			b1.Text = string.Join("\n", dataSorted);
			l1.Text = string.Format("Время: {0} мс", time.Elapsed.TotalMilliseconds);

			bool badSortFlag = false;
			for (int i = 0; i < dataSorted.Length - 1; ++i)
			{
				if (dataSorted[i] > dataSorted[i + 1])
				{
					badSortFlag = true;

					break;
				}
			}
			if (badSortFlag)
			{
				l2.Text = "[!] НЕ ОТСОРТИРОВАНО";
			}
			else
			{
				l2.Text = "Проверка: ОК";
			}

			switch (dataSorted.Length)
			{
				case 10:
					timeMemory[0] = time.Elapsed.TotalMilliseconds;
					break;
				case 100:
					timeMemory[1] = time.Elapsed.TotalMilliseconds;
					break;
				case 1000:
					timeMemory[2] = time.Elapsed.TotalMilliseconds;
					break;
				case 10000:
					timeMemory[3] = time.Elapsed.TotalMilliseconds;
					break;
			}
			switch (dataSorted.Length)
			{
				case 10:
				case 100:
				case 1000:
				case 10000:
					b2.Text = string.Format("10: {0} мс\n100: {1} мс\n1000: {2} мс\n10000: {3} мс\n", timeMemory[0], timeMemory[1], timeMemory[2], timeMemory[3]);
					break;
			}
		}

		private void bubbleSort(ref short[] toSort)
		{
			short temp;
			bool swapped = true;
			for (int i = 0; swapped && i < toSort.Length; ++i)
			{
				swapped = false;
				for (int j = 0; j < toSort.Length - 1; ++j)
				{
					if (toSort[j] > toSort[j + 1])
					{
						temp = toSort[j + 1];
						toSort[j + 1] = toSort[j];
						toSort[j] = temp;
						swapped = true;
					}
				}
			}
		}

		private void selectionSort(ref short[] toSort)
		{
			short temp, smallest;
			for (short i = 0; i < toSort.Length - 1; ++i)
			{
				smallest = i;
				for (short j = (short)(i + 1); j < toSort.Length; ++j)
				{
					if (toSort[j] < toSort[smallest])
					{
						smallest = j;
					}
				}
				temp = toSort[smallest];
				toSort[smallest] = toSort[i];
				toSort[i] = temp;
			}
		}

		private void insertionSort(ref short[] toSort)
		{
			short temp;
			int j;
			for (int i = 1; i <= toSort.Length - 1; ++i)
			{
				temp = toSort[i];
				j = (short)(i - 1);
				while (j >= 0 && toSort[j] > temp)
				{
					toSort[j + 1] = toSort[j];
					j--;
				}
				toSort[j + 1] = temp;
			}
		}

		private void Merge(ref short[] array, int lowIndex, int middleIndex, int highIndex)
		{
			var left = lowIndex;
			var right = middleIndex + 1;
			var tempArray = new int[highIndex - lowIndex + 1];
			var index = 0;
			while ((left <= middleIndex) && (right <= highIndex))
			{
				if (array[left] < array[right])
				{
					tempArray[index] = array[left];
					left++;
				}
				else
				{
					tempArray[index] = array[right];
					right++;
				}
				index++;
			}
			for (var i = left; i <= middleIndex; i++)
			{
				tempArray[index] = array[i];
				index++;
			}
			for (var i = right; i <= highIndex; i++)
			{
				tempArray[index] = array[i];
				index++;
			}
			for (var i = 0; i < tempArray.Length; i++)
			{
				array[lowIndex + i] = (short)tempArray[i];
			}
		}

		private void mergeSort(ref short[] array, int lowIndex, int highIndex)
		{
			if (lowIndex < highIndex)
			{
				var middleIndex = (lowIndex + highIndex) / 2;
				mergeSort(ref array, lowIndex, middleIndex);
				mergeSort(ref array, middleIndex + 1, highIndex);
				Merge(ref array, lowIndex, middleIndex, highIndex);
			}
		}

		private void mergeSort(ref short[] array)
		{
			mergeSort(ref array, 0, array.Length - 1);
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (toRndArr != null)
			{
				short[] toSort = (short[])toRndArr.Clone();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				bubbleSort(ref toSort);
				stopWatch.Stop();
				sortResultRoutine(ref toSort, ref richTextBox2, ref richTextBox6, ref label3, ref label4, ref stopWatch, ref BubbleTime);
			}
			else
			{
				label2.Text = "[!] Bubble";
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			if (toRndArr != null)
			{
				short[] toSort = (short[])toRndArr.Clone();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				selectionSort(ref toSort);
				stopWatch.Stop();
				sortResultRoutine(ref toSort, ref richTextBox3, ref richTextBox7, ref label5, ref label6, ref stopWatch, ref SelectionTime);
			}
			else
			{
				label2.Text = "[!] Bubble";
			}
		}

		private void button4_Click(object sender, EventArgs e)
		{
			if (toRndArr != null)
			{
				short[] toSort = (short[])toRndArr.Clone();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				insertionSort(ref toSort);
				stopWatch.Stop();
				sortResultRoutine(ref toSort, ref richTextBox4, ref richTextBox8, ref label7, ref label8, ref stopWatch, ref InsertionTime);
			}
			else
			{
				label2.Text = "[!] Bubble";
			}
		}

		private void button5_Click(object sender, EventArgs e)
		{
			if (toRndArr != null)
			{
				short[] toSort = (short[])toRndArr.Clone();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				mergeSort(ref toSort);
				stopWatch.Stop();
				sortResultRoutine(ref toSort, ref richTextBox5, ref richTextBox9, ref label9, ref label10, ref stopWatch, ref MergeTime);
			}
			else
			{
				label2.Text = "[!] Bubble";
			}
		}
	}
}
