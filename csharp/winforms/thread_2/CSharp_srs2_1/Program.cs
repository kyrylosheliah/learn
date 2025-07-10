using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.IO;

namespace CSharp_srs2
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
				var threads = new List<Thread>(10);
				var parameter = new string_string_ListCharInt(input);
				while (sliceIndex + step < input.Length)
				{
					sliceIndex += step;
					threads.Add(new Thread(() =>
					{
						CountChars(parameter, sliceIndex - step, sliceIndex);
					}));
				}
				if (sliceIndex != input.Length - 1)
				{
					threads.Add(new Thread(() =>
					{
						CountChars(parameter, sliceIndex, input.Length - 1);
					}));
				}
				foreach (Thread thread in threads)
				{
					thread.Start();
				}
				foreach (Thread thread in threads)
				{
					thread.Join();
				}
				Console.WriteLine("Получены данные задачи:");
				foreach (CharInt item in parameter.toreturn.OrderBy(item => item.interger))
				{
					Console.WriteLine("Символ '"+ item.character + "', число вхождений ["+ item.interger +"]");
				}
			}
			else
			{
				Console.WriteLine("Результат чтения - пусто");
			}
			Console.ReadKey();
		}

		static object locker = new object();
		static void CountChars(string_string_ListCharInt parameters, int from, int to)
		{
			Console.WriteLine("Начало потока " + Thread.CurrentThread.ManagedThreadId);
			int charIndex;
			for (int i = from; i < to; ++i)
			{
				lock (locker)
				{
					charIndex = parameters.toreturn.FindIndex(item => item.character == parameters.data[i]);
					if (charIndex == -1)
					{
						parameters.toreturn.Add(new CharInt(parameters.data[i], 1));
					}
					else
					{
						parameters.toreturn[charIndex].interger += 1;
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

		public string_string_ListCharInt(string inputData)
		{
			data = inputData;
			toreturn = new List<CharInt>(64);
		}
	}
}
