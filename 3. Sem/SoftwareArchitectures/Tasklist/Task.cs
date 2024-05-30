using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tasklist
{
    class Task
    {
        public string TaskName { get; set; }
        public string TaskText { get; set; }
        public uint Priority { get; set; }
        public DateTime DueDate { get; set; }
        public Task(string name, string text, uint num, DateTime date)
        {
            TaskName = name;
            TaskText = text;
            Priority = num;
            DueDate = date;
        }
    }
}