using System;

namespace Tasklist
{
    class Program
    {
        static void Main()
        {
            var taskHandler = new TaskHandler(ToolBox.Welcome());
            taskHandler.Hello();
            while (true)
            {
                int MyInput = ToolBox.GetMenu();
                switch (MyInput)
                {
                    case 1:
                        taskHandler.AddTask();
                        break;
                    case 2:
                        taskHandler.Update();
                        break;
                    case 3:
                        taskHandler.Display();
                        break;
                    case 4:
                        taskHandler.Delete();
                        break;
                    case 5:
                        taskHandler.Filter();
                        break;
                    case 6:
                        return;
                    default:
                        ToolBox.WrongNumber();
                        break;
                }
            }
        }
    }
}