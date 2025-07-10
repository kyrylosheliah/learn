using System;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace CSharp_lab7
{

	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private ArrayList arrayListPrevious = new ArrayList();
		private ArrayList arrayListCurrent = new ArrayList();
		private int element;

		private int parseUserElement()
		{
			try { return int.Parse(textBox1.Text); }
			catch { return int.MinValue; }
		}

		private void arrayListMemorize()
		{
			arrayListPrevious = (ArrayList)arrayListCurrent.Clone();
		}

		private string arrayListToString(ref ArrayList data, bool fromHead = true)
		{
			if (data.Count != 0)
			{
				string toReturn = "";
				string[] toJoin = new string[data.Count];
				int i = 0;
				foreach (int obj in data)
				{
					toJoin[i] = obj.ToString();
					++i;
				}
				if (fromHead)
				{
					toReturn = string.Join("\n", toJoin);
				}
				else
				{
					Array.Reverse(toJoin);
					toReturn = string.Join("\n", toJoin);
				}
				return toReturn;
			}
			else { return ""; }
		}

		private void arrayListUpdate()
		{
			richTextBox1.Text = arrayListToString(ref arrayListCurrent, true);
			richTextBox2.Text = arrayListToString(ref arrayListCurrent, false);
			richTextBox3.Text = arrayListToString(ref arrayListPrevious, true);
			richTextBox4.Text = arrayListToString(ref arrayListPrevious, false);
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if ((element = parseUserElement()) != int.MinValue)
			{
				arrayListMemorize();
				arrayListCurrent.Insert(0, element);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "Ошибка считывания";
			}
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if ((element = parseUserElement()) != int.MinValue)
			{
				arrayListMemorize();
				arrayListCurrent.Add(element);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "Ошибка считывания";
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			if ((element = parseUserElement()) != int.MinValue)
			{
				arrayListMemorize();
				
				if (arrayListCurrent.Count > 1)
				{
					int index = -1;
					int prev = (int)arrayListCurrent[0];
					if (element < prev)
					{
						index = 0;
					}
					else
					{
						for (int i = 1; i < arrayListCurrent.Count; ++i)
						{
							if (prev > (int)arrayListCurrent[i] || element < (int)arrayListCurrent[i])
							{
								index = i;
								break;
							}
							prev = (int)arrayListCurrent[i];
						}
					}
					if (index == -1)
					{
						arrayListCurrent.Add(element);
					}
					else
					{
						arrayListCurrent.Insert(index, element);
					}
				}
				else if (arrayListCurrent.Count == 1)
				{
					if (element > (int)arrayListCurrent[0])
					{
						arrayListCurrent.Add(element);
					}
					else
					{
						arrayListCurrent.Insert(0, element);
					}
				}
				else
				{
					arrayListCurrent.Add(element);
				}
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Ошибка считывания";
			}
		}

		private void button8_Click(object sender, EventArgs e)
		{
			if (arrayListCurrent.Count != 0)
			{
				arrayListMemorize();
				arrayListCurrent.RemoveAt(0);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Удалять нечего";
			}
		}

		private void button9_Click(object sender, EventArgs e)
		{
			if (arrayListCurrent.Count != 0)
			{
				arrayListMemorize();
				arrayListCurrent.RemoveAt(arrayListCurrent.Count - 1);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Удалять нечего";
			}
		}

		private void button10_Click(object sender, EventArgs e)
		{
			arrayListMemorize();
			arrayListCurrent.Clear();
			arrayListUpdate();
		}







		private void bubbleSort(ref ArrayList toSort)
		{
			int temp;
			bool swapped = true;
			for (int i = 0; swapped && i < toSort.Count; ++i)
			{
				swapped = false;
				for (int j = 0; j < toSort.Count - 1; ++j)
				{
					if ((int)toSort[j] > (int)toSort[j + 1])
					{
						temp = (int)toSort[j + 1];
						toSort[j + 1] = toSort[j];
						toSort[j] = temp;
						swapped = true;
					}
				}
			}
		}

		private void selectionSort(ref ArrayList toSort)
		{
			int temp, smallest;
			for (short i = 0; i < toSort.Count - 1; ++i)
			{
				smallest = i;
				for (short j = (short)(i + 1); j < toSort.Count; ++j)
				{
					if ((int)toSort[j] < (int)toSort[smallest])
					{
						smallest = j;
					}
				}
				temp = (int)toSort[smallest];
				toSort[smallest] = toSort[i];
				toSort[i] = temp;
			}
		}

		private void insertionSort(ref ArrayList toSort)
		{
			int temp, j;
			for (int i = 1; i <= toSort.Count - 1; ++i)
			{
				temp = (int)toSort[i];
				j = (short)(i - 1);
				while (j >= 0 && (int)toSort[j] > temp)
				{
					toSort[j + 1] = toSort[j];
					j--;
				}
				toSort[j + 1] = temp;
			}
		}

		private void Merge(ref ArrayList array, int lowIndex, int middleIndex, int highIndex)
		{
			int left = lowIndex;
			int right = middleIndex + 1;
			int[] tempArray = new int[highIndex - lowIndex + 1];
			int index = 0;
			while ((left <= middleIndex) && (right <= highIndex))
			{
				if ((int)array[left] < (int)array[right])
				{
					tempArray[index] = (int)array[left];
					left++;
				}
				else
				{
					tempArray[index] = (int)array[right];
					right++;
				}
				index++;
			}
			for (var i = left; i <= middleIndex; i++)
			{
				tempArray[index] = (int)array[i];
				index++;
			}
			for (var i = right; i <= highIndex; i++)
			{
				tempArray[index] = (int)array[i];
				index++;
			}
			for (var i = 0; i < tempArray.Length; i++)
			{
				array[lowIndex + i] = (int)tempArray[i];
			}
		}

		private void mergeSort(ref ArrayList array, int lowIndex, int highIndex)
		{
			if (lowIndex < highIndex)
			{
				var middleIndex = (lowIndex + highIndex) / 2;
				mergeSort(ref array, lowIndex, middleIndex);
				mergeSort(ref array, middleIndex + 1, highIndex);
				Merge(ref array, lowIndex, middleIndex, highIndex);
			}
		}

		private void mergeSort(ref ArrayList array)
		{
			mergeSort(ref array, 0, array.Count - 1);
		}



		private void sortResultRoutine(ref ArrayList dataSorted, ref Label lTime, ref Label lTest, ref Stopwatch swTime)
		{
			lTime.Text = string.Format("Время: {0} мс", swTime.Elapsed.TotalMilliseconds);

			bool badSortFlag = false;
			for (int i = 0; i < dataSorted.Count - 1; ++i)
			{
				if ((int)dataSorted[i] > (int)dataSorted[i + 1])
				{
					badSortFlag = true;

					break;
				}
			}
			if (badSortFlag)
			{
				lTest.Text = "[!] НЕ ОТСОРТИРОВАНО";
			}
			else
			{
				lTest.Text = "Проверка: ОК";
			}
		}


		private void button4_Click(object sender, EventArgs e)
		{
			if (arrayListCurrent.Count != 0)
			{
				arrayListMemorize();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				bubbleSort(ref arrayListCurrent);
				stopWatch.Stop();
				arrayListUpdate();
				sortResultRoutine(ref arrayListCurrent, ref label2, ref label3, ref stopWatch);
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Сортировать нечего";
			}
		}

		private void button5_Click(object sender, EventArgs e)
		{
			if (arrayListCurrent.Count != 0)
			{
				arrayListMemorize();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				selectionSort(ref arrayListCurrent);
				stopWatch.Stop();
				arrayListUpdate();
				sortResultRoutine(ref arrayListCurrent, ref label2, ref label3, ref stopWatch);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Сортировать нечего";
			}
		}

		private void button6_Click(object sender, EventArgs e)
		{
			if (arrayListCurrent.Count != 0)
			{
				arrayListMemorize();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				insertionSort(ref arrayListCurrent);
				stopWatch.Stop();
				arrayListUpdate();
				sortResultRoutine(ref arrayListCurrent, ref label2, ref label3, ref stopWatch);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Сортировать нечего";
			}
		}

		private void button7_Click(object sender, EventArgs e)
		{
			if (arrayListCurrent.Count != 0)
			{
				arrayListMemorize();
				Stopwatch stopWatch = new Stopwatch();
				stopWatch.Start();
				mergeSort(ref arrayListCurrent);
				stopWatch.Stop();
				arrayListUpdate();
				sortResultRoutine(ref arrayListCurrent, ref label2, ref label3, ref stopWatch);
				arrayListUpdate();
				label8.Text = "________________";
			}
			else
			{
				label8.Text = "[!] Сортировать нечего";
			}
		}
	}
}
