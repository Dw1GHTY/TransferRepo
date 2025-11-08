
using Grpc.Core;
using Grpc.Net.Client;
using Okt2Proto;
using System.Threading.Tasks;

Console.WriteLine("Hello, World!");


// 1. Setup Channel and Client (as above)
var channel = GrpcChannel.ForAddress("https://localhost:5292");
var client = new Okt2Service.Okt2ServiceClient(channel);

// 2. Start the bidirectional call
using var call = client.IsSquare();

Console.WriteLine("Client stream started...");

// Task 1: Writing (Sending data to the server)
var writeTask = Task.Run(async () =>
{
    // Define the list of messages to send
    var numbersToSend = new List<Numbers>
    {
        new Numbers { A = 2, B = 4 },   // Product 8 (Not square)
        new Numbers { A = 3, B = 3 },   // Product 9 (Is square)
        new Numbers { A = 5, B = 5 },   // Product 25 (Is square)
        new Numbers { A = 4, B = 2 },   // Product 8 (Not square)
    };

    foreach (var num in numbersToSend)
    {
        Console.WriteLine($"Client sending: {num.A} and {num.B}");
        await call.RequestStream.WriteAsync(num);
        await Task.Delay(500); // Wait a moment between sends
    }

    // IMPORTANT: Tell the server we are done sending data
    await call.RequestStream.CompleteAsync();
});


// Task 2: Reading (Receiving data from the server)
var readTask = Task.Run(async () =>
{
    // Await foreach loop to read responses as they arrive
    await foreach (var response in call.ResponseStream.ReadAllAsync())
    {
        Console.WriteLine($"Server response: {response.Message}");
    }
});

// 3. Wait for both tasks to complete
await Task.WhenAll(writeTask, readTask);

Console.WriteLine("Client stream ended.");