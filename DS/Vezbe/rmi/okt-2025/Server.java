
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    public ITempManager tempManager;

    public Server() throws RemoteException {
        try {
            this.tempManager = new TempManager();
            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/tempManager", tempManager);

        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
