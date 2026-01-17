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
            IChatServiceCallback callback = new Callback();
            InstanceContext context = new InstanceContext(callback);
            ServiceReference1.ChatServiceClient client = new ServiceReference1.ChatServiceClient(context);
        }
    }


    public class Callback : ServiceReference1.IChatServiceCallback
    {
        public void notifyReceiver(ChatMessage msg) 
        {
            Console.WriteLine(msg.Sender);
            Console.WriteLine(msg.Content);
            Console.WriteLine(msg.Timestamp.ToString());
        }
    }
}
