using Google.Protobuf.WellKnownTypes;
using Grpc.Core;

namespace Server.Services
{
    public class MessageService : Server.MessageServiceProto.MessageServiceProtoBase
    {
        public List<Message> messagesList;

        public MessageService()
        {
            this.messagesList = new List<Message>();
        }

        public override Task<Empty> sendMessage(Message newMessage, ServerCallContext context)
        {
            this.messagesList.Add(newMessage);

            return Task.FromResult(new Empty());
        }

        public override Task<Message> deleteMessage(MessageId msgId, ServerCallContext context)
        {
            Message msgToDelete = messagesList.FirstOrDefault<Message>(msg => msg.Id.Val == msgId.Val);

            if (msgToDelete == null)
            {
                throw new RpcException(new Status(StatusCode.NotFound, $"Message with ID {msgId.Val} not found"));
            }
            this.messagesList.Remove(msgToDelete);

            return Task.FromResult(new Message { Id = msgToDelete.Id, Content = msgToDelete.Content });

        }

        public override async Task listMessages(Empty request, IServerStreamWriter<Message> outputStream ,ServerCallContext context) 
        {
            foreach (Message msg in messagesList) 
            {
                await outputStream.WriteAsync(new Message { Content = msg.Content });
            }
        }

    }
}
