using KorisnikServisGrpc;
namespace Server.Services
{
    public class DatabaseService
    {
        private List<Korisnik> listaKorisnika;
        private static DatabaseService database;
        private static object lockObj = new object();


        public DatabaseService() 
        {
            listaKorisnika = new List<Korisnik>();
        }
        public static DatabaseService getInstance() 
        {
            if (database == null) 
            {
                lock (lockObj) 
                {
                    if (database == null) 
                    {
                        database = new DatabaseService();
                    }
                }
            }
            return database;
        }


        public Korisnik GetKorisnik(int id) 
        {
            var korisnik = listaKorisnika.Find(k => k.Id == id);
            if (korisnik == null)
                return null;
            return korisnik;
        }
        public Korisnik CreateKorisnik(Korisnik newKorisnik) 
        {
            var k = listaKorisnika.Append(newKorisnik);

            return newKorisnik;
        }
        public Korisnik DeleteKorisnik(int id) 
        {
            var k = GetKorisnik(id);

            if (k == null)
                return null;
            return k;
        }
        public Korisnik UpdateKorisnik(Korisnik updatedKorisnik) 
        {
            var k = GetKorisnik(updatedKorisnik.Id);
            if (k == null)
                return null;
            k.Ime = updatedKorisnik.Ime;
            k.Prezime = updatedKorisnik.Prezime;
            k.Adresa = updatedKorisnik.Adresa;
            k.BrojeviTelefona = updatedKorisnik.BrojeviTelefona;

            return k;
        }
    
    }
}
