
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Echo extends UnicastRemoteObject implements IEcho {

    public Echo() throws RemoteException {
        try {

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public String getEcho(String echo) throws RemoteException {
        try {
            return echo;
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return echo;
    }
}
