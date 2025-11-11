using System;
using System.Threading.Tasks;
using Grpc.Net.Client;
using Lab1Namespace; // iz tvoje generisane .proto klase
using Google.Protobuf.WellKnownTypes;

class Program
{
    static async Task Main(string[] args)
    {
        // Kreiranje kanala ka serveru
        var channel = GrpcChannel.ForAddress("https://localhost:5001");
        var client = new Lab1Service.Lab1ServiceClient(channel);

        Console.WriteLine("=== TEST 1: Poziv proslediBroj (Unary RPC) ===");
        var broj = new Broj { Vrednost = 5 };

        client.proslediBroj(broj);
        Console.WriteLine("Prosleđen broj 5 (računa srednju vrednost 1..5 = 3, dodaje u acc).");

        Console.WriteLine();

        Console.WriteLine("=== TEST 2: Poziv proslediTok (Bidirectional Stream) ===");

        // Otvaramo bidirectional stream
        var call = client.proslediTok();

        // Task koji čita rezultate od servera
        var readTask = Task.Run(async () =>
        {
            await foreach (var odgovor in call.ResponseStream.ReadAllAsync())
            {
                Console.WriteLine($"Server vratio: {odgovor.Vrednost}");
            }
        });

        // Šaljemo tok brojeva
        int[] niz = { 2, 4, 6, 8, 10, 12 };
        foreach (var n in niz)
        {
            Console.WriteLine($"Klijent šalje: {n}");
            await call.RequestStream.WriteAsync(new Broj { Vrednost = n });
            await Task.Delay(300); // malo pauze radi demonstracije
        }

        await call.RequestStream.CompleteAsync();
        await readTask;

        Console.WriteLine("\nTest završen. Pritisni ENTER za izlaz.");
        Console.ReadLine();
    }
}
