
import java.rmi.Naming;
import java.rmi.RemoteException;

public class Client {

    private ITempManager serverTempManager;

    public Client() throws RemoteException {
        try {
            serverTempManager = (ITempManager) Naming.lookup("rmi://localhost:1099/tempManager");

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

}
