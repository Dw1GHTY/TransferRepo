import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Klijent {
    
    public IWhiteboardManager w;
    public ICallback callback;

    public Klijent(){

        try {
            callback = new Callback();
            w = (IWhiteboardManager)Naming.lookup("rmi://localhost:1099/service");
            //System.out.println(w);
            w.register(callback);
            
            String unos = "sample";
            while(!unos.equals("x")){
                System.out.println("To draw, press 'a' \n To exit, press 'x'");
                unos = System.console().readLine();
                switch (unos) {
                    case "a":
                        System.out.println("Unesi naziv figure:");
                        String newFigure = System.console().readLine();
                        w.addObject(newFigure);
                        callback.callback();
                        break;
                    case "x":
                        break;
                    default:
                        break;
                }
            }

            w.unregister(callback);
        } catch (Exception e) {
            System.out.println("error" + e.getMessage());
        }
    }

    public static void main(String[] args) {
        new Klijent();
        System.console().readLine();

    }


    public class Callback extends UnicastRemoteObject implements ICallback{
        public Callback() throws RemoteException {}

        public void callback() throws RemoteException{
            for (String figure : w.getAllObjects().keySet()) {
                System.out.println(figure);
            } 
        }
    }

}
