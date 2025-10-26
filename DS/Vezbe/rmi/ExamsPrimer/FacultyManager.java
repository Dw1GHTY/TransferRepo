import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.Map;

public class FacultyManager extends UnicastRemoteObject implements IFacultyManager {
    
    private Map<Integer, Exam> exams;

    public FacultyManager() throws RemoteException {
        try {
            this.exams = new HashMap<Integer, Exam>();
            Exam ispit1 = new Exam(1, "DS");
            this.exams.put(18289, ispit1);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public Exam findIspit(int brojIndeksa) throws RemoteException {
        try {
            Exam ispit = this.exams.get(brojIndeksa);
            if( ispit != null)
                return ispit;
            else throw new RemoteException("Kurac " + brojIndeksa); 
        } catch (Exception e) {
            System.out.println(e.getMessage());
            throw new RemoteException("Mega problem " + e.getMessage(), e);
        }
    }

}
