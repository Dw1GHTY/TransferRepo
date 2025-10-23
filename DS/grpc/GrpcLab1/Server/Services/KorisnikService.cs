using Grpc.Core;
using Google.Protobuf.WellKnownTypes;
using KorisnikServisGrpc;
using System.Runtime.CompilerServices;
namespace Server.Services
{
    public class KorisnikService : KorisnikServis.KorisnikServisBase
    {
        public override Task<Korisnik> GetKorisnik(Id korisnikId, ServerCallContext context)
        {
            var db = DatabaseService.getInstance();
            var korisnik = db.GetKorisnik(korisnikId.Id_);
            return Task.FromResult(korisnik);
        }

        public override Task<Korisnik> CreateKorisnik(Korisnik newKorisnik, ServerCallContext context) 
        {
            var db = DatabaseService.getInstance();
            var k = db.CreateKorisnik(newKorisnik);
            return Task.FromResult(k);
        }
        public override Task<Korisnik> UpdateKorisnik(Korisnik updatedKorisnik, ServerCallContext context) 
        {
            var db = DatabaseService.getInstance();
            var k = db.UpdateKorisnik(updatedKorisnik);

            return Task.FromResult(k);
        }
        public override Task<Korisnik> DeleteKorisnik(Id korisnikId, ServerCallContext context) 
        {
            var db = DatabaseService.getInstance();
            var k = db.DeleteKorisnik(korisnikId.Id_);

            return Task.FromResult(k);
        }

        public override async Task DeleteKorisnici(
            IAsyncStreamReader<Id> requestStream, 
            IServerStreamWriter<Korisnik> responseStream, 
            ServerCallContext context) 
        {
            var db = DatabaseService.getInstance();


            await foreach (var id in requestStream.ReadAllAsync()) 
            {
                var k = db.GetKorisnik(id.Id_);
                if (k != null)
                { 
                    db.DeleteKorisnik(id.Id_);
                    await responseStream.WriteAsync(k);
                }
            }
        }


        
    }
}
