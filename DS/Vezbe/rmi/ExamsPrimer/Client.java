import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Scanner;

public class Client {
    IFacultyManager facultyManager;

    public Client() throws Exception {  // Changed from RemoteException
        this.facultyManager = (IFacultyManager) Naming.lookup("rmi://localhost:1099/facultyManager");
        System.out.println("Client initialized");
    }
    
    public static void main(String[] args) {
        try {
            Client client = new Client();
            Scanner scanner = new Scanner(System.in);
            String input = null;
            
            System.out.println("=== Welcome to Faculty Manager ===");
            
            do {
                System.out.println("\nMenu:");
                System.out.println("1. Find Exam by Student Index");
                System.out.println("0. Exit");
                System.out.print("Enter choice: ");
                
                input = scanner.nextLine().trim();
                
                switch(input) {
                    case "1":
                        System.out.print("Enter student index number: ");
                        try {
                            int brojIndeksa = Integer.parseInt(scanner.nextLine().trim());
                            Exam exam = client.facultyManager.findIspit(brojIndeksa);
                            System.out.println("Exam found: " + exam);
                        } catch (NumberFormatException e) {
                            System.out.println("Invalid number format!");
                        } catch (RemoteException e) {
                            System.out.println("Error: " + e.getMessage());
                        }
                        break;
                        
                    case "0":
                        System.out.println("Goodbye!");
                        break;
                        
                    default:
                        System.out.println("Invalid choice! Please try again.");
                        break;
                }
                
            } while(!input.equals("0"));
            
            scanner.close();
            
        } catch (Exception e) {
            System.err.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}