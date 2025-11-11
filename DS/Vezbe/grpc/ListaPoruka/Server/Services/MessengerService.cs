using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using MessengerNamespace;
using System.IO;
namespace Server.Services
{
    public class MessengerService : MessengerNamespace.MessengerService.MessengerServiceBase
    {
        
        public Task<Empty> addMessage(Message newMessage, ServerCallContext context) 
        {
            Database db = Database.Instance();
            db.messagesList.Add(newMessage);

            return Task.FromResult(new Empty());
        }

        public Task<Empty> deleteMessage(MessageId messageId, ServerCallContext context) 
        {
            Database db = Database.Instance();
            var messageToDelete = db.messagesList.Find(m => m.MessageId == messageId.MessageId_);

            if (messageToDelete != null) 
            {
                db.messagesList.Remove(messageToDelete);
                return Task.FromResult(new Empty());
            }
            return Task.FromResult(new Empty());
        }


        public async Task listMessages(Empty empty, IServerStreamWriter<Message> outputStream, ServerCallContext context) 
        {
            Database db = Database.Instance();
            foreach (Message message in db.messagesList) 
            {
                await outputStream.WriteAsync(new Message() 
                {
                    MessageId = message.MessageId,
                    MessageContent = message.MessageContent,
                });
            }
        }
    }
}
