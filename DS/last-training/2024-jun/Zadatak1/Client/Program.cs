using Grpc.Net.Client;
using Google.Protobuf.WellKnownTypes; // Za Empty tip
using Server; // Namespace tvojih generisanih proto klasa
using Grpc.Core;

// Glavna metoda mora biti async za gRPC pozive
async Task Main()
{
    Console.WriteLine("========= Welcome ========= ");

    using var channel = GrpcChannel.ForAddress("https://localhost:5270");
    var client = new MessageServiceProto.MessageServiceProtoClient(channel);

    while (true) // Petlja da bi mogao više puta da testiraš
    {
        Console.WriteLine("\n[n] -> New message | [l] -> List all | [d] -> Delete | [e] -> Exit");
        string input = Console.ReadLine()?.ToLower();

        switch (input)
        {
            case "n":
                Console.Write("Enter message content: ");
                string content = Console.ReadLine();
                // Poziv rpc sendMessage(Message) returns (google.protobuf.Empty)
                await client.sendMessageAsync(new Message { Content = content, Id = new MessageId { Val = new Random().Next(1, 1000) } });
                Console.WriteLine("Message sent!");
                break;

            case "l":
                Console.WriteLine("--- Messages from server ---");
                // Poziv rpc listMessages(Empty) returns (stream Message)
                using (var call = client.listMessages(new Empty()))
                {
                    while (await call.ResponseStream.MoveNext())
                    {
                        var msg = call.ResponseStream.Current;
                        Console.WriteLine($"[{msg.Id.Val}] {msg.Content}");
                    }
                }
                break;

            case "d":
                Console.Write("Enter ID to delete: ");
                if (int.TryParse(Console.ReadLine(), out int id))
                {
                    try
                    {
                        // Poziv rpc deleteMessage(MessageId) returns (Message)
                        var deleted = await client.deleteMessageAsync(new MessageId { Val = id });
                        Console.WriteLine($"Deleted: {deleted.Content}");
                    }
                    catch (RpcException ex)
                    {
                        Console.WriteLine($"Error: {ex.Status.Detail}");
                    }
                }
                break;

            case "e":
                return;
        }
    }
}

// Pokretanje
await Main();