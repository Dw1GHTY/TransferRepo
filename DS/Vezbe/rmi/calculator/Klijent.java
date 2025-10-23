import java.rmi.Naming;
public class Klijent {

    public Klijent(){
        try {
            ICalculator c = (ICalculator)Naming.lookup("rmi://localhost:1099/service");
            System.out.println(c.add(2, 2));

            String input = new String();

            while(!input.equals("x")){

                System.out.println("+ -> add\n - -> subtract\n * -> multiplication");
                input = System.console().readLine();

                switch (input) {
                    case "+":
                        System.out.println("Unesi dva broja:\n");
                        input = System.console().readLine();
                        int a = Integer.parseInt(input);
                        input = System.console().readLine();
                        int b = Integer.parseInt(input);
                        System.out.println(c.add(a, b));
                        break;
                
                    default:
                        break;
                }
            }

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args){

        new Klijent();

        
    }

}
