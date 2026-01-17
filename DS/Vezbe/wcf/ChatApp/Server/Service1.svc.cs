using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace ChatNamespace
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class ChatService : IChatService
    {
        private Dictionary<string, IChatCallback> users;


        public ChatService() 
        {
            users = new Dictionary<string, IChatCallback>();
        }

        public void register(string username)
        {
            // ako unese isti username, prethodna sesija je prestala da vazi

            var callback = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            if (users.ContainsKey(username))
            {
                users[username] = callback;
            }
            else 
            {
                users.Add(username, callback);
            }
              
        }

        public void sendMessage(Message msg, string username) 
        {
            if (users.ContainsKey(username)) 
            {
                IChatCallback callback = users[username];
                callback.sendMessageToReceiver(username, msg);
            }
        }
       
    }
}
