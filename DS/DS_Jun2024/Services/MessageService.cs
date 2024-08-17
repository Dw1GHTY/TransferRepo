using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using MessageNamespace;

namespace DS_Jun2024.Services
{
    public class MessageService: MessageNamespace.ServiceMessages.ServiceMessagesBase
    {
        public override Task<Empty> SendMessage(Poruka p, ServerCallContext context) 
        {
            if (MessagesDB.Instanca().baza.ContainsKey(p.PorukaId)) 
            {
                return Task.FromResult(new Empty());
            }
            MessagesDB.Instanca().baza.Add(p.PorukaId, p);
            return Task.FromResult(new Empty());
        }

        public override Task<Empty> DeleteMessage(Identifikator i, ServerCallContext context) 
        {
            if (MessagesDB.Instanca().baza.ContainsKey(i)) 
            {
                MessagesDB.Instanca().baza.Remove(i);
            }
            return Task.FromResult(new Empty());
        }

        public override async Task ListMessages(Empty empty, IServerStreamWriter<Poruka> izlaz, ServerCallContext context) 
        {
            foreach (Poruka p in MessagesDB.Instanca().baza.Values) 
            {
                await izlaz.WriteAsync(p);
            }
        }
    }
}
