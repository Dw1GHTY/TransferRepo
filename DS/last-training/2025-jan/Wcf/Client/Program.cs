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
        static void Main(string[] args)
        {

            Callback cbHandler = new Callback();
            InstanceContext ctx = new InstanceContext(cbHandler);
            ChatServiceClient client = new ChatServiceClient(ctx);

            Console.WriteLine("=== WCF CHAT CLIENT ===");
            Console.Write("Enter your username: ");
            string username = Console.ReadLine();

            // Registracija na serveru
            client.register(username);
            Console.WriteLine($"Registered as {username}.");

            while (true)
            {
                Console.WriteLine("\nOptions: [m] send message, [q] quit");
                string command = Console.ReadLine()?.ToLower();

                if (command == "q") break;
                if (command == "m")
                {
                    sendMessage(client);
                }
            }

            
            client.Close();
        }


        static void sendMessage(ChatServiceClient client)
        {
            Console.Write("To user: ");
            string to = Console.ReadLine();
            Console.Write("Message: ");
            string text = Console.ReadLine();

            // Pozivamo metodu servisa - server će sam prepoznati ko šalje
            // na osnovu kanala koji je otvoren pri instanciranju klijenta
            client.sendMessage(to, text);
            Console.WriteLine("Message sent!");
        }



    }

    public class Callback : IChatServiceCallback
    {
        public Callback() { }


        public void CallbackNotifyReceiver(ChatMessage msg) 
        {
            Console.WriteLine("\n------------------------------------");
            Console.WriteLine($"NEW MESSAGE from: {msg.Sender}");
            Console.WriteLine($"Content: {msg.Content}");
            Console.WriteLine($"Sent at: {msg.Timestamp}");
            Console.WriteLine("------------------------------------");
        }
    }


}
