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
            Console.Title = "Chat Client";
            Console.Write("Enter your username: ");
            string username = Console.ReadLine();

            // Create callback context
            ChatCallback callback = new ChatCallback();
            InstanceContext context = new InstanceContext(callback);

            // Create client proxy
            ChatServiceClient client = new ChatServiceClient(context);

            // Register user
            client.register(username);
            Console.WriteLine("Registered successfully!");

            // Send messages to others
            while (true)
            {
                Console.Write("Send to: ");
                string receiver = Console.ReadLine();

                Console.Write("Message: ");
                string text = Console.ReadLine();

                var message = new Message
                {
                    Sender = username,
                    Content = text,
                    DateSent = DateTime.Now
                };

                client.sendMessage(message, receiver);
            }
        }

        internal class Callback : IChatServiceCallback
        {
            public void sendMessageToReceiver(Message msg)
            {
                Console.WriteLine("New message from " + msg.Sender + ": \n" + msg.Content + "\n at: " + msg.DateSent);
            }
        }
    }


    
}
