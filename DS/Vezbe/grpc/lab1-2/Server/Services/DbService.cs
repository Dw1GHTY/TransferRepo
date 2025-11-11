namespace Server.Services
{
    public class DbService
    {
        public int acc;
        private static DbService instanca;
        private static object lockObj = new object();


        public DbService() 
        {
            acc = 0;
        }


        public DbService Instanca() 
        {
            if (instanca == null) 
            {
                lock (lockObj) 
                {
                    instanca = new DbService();
                }
            }
            return instanca;
        }
    }
}
