using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace Server
{
    // Dodajemo ConcurrencyMode.Multiple da servis ne bi blokirao ostale klijente 
    // dok se izvršava neka duga operacija (npr. slanje poruke).
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Multiple)]
    public class ChatService : IChatService
    {
        private Dictionary<string, IChatCallback> users = new Dictionary<string, IChatCallback>();
        private readonly object syncObj = new object();

        public void register(string username)
        {
            IChatCallback callback = OperationContext.Current.GetCallbackChannel<IChatCallback>();

            lock (syncObj)
            {
                if (users.ContainsKey(username))
                {
                    users[username] = callback;
                    Console.WriteLine($"Korisnik {username} je ažurirao sesiju.");
                }
                else
                {
                    users.Add(username, callback);
                    Console.WriteLine($"Korisnik {username} se registrovao.");
                }
            }
        }

        public void sendMessage(Message msg, string to)
        {
            IChatCallback receiver = null;
            lock (syncObj)
            {
                if (this.users.ContainsKey(to))
                {
                    receiver = this.users[to];
                }
            }
            if (receiver != null)
            {
                try
                {
                    receiver.notifyReceiver(msg);
                }
                catch (Exception ex)
                {
                    // Ako slanje ne uspe (klijent je pao), brišemo ga
                    Console.WriteLine($"Greska pri slanju ka {to}. Uklanjam korisnika. {ex.Message}");
                    lock (syncObj)
                    {
                        if (users.ContainsKey(to)) users.Remove(to);
                    }
                }
            }
        }
    }
}