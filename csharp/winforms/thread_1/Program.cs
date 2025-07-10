using System;
using System.Collections.Generic;
using System.Threading;
using System.Diagnostics;

namespace CSharp_lab12
{
	class Program
	{

		static void Main(string[] args)
		{
			Action<object> delegateFunction = ItemCount;
			int count = 3;
			List<Thread> threads = new List<Thread>(count);
			Stopwatch stopWatch = new Stopwatch();
			stopWatch.Start();
			for (int i = 0; i < count; ++i)
			{
				threads.Add(new Thread(new ParameterizedThreadStart(delegateFunction)));
				threads[threads.Count - 1].Start(i + 1);
			}
			for (int i = 0; i < count; ++i)
			{
				threads[i].Join();
			}
			stopWatch.Stop();
			Console.WriteLine($"\nМногопоточное выполнение. Время: {stopWatch.Elapsed.TotalMilliseconds} мс\n");

			stopWatch.Reset();
			stopWatch.Start();
			for (int i = 0; i < count; ++i)
			{
				ItemCount(i + 1);
			}
			stopWatch.Stop();
			Console.WriteLine($"\nОднопоточное выполнение. Время: {stopWatch.Elapsed.TotalMilliseconds} мс\n");

			Console.ReadKey();
		}

		static void ItemCount(object order)
		{
			Console.WriteLine($"{(int)order} поток {{{Thread.CurrentThread.ManagedThreadId}}}: Начало выполнения ...");
			int[,,] data = new int[100, 1000, 1000];
			int count = 0;
			Random rand = new Random((new Random()).Next(int.MinValue, int.MaxValue));
			Console.WriteLine($"{(int)order} поток {{{Thread.CurrentThread.ManagedThreadId}}}: Инициализация элементов массива ...");
			for (int i = 0; i < data.GetLength(0); ++i)
			{
				for (int j = 0; j < data.GetLength(1); ++j)
				{
					for (int k = 0; k < data.GetLength(2); ++k)
					{
						data[i, j, k] = rand.Next(int.MinValue, int.MaxValue);
					}
				}
			}
			Console.WriteLine($"{(int)order} поток {{{Thread.CurrentThread.ManagedThreadId}}}: Подсчет количества элементов массива ...");
			foreach (var item in data)
			{
				++count;
			}
			Console.WriteLine($"{(int)order} поток {{{Thread.CurrentThread.ManagedThreadId}}}: Количество элементов - {count} ...");
			Console.WriteLine($"{(int)order} поток {{{Thread.CurrentThread.ManagedThreadId}}}: Конец выполнения");
		}

	}
}
