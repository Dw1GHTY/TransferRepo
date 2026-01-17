using Client.ServiceReference1;
using System;
using System.ServiceModel;

namespace Client
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // 1. Inicijalizacija je bila dobra - prosleđujemo naš callback serveru
            Callback callbackHandler = new Callback();
            InstanceContext context = new InstanceContext(callbackHandler);
            ChatServiceClient client = new ChatServiceClient(context);

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

    // Implementacija callback interfejsa
    public class Callback : IChatServiceCallback
    {
        public void CallbackNotifyReceiver(ChatMessage msg)
        {
            // Ovo se izvršava asinhrono kada server "gurne" poruku klijentu
            Console.WriteLine("\n------------------------------------");
            Console.WriteLine($"NEW MESSAGE from: {msg.Sender}");
            Console.WriteLine($"Content: {msg.Content}");
            Console.WriteLine($"Sent at: {msg.Timestamp}");
            Console.WriteLine("------------------------------------");
        }
    }
}