
import java.rmi.Naming;

public class Client {

    public ITempManager tempManager;

    public Client() {
        try {
            this.tempManager = (ITempManager) Naming.lookup("rmi://localhost:1099/tempManager");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
