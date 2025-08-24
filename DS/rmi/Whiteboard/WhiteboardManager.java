import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class WhiteboardManager extends UnicastRemoteObject implements IWhiteboardManager {
    
    public List<ICallback> clients;
    private static int version;
    public static HashMap<String, Integer> whiteboard;

    public WhiteboardManager() throws RemoteException{
        setVersion(0);  //pocinje od 0 kad se inicijalizuje
        whiteboard = new HashMap<String, Integer>();
        clients = new ArrayList<ICallback>();
    }



    //ispis svih Figure-a na tabli == trenutno stanje
    public HashMap<String, Integer> getAllObjects() throws RemoteException {
        
        return whiteboard;
        
    }

    public void addObject(String figureName) throws RemoteException {

        setVersion(getVersion() + 1); //inkrementira verziju, dodaje novi obj u mapu i dodeljuje joj verziju table
        whiteboard.put(figureName, getVersion());   //ako ga nema dodaje novi, ako ga ima menja mu value

    }

    public int getObjectVersion(String figureName) throws RemoteException {
        return whiteboard.get(figureName);
    }


    public static int getVersion() {
        return version;
    }
    public static void setVersion(int newVersion) {
        WhiteboardManager.version = newVersion;
    }


    public synchronized void register(ICallback cb) throws RemoteException{
        System.out.println(cb + " " + clients);
        clients.add(cb);    
    }
    
    public synchronized void unregister(ICallback cb) throws RemoteException{
        clients.remove(cb);
    }
}
