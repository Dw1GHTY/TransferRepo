using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace ChatNamespace
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract(CallbackContract = typeof(IChatCallback))]
    public interface IChatService
    {
        [OperationContract(IsOneWay = true)]
        void register(string username);

        [OperationContract(IsOneWay = true)]
        void sendMessage(Message msg, string username);
    }

    [DataContract]
    public class Message 
    {
        string sender, content;
        DateTime dateSent;

        [DataMember]
        public string Sender { get; set; }

        [DataMember]
        public string Content { get; set; }

        [DataMember]
        public DateTime DateSent { get; set; }
    }


    [ServiceContract]
    public interface IChatCallback 
    {
        [OperationContract(IsOneWay = true, Name = "CallbackSendMessage")]
        void sendMessageToReceiver(Message msg);
    }
    
}
