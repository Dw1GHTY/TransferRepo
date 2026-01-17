using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract(CallbackContract = typeof(IChatCallback))]
    public interface IChatService
    {
        [OperationContract(IsOneWay = true)]
        void register(string username);

        [OperationContract(IsOneWay = true)]
        void sendMessage(string toUser, string message);
    }


    [DataContract]
    public class ChatMessage 
    {

        [DataMember]
        public string Sender { get; set; }
        [DataMember]
        public DateTime Timestamp { get; set; }
        [DataMember]
        public string Content { get; set; }
    }

    [ServiceContract]
    public interface IChatCallback 
    {
        [OperationContract(IsOneWay = true, Name = "CallbackNotifyReceiver")]
        void notifyReceiver(ChatMessage msg);
    }



    
}
