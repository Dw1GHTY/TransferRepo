using Client.ServiceReference1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    internal class Program
    {
        public Callback cb;
        static void Main(string[] args)
        {
            ICalculatorServiceCallback cb = new Callback();
            CalculatorServiceClient client = new CalculatorServiceClient(new InstanceContext(cb));

            float number = 0.0f;
            string inputNumber = string.Empty;
            string operation = null;

            while (operation != "x") 
            {
                Console.WriteLine("Enter operation: ");
                operation = Console.ReadLine();

                Console.WriteLine("Enter value: ");
                inputNumber = Console.ReadLine();
                float.TryParse(inputNumber, out number);

                switch (operation)
                {
                    case "+":
                        client.add(number);
                        break;
                    case "-":
                        client.subtract(number);
                        break;
                    case "*":
                        client.multiply(number);
                        break;
                    case "/":
                        client.divide(number);
                        break;
                    case "c":
                        client.clearState();
                        break;
                    default:
                        break;
                }
                operation = string.Empty;
                inputNumber = string.Empty;
                number = 0.0f;
                Console.WriteLine("\n==================");
            }


        }


        
        
    }

    public class Callback : ICalculatorServiceCallback {

        public Callback() { }

        public void notifyUser(float result, string currentState) {
            Console.WriteLine("========= Callback =========");
            Console.WriteLine("Current state: " + currentState);
            Console.WriteLine("Current result: " + result);
        }
    
    }

}
