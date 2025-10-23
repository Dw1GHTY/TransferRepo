using Grpc.Net.Client;
using KorisnikServisGrpc;

class Program
{
    static async Task Main(string[] args)
    {
        // Povezivanje sa serverom
        using var channel = GrpcChannel.ForAddress("https://localhost:7777"); // Promeni port!
        var client = new KorisnikServis.KorisnikServisClient(channel);

        bool running = true;

        while (running)
        {
            Console.WriteLine("\n=== GRPC KLIJENT MENI ===");
            Console.WriteLine("1. GetKorisnik (po ID-u)");
            Console.WriteLine("2. CreateKorisnik");
            Console.WriteLine("3. UpdateKorisnik");
            Console.WriteLine("4. DeleteKorisnik (po ID-u)");
            Console.WriteLine("5. DeleteKorisnici (stream)");
            Console.WriteLine("0. Izlaz");
            Console.Write("\nIzbor: ");

            var choice = Console.ReadLine();

            try
            {
                switch (choice)
                {
                    case "1":
                        await GetKorisnik(client);
                        break;
                    case "2":
                        await CreateKorisnik(client);
                        break;
                    case "3":
                        await UpdateKorisnik(client);
                        break;
                    case "4":
                        await DeleteKorisnik(client);
                        break;
                    case "5":
                        await DeleteKorisnici(client);
                        break;
                    case "0":
                        running = false;
                        Console.WriteLine("Izlazim...");
                        break;
                    default:
                        Console.WriteLine("Nevalidan izbor!");
                        break;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Greška: {ex.Message}");
            }
        }
    }

    static async Task GetKorisnik(KorisnikServis.KorisnikServisClient client)
    {
        Console.Write("Unesi ID korisnika: ");
        if (!int.TryParse(Console.ReadLine(), out int id))
        {
            Console.WriteLine("Nevalidan ID!");
            return;
        }

        var request = new Id { Id_ = id };
        var korisnik = await client.GetKorisnikAsync(request);

        Console.WriteLine($"\n--- Korisnik ---");
        Console.WriteLine($"ID: {korisnik.Id}");
        Console.WriteLine($"Ime: {korisnik.Ime}");
        Console.WriteLine($"Prezime: {korisnik.Prezime}");
        Console.WriteLine($"Opciona adresa: {korisnik.Adresa}");
        Console.WriteLine($"Broj telefona: {korisnik.BrojeviTelefona}");
    }

    static async Task CreateKorisnik(KorisnikServis.KorisnikServisClient client)
    {
        Console.Write("Unesi ID: ");
        if (!int.TryParse(Console.ReadLine(), out int id))
        {
            Console.WriteLine("Nevalidan ID!");
            return;
        }

        Console.Write("Unesi ime: ");
        var ime = Console.ReadLine();

        Console.Write("Unesi prezime: ");
        var prezime = Console.ReadLine();

        Console.Write("Unesi opciona adresu (Enter za prazno): ");
        var adresa = Console.ReadLine();

        Console.Write("Unesi broj telefona: ");
        var telefon = Console.ReadLine();

        var newKorisnik = new Korisnik
        {
            Id = id,
            Ime = ime,
            Prezime = prezime,
            Adresa = adresa,
            BrojeviTelefona = telefon
        };

        var created = await client.CreateKorisnikAsync(newKorisnik);
        Console.WriteLine($"\nKreiran korisnik sa ID: {created.Id}");
    }

    static async Task UpdateKorisnik(KorisnikServis.KorisnikServisClient client)
    {
        Console.Write("Unesi ID korisnika za ažuriranje: ");
        if (!int.TryParse(Console.ReadLine(), out int id))
        {
            Console.WriteLine("Nevalidan ID!");
            return;
        }

        Console.Write("Unesi novo ime: ");
        var ime = Console.ReadLine();

        Console.Write("Unesi novo prezime: ");
        var prezime = Console.ReadLine();

        Console.Write("Unesi novu opciona adresu: ");
        var adresa = Console.ReadLine();

        Console.Write("Unesi novi broj telefona: ");
        var telefon = Console.ReadLine();

        var updatedKorisnik = new Korisnik
        {
            Id = id,
            Ime = ime,
            Prezime = prezime,
            Adresa = adresa,
            BrojeviTelefona = telefon
        };

        var result = await client.UpdateKorisnikAsync(updatedKorisnik);
        Console.WriteLine($"\nAžuriran korisnik sa ID: {result.Id}");
    }

    static async Task DeleteKorisnik(KorisnikServis.KorisnikServisClient client)
    {
        Console.Write("Unesi ID korisnika za brisanje: ");
        if (!int.TryParse(Console.ReadLine(), out int id))
        {
            Console.WriteLine("Nevalidan ID!");
            return;
        }

        var request = new Id { Id_ = id };
        var deleted = await client.DeleteKorisnikAsync(request);

        Console.WriteLine($"\nObrisan korisnik:");
        Console.WriteLine($"ID: {deleted.Id}, Ime: {deleted.Ime}, Prezime: {deleted.Prezime}");
    }

    static async Task DeleteKorisnici(KorisnikServis.KorisnikServisClient client)
    {
        Console.Write("Unesi ID-eve za brisanje (odvojene zarezom, npr: 1,2,3): ");
        var input = Console.ReadLine();
        var ids = input.Split(',').Select(x => int.Parse(x.Trim())).ToList();

        using var call = client.DeleteKorisnici();

        // Task za slanje ID-eva
        var sendTask = Task.Run(async () =>
        {
            foreach (var id in ids)
            {
                await call.RequestStream.WriteAsync(new Id { Id_ = id });
                Console.WriteLine($"Poslat ID: {id}");
            }
            await call.RequestStream.CompleteAsync();
        });

        // Task za primanje obrisanih korisnika
        var receiveTask = Task.Run(async () =>
        {
            Console.WriteLine("\n--- Obrisani korisnici ---");
            await foreach (var korisnik in call.ResponseStream.ReadAllAsync())
            {
                Console.WriteLine($"ID: {korisnik.Id}, Ime: {korisnik.Ime}, Prezime: {korisnik.Prezime}");
            }
        });

        await Task.WhenAll(sendTask, receiveTask);
        Console.WriteLine("\nBrisanje završeno!");
    }
}