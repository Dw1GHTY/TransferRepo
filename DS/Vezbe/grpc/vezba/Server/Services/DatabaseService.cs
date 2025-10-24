namespace MessagingService.Services;

public class DatabaseService
{
    private static DatabaseService messageQueue;
    private static object lockObj = new object();
    private static List<Message> messages;
    public DatabaseService()
    {
        messages = new List<Message>();
    }

    public static DatabaseService getInstance()
    {
        if (messageQueue == null)
        {
            lock (lockObj)
            {
                if (messageQueue == null)
                    messageQueue = new DatabaseService();
            }
        }
        return messageQueue;
    }

    public void AddMessage(Message msg)
    {
        messages.Add(msg);
    }

    public List<Message> GetMessages()
    {
        return messages;
    }

    public Message FindAndDeleteMessage(Id id) 
    {
        Message msg = messages.Find(m => m.Id == id.Id_);
        if(msg != null)
            messages.Remove(msg);

        return msg;
    }


}

