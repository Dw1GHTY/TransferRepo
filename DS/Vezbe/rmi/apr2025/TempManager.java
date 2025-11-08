
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class TempManager extends UnicastRemoteObject implements ITempManager {

    private double idealTemp;
    private double acceptableRange;

    public TempManager(double idealTemp, double acceptableRange) throws RemoteException {
        try {
            this.idealTemp = idealTemp;
            this.acceptableRange = acceptableRange;
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void execTempAdjustment(double sensorTemperature) throws RemoteException {
        try {
            double maxTemp = this.idealTemp + this.acceptableRange;
            double minTemp = this.idealTemp - this.acceptableRange;
            if (sensorTemperature > maxTemp) {
                sendMessage(new Message("Cool it down!"));
            } else if (sensorTemperature < minTemp) {
                sendMessage(new Message("Warm it up!"));
            } else {
                sendMessage(new Message("System shutdown . . ."));
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void sendMessage(Message message) throws RemoteException {
        //? List<ICallback> as param
    }

}
