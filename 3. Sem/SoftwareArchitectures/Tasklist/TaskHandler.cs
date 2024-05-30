using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tasklist
{
    class TaskHandler
    {
        private List<Task> TaskList = new();
        private readonly string ListOwner;
        private const int Min = 0;
        private const int Max = 100;
        public TaskHandler(string name)
        {
            ListOwner = name;
        }
        public void Hello()
        {
            Console.WriteLine($"\n\nTaskList by {ListOwner}\n");
            //dummy tasks
            Task dummy1 = new("Einkaufen", "Nach der FH zum Billa einkaufen fahren!", 50, DateTime.Parse("1.10.2021"));
            Task dummy2 = new("Lernen", "Erste Abgabe für Softwarearchitekturen fertigstellen", 75, DateTime.Parse("5.10.2021"));
            TaskList.Add(dummy1);
            TaskList.Add(dummy2);
            //dummy tasks
        }
        public void AddTask()
        {
            Console.Clear();
            Console.Write("Please enter a TaskName: ");
            string name = Console.ReadLine();
            Console.Write("Please enter a Description: ");
            string text = Console.ReadLine();
            Console.Write("Please enter a Priority (0 - 100): ");
            try
            {
                uint num = Convert.ToUInt32(Console.ReadLine());
                if (num < Min || num > Max)
                {
                    Console.WriteLine("\nError: Please enter a valid Integer (0 - 100)!\n");
                    return;
                }
                Console.Write("In how many Days is the Task due?: ");
                uint days = Convert.ToUInt32(Console.ReadLine());
                DateTime due = DateTime.Today.AddDays(days);
                var TempTask = new Task(name, text, num, due);
                Console.WriteLine();
                TaskList.Add(TempTask);
                Console.WriteLine("\nTask successfully added!\n");
            }
            catch (FormatException)
            {
                Console.Clear();
                Console.WriteLine("\nError: Please enter an Integer!\n");
            }
            catch (OverflowException)
            {
                Console.Clear();
                Console.WriteLine("\nError: Please enter a valid Integer!\n");
            }
        }
        public void Display()
        {
            int i = 1;
            if (IsEmpty(TaskList))
            {
                Console.Clear();
                Console.WriteLine();
                Console.WriteLine("The List is Empty!\n");
                return;
            }
            Console.Clear();
            foreach (Task task in TaskList)
            {
                Console.WriteLine();
                Console.WriteLine($"Task {i}");
                Console.Write("Name: ");
                Console.Write(task.TaskName + "\n");
                Console.Write("Description: ");
                Console.Write(task.TaskText + "\n");
                Console.Write("Priority: ");
                Console.Write(task.Priority + "\n");
                Console.Write("DueDate: ");
                Console.Write(task.DueDate.ToLongDateString() + "\n");
                Console.WriteLine();
                i++;
            }
        }
        public void Delete()
        {
            int count = TaskList.Count;
            Console.Clear();
            Display();
            if (count == Min)
            {
                return;
            }
            Console.Write("Which Task would You like to Delete?: ");
            try
            {
                int del = Convert.ToInt32(Console.ReadLine());
                if (del < 1 || del > count)
                {
                    Console.WriteLine("\nError: Please enter a valid Integer!\n");
                    return;
                }
                TaskList.RemoveAt(del - 1);
                Console.WriteLine("\nTask successfully removed!\n");
            }
            catch (FormatException)
            {
                Console.Clear();
                Console.WriteLine("\nError: Please enter an Integer!\n");
            }
        }
        public void Update()
        {
            int count = TaskList.Count;
            Console.Clear();
            Display();
            if (IsEmpty(TaskList))
            {
                return;
            }
            Console.Write("Which Task would You like to Update?: ");
            try
            {
                int update = Convert.ToInt32(Console.ReadLine());
                if (update < 1 || update > count)
                {
                    Console.WriteLine("\nError: Please enter a valid Integer!\n");
                    return;
                }
                Console.Write("Please enter a TaskName: ");
                string name = Console.ReadLine();
                Console.Write("Please enter a Description: ");
                string text = Console.ReadLine();
                Console.Write("Please enter a Priority (0 - 100): ");
                uint num = Convert.ToUInt32(Console.ReadLine());
                if (num < Min || num > Max)
                {
                    Console.WriteLine("\nError: Please enter a valid Integer (0 - 100)!\n");
                    return;
                }
                Console.Write("In how many Days is the Task due?: ");
                uint days = Convert.ToUInt32(Console.ReadLine());
                DateTime due = DateTime.Today.AddDays(days);
                var TempTask = new Task(name, text, num, due);
                TaskList[update - 1] = TempTask;
                Console.WriteLine("\nTask successfully updated!\n");
            }
            catch (FormatException)
            {
                Console.Clear();
                Console.WriteLine("\nError: Please enter an Integer!\n");
            }
            catch (OverflowException)
            {
                Console.Clear();
                Console.WriteLine("\nError: Please enter a valid Integer!\n");
            }
        }
        public void Filter()
        {
            Console.Clear();
            if (IsEmpty(TaskList))
            {
                Console.Clear();
                Console.WriteLine();
                Console.WriteLine("The List is Empty!\n");
                return;
            }
            int input = ToolBox.GetFilterMenu();
            if (input == -1)
            {
                return;
            }
            if (input == 1)
            {
                TaskList = TaskList.OrderByDescending(x => x.Priority).ToList();
                Console.WriteLine("\nTasklist Ordered!\n");
            }
            if (input == 2)
            {
                TaskList = TaskList.OrderBy(x => x.DueDate).ToList();
                Console.WriteLine("\nTasklist Ordered!\n");
            }
            if (input == 3)
            {
                DisplayExpiredTasks();
            }
        }
        private void DisplayExpiredTasks()
        {
            int i = 1;
            if (IsEmpty(TaskList))
            {
                Console.Clear();
                Console.WriteLine();
                Console.WriteLine("The List is Empty!\n");
                return;
            }
            foreach (Task task in TaskList) if (task.DueDate <= DateTime.Today)
                {
                    Console.WriteLine();
                    Console.WriteLine($"Task {i}");
                    Console.Write("Name: ");
                    Console.Write(task.TaskName + "\n");
                    Console.Write("Description: ");
                    Console.Write(task.TaskText + "\n");
                    Console.Write("Priority: ");
                    Console.Write(task.Priority + "\n");
                    Console.Write("DueDate: ");
                    Console.Write(task.DueDate.ToLongDateString() + "\n");
                    i++;
                }
            Console.WriteLine("\n");
        }
        private static bool IsEmpty(List<Task> taskList)
        {
            if (taskList.Any())
            {
                return false;
            }
            return true;
        }
    }
}