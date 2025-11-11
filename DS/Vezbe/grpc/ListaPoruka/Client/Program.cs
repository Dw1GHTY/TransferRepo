using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Grpc.Net.Client;
using MessengerNamespace;
using System.Threading.Tasks;

async Task<int> main() 
{
    using var channel = GrpcChannel.ForAddress("http://localhost:5189");
    var client = new MessengerService.MessengerServiceClient(channel);

    Console.WriteLine("\nAdding messages...");
    client.addMessage(new Message { MessageId = 1, MessageContent = "Hello from client!" });
    client.addMessage(new Message { MessageId = 1, MessageContent = "Whats the wather like!" });
    client.addMessage(new Message { MessageId = 1, MessageContent = "Im an americaan" });

    Console.WriteLine("\nListing all messages:");
    using (var call = client.listMessages(new Empty()))

    {
        await foreach (var msg in call.ResponseStream.ReadAllAsync()) 
        {
            Console.WriteLine($"ID: {msg.MessageId}, Content: {msg.MessageContent}");
        }
    }


    Console.ReadLine();

        return 0;
}

await main();