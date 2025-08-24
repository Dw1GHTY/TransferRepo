import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {
    
    public Server() throws RemoteException{
        try {
            LocateRegistry.createRegistry(1099);
            IWhiteboardManager w = new WhiteboardManager();
            Naming.rebind("rmi://localhost:1099/service", w);

            System.out.println("***********Server initialised***********\n");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        try {
            new Server();
            System.console().readLine();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

}
