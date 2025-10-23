using ServerNamespace;

namespace DS_Lab1
{
    public class Korisnici
    {
        private static Korisnici instanca;
        private static object lockObj = new object();
        public Dictionary<int, Korisnik> baza { get; set; }

        private Korisnici()
        {
            baza = new Dictionary<int, Korisnik>()
            {
                {
                    1, new Korisnik()
                    {
                        ImeKorsinika = "Cicak",
                        PrezimeKorisnika = "Cickic",
                        BrTelefona = "123468"
                    }
                }
            };
        }
        public static Korisnici Instanca()
        {
            if(instanca== null)
            {
                lock (lockObj)
                {
                    instanca = new Korisnici();
                }
            }
            return instanca;
        }
    }
}

//info: Microsoft.Hosting.Lifetime[14]
//      Now listening on: http://localhost:5252
//info: Microsoft.Hosting.Lifetime[14]
//      Now listening on: https://localhost:7114
