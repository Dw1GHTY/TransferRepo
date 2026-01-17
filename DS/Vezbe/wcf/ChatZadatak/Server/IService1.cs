using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{

    [ServiceContract(CallbackContract = typeof(IChatCallback))]
    public interface IChatService
    {
        [OperationContract(IsOneWay = true)]
        void sendMessage(Message msg, string to);

        [OperationContract(IsOneWay = true)]
        void register(string username);

    }

    [ServiceContract]
    public interface IChatCallback 
    {
        [OperationContract(IsOneWay = true, Name = "CallbackNotifyReceiver")]
        void notifyReceiver(Message msg);
    }

    [DataContract]
    public class Message
    {
        string from, content;
        DateTime timestamp;


        [DataMember]
        public string From { get; set; }

        [DataMember]
        public string Content { get; set; } 

        [DataMember]
        public DateTime Timestamp { get; set; }

    }
}
