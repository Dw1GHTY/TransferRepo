
using Grpc.Core;
using Google.Protobuf.WellKnownTypes;
using MessagingService;
using MessagingService.Services;

public class MessageQueueService : MessagingService.MessageQueueService.MessageQueueServiceBase
{

    public override Task<Empty> SendMessage(Message message, ServerCallContext context) 
    {
        DatabaseService db = DatabaseService.getInstance();
        db.AddMessage(message);

        return Task.FromResult(new Empty());
    }

    public override Task<Message> DeleteMessage(Id id, ServerCallContext context) 
    {
        DatabaseService db = DatabaseService.getInstance();
        Message msgToDelete = db.FindMessage(id);

        if (msgToDelete != null) 
        {
            db.De
            return Task.FromResult(msgToDelete);
        }
    }

}

