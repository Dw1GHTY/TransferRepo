import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    private IBroker broker;
    // ! treba mi lista callbackova gde su registrovani klijenti

    public Server() throws RemoteException {
        LocateRegistry.createRegistry(1099);
        Naming.rebind("rmi://localhost:1099/broker", broker);
    }

    public static void main(String[] args) {

    }
}