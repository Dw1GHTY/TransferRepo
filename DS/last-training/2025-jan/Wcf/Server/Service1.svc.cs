using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{

    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Service1 : IChatService
    {
        public Dictionary<string, IChatCallback> registeredUsers;
        public Service1() 
        {
            this.registeredUsers = new Dictionary<string, IChatCallback>(); 
        }

        public void register(string username) 
        {
            IChatCallback cb = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            this.registeredUsers.Add(username, cb);
        }

        public void sendMessage(string username, string messageContent) 
        {

            string senderUsername = this.registeredUsers.FirstOrDefault(x => x.Key == username).Key;

            ChatMessage message = new ChatMessage()
            {
                Timestamp = DateTime.Now,
                Content = messageContent,
                Sender = senderUsername,
            };


            IChatCallback receiverCb = this.registeredUsers[username];
            receiverCb.notifyReceiver(message);
        }
    }
}
