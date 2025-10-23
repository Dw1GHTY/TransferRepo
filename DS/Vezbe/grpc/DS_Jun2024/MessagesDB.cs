
namespace MessageNamespace
{
    public class MessagesDB
    {
        private static MessagesDB instanca;
        private static object lockObj = new object();
        public Dictionary<Identifikator, Poruka> baza {  get; set; }

        private MessagesDB() 
        {
            baza = new Dictionary<Identifikator, Poruka>();

        }


        public static MessagesDB Instanca() 
        {
            if (instanca == null) 
            {
                lock (lockObj) 
                {
                    instanca = new MessagesDB();
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