using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Chat
{
    [ServiceContract]
    public interface IChatService 
    {
        [OperationContract(IsOneWay = true)]
        void SendMessage(string receiverUsername, Message message);
        [OperationContract(IsOneWay = true)]
        void Register(string username);
    }

    [ServiceContract]
    public interface ICallback 
    {
        [OperationContract(IsOneWay = true, Name = "CallbackSendMessage")]
        void SendMessage(Message message);
    }

    [DataContract]
    public class Message
    {
        string text;
        DateTime timestamp;
        string sender;


        [DataMember]
        public string Text {get; set;}

        [DataMember]
        public DateTime Timestamp { get; set; }

        [DataMember]
        public string Sender { get; set; }
    }

}
