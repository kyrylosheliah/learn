using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace CSharp_srs2_3
{
	class Program
	{
		static void Main(string[] args)
		{
			string input;
			try
			{
				input = File.ReadAllText("in.txt");
			}
			catch (Exception)
			{
				Console.WriteLine("Ошибка чтения");
				Console.ReadKey();
				return;
			}

			if (!(input.Length == 0))
			{
				Console.WriteLine("Считан текст, " + input.Length + " символов");
				Console.WriteLine("Запуск задачи ...");
				int step;
				if (input.Length >= 2000)
				{
					step = (int)(input.Length / 10) - 1;
				}
				else if (input.Length >= 500)
				{
					step = (int)(input.Length / 5) - 1;
				}
				else
				{
					step = input.Length - 1;
				}
				int sliceIndex = 0;
				var toreturn = new List<CharInt>(64);
				var tasks = new List<Task>(10);
				while (sliceIndex + step < input.Length)
				{
					sliceIndex += step;
					tasks.Add(Task.Factory.StartNew(CountChars, new string_string_ListCharInt(input, toreturn, sliceIndex - step, sliceIndex)));
				}
				if (sliceIndex != input.Length - 1)
				{
					tasks.Add(Task.Factory.StartNew(CountChars, new string_string_ListCharInt(input, toreturn, sliceIndex, input.Length - 1)));
				}
				Task.WaitAll(tasks.ToArray());
				Console.WriteLine("Получены данные задачи:");
				foreach (CharInt item in toreturn.OrderBy(item => item.interger))
				{
					Console.WriteLine("Символ '" + item.character + "', число вхождений [" + item.interger + "]");
				}
			}
			else
			{
				Console.WriteLine("Результат чтения - пусто");
			}
			Console.ReadKey();
		}

		static object locker = new object();
		static void CountChars(object parameter)
		{
			Console.WriteLine("Начало потока " + Thread.CurrentThread.ManagedThreadId);
			var input = (string_string_ListCharInt)parameter;
			int charIndex;
			for (int i = input.from; i < input.to; ++i)
			{
				lock (locker)
				{
					charIndex = input.toreturn.FindIndex(item => item.character == input.data[i]);
					if (charIndex == -1)
					{
						input.toreturn.Add(new CharInt(input.data[i], 1));
					}
					else
					{
						input.toreturn[charIndex].interger += 1;
					}
				}
			}
			Console.WriteLine("Конец потока " + Thread.CurrentThread.ManagedThreadId);
		}
	}

	public class CharInt
	{
		public char character;
		public int interger;
		public CharInt(char ch, int num)
		{
			character = ch;
			interger = num;
		}
	}

	public class string_string_ListCharInt
	{
		public string data { get; }
		public List<CharInt> toreturn;
		public int from;
		public int to;

		public string_string_ListCharInt(string inputData, List<CharInt> outputStructure, int inputFrom, int inputTo)
		{
			data = inputData;
			toreturn = outputStructure;
			from = inputFrom;
			to = inputTo;
		}
	}
}
