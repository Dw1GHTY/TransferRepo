using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Service1 : IChatService
    {
        private Dictionary<string, IChatCallback> users;
        public Service1() 
        {
            this.users = new Dictionary<string, IChatCallback>();
        }

        public void register(string username) 
        {
            // ako prosledi isti username => nova sesija => novi callback
            this.users.Add(username, OperationContext.Current.GetCallbackChannel<IChatCallback>());
        }

        public void sendMessage(string toUser, string message) 
        {
            // izvlacenje username-a posiljaoca preko njegovog Callback kanala

            //Callback posiljaoca
            IChatCallback callerCallback = OperationContext.Current.GetCallbackChannel<IChatCallback>();

            string senderUsername = users.FirstOrDefault(x => x.Value == callerCallback).Key;

            ChatMessage msg = new ChatMessage()
            {
                Timestamp = DateTime.Now,
                Content = message,
                Sender = senderUsername
            };

            if (this.users.ContainsKey(toUser))
            {
                IChatCallback receiver = this.users[toUser];
                receiver.notifyReceiver(msg);
            }

        }

    }
}
