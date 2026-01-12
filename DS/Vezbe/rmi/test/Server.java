
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    IEcho obj;

    public Server() throws RemoteException {
        try {
            this.obj = new Echo();

            LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099", obj);

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        try {
            new Server();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

}
