import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.HashMap;

public interface IWhiteboardManager extends Remote{

    public HashMap<String, Integer> getAllObjects() throws RemoteException;
    public void addObject(String figureName) throws RemoteException;
    public int getObjectVersion(String figureName) throws RemoteException;

    public void register(ICallback cb) throws RemoteException;
    public void unregister(ICallback cb) throws RemoteException;
}