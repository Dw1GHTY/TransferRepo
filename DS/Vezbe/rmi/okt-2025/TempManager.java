
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class TempManager extends UnicastRemoteObject implements ITempManager {

    public TempManager() throws RemoteException {
        try {

        } catch (Exception e) {
            System.out.println(e);
        }

    }

}
