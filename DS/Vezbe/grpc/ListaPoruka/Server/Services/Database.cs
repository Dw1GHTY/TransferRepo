using MessengerNamespace;

namespace Server.Services
{
    public class Database
    {
        private static Database instance;
        private static object lockObject = new object();
        public List<Message> messagesList;


        public Database() 
        {
            messagesList = new List<Message>();
        }

        public static Database Instance() 
        {
            if (instance == null) 
            {
                lock (lockObject) 
                {
                    instance = new Database();
                }
            }
            return instance;
        }
    }
}
