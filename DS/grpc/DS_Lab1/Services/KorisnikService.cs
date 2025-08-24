using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using ServerNamespace;
using System.IO;

namespace DS_Lab1.Services
{
    public class KorisnikService : ServerNamespace.KorisniciService.KorisniciServiceBase
    {

        public static int acc = 0;

        //rpc CreateKorisnika(Korisnik) returns(Poruka);
        public override Task<Poruka> CreateKorisnika(
            Korisnik request, ServerCallContext context)
        {
            if(Korisnici.Instanca().baza.ContainsKey(request.Identifikator.Id))
            {
                return Task.FromResult(new Poruka()
                {
                    Tekst = "Vec postoji"
                });
            }
            Korisnik tmp = new Korisnik()
            {
                ImeKorsinika = request.ImeKorsinika,
                PrezimeKorisnika = request.PrezimeKorisnika,
                BrTelefona = request.BrTelefona
            };
            if(request.HasAdresaKorisnika)
            {
                tmp.AdresaKorisnika = request.AdresaKorisnika;
            }
            Korisnici.Instanca().baza.Add(request.Identifikator.Id, tmp);
            return Task.FromResult(new Poruka() { Tekst = "Korisnik uspesno kreiran" });
        }
        //rpc ReadKorisnika(Identifikator) returns(Korisnik);
        public override Task<Korisnik> ReadKorisnika(
            Identifikator id, 
            ServerCallContext context) 
        {
            if (!Korisnici.Instanca().baza.ContainsKey(id.Id)) 
            {
                return Task.FromResult(new Korisnik());
            }
            Korisnik tmp = Korisnici.Instanca().baza[id.Id];
            return Task.FromResult<Korisnik>(tmp);
        }

        //rpc UpdateKorsnika(UpdateTip) returns(Poruka);
        public override Task<Poruka> UpdateKorsnika(UpdateTip request, ServerCallContext context) 
        {
            if (!Korisnici.Instanca().baza.ContainsKey(request.Id.Id)) 
            {
                return Task.FromResult(new Poruka() { Tekst = "Nema ga" });
            }
            Korisnik tmp = Korisnici.Instanca().baza[request.Id.Id];
            tmp.ImeKorsinika = request.Korisnik.ImeKorsinika;
            tmp.PrezimeKorisnika = request.Korisnik.PrezimeKorisnika;
            if (request.Korisnik.HasAdresaKorisnika) 
            {
                tmp.AdresaKorisnika = request.Korisnik.AdresaKorisnika;
            }
            tmp.BrTelefona = request.Korisnik.BrTelefona;

            return Task.FromResult(new Poruka() { Tekst = "Uspesno azuriran Korisnik"});
        }


        //rpc DelteKorisnika(Identifikator) returns(google.protobuf.Empty);
        public override Task<Empty> DelteKorisnika(Identifikator request, ServerCallContext context) 
        {
            if (!Korisnici.Instanca().baza.ContainsKey(request.Id)) 
            {
                return Task.FromResult(new Empty());
            }
            Korisnici.Instanca().baza.Remove(request.Id);
            return Task.FromResult(new Empty());
        }


        //rpc ReadFromToKorisnika(Opseg) returns(stream Korisnik);
        public override async Task ReadFromToKorisnika(Opseg request, IServerStreamWriter<Korisnik> response,
            ServerCallContext context)
        {
            var listaOdDo = Korisnici.Instanca().baza.OrderBy(x=>x.Key).Where(
                x=> x.Key>=request.IdFrom.Id && x.Key<=request.IdTo.Id);
            foreach(var k in listaOdDo)
            {
                await response.WriteAsync(k.Value);
            }
        }

        //rpc DeleteStreamKorisnika(stream Identifikator) returns(stream Poruka);
        public override async Task DeleteStreamKorisnika(
            IAsyncStreamReader<Identifikator> request, IServerStreamWriter<Poruka> response,
            ServerCallContext context)
        {
            await foreach(var i in request.ReadAllAsync())
            {
                if(Korisnici.Instanca().baza.ContainsKey(i.Id))
                {
                    Korisnici.Instanca().baza.Remove(i.Id);
                    await response.WriteAsync(new Poruka() { Tekst = "uspesno obrisan korisnik " + i.Id });
                }
                else
                {
                    await response.WriteAsync(new Poruka() { Tekst = "ne postoji korsnik " + i.Id });
                }
            }
        }

        //rpc ReadStreamKorisnika(google.protobuf.Empty) returns(stream Korisnik)

        public override async Task ReadStreamKorisnika(Empty e, IServerStreamWriter<Korisnik> response
            , ServerCallContext context)
        {
            foreach(var x in Korisnici.Instanca().baza)
            {
                await response.WriteAsync(x.Value);
            }
        }
    }
}
