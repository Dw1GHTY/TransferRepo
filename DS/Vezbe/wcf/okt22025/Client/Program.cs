using Client.KalkulatorServiceReference;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    internal class Program
    {


        static void Main(string[] args)
        {
            IKalkulatorServiceCallback cb = new Callback();
            KalkulatorServiceClient client  = new KalkulatorServiceClient(new InstanceContext(cb));

            string unos = null;
            float broj = 0.0f;
            Console.WriteLine("=======Kalkulator=======");

            while (true) 
            {
                Console.WriteLine("\n\nOperacija: ");
                unos = Console.ReadLine();

                Console.WriteLine("Unesi operand: ");
                broj = float.Parse(Console.ReadLine());

                switch (unos) 
                {
                    case "+": Console.WriteLine("Rez:" + saberi(broj, client)); break;
                    case "-": Console.WriteLine("Rez:" + oduzmi(broj, client)); break;
                    case "*": Console.WriteLine("Rez:" + pomnozi(broj, client)); break;
                    case "/": Console.WriteLine("Rez:" + podeli(broj, client)); break;
                    case "d": obrisi(client); break;
                    default: break;
                }
            }

        }

        public static void obrisi(KalkulatorServiceClient client)
        {
            client.obrisiRacunanje();
        }
        public static float saberi(float broj, KalkulatorServiceClient client) 
        {
            return client.saberi(broj);
        }
        public static float oduzmi(float broj, KalkulatorServiceClient client)
        {
            return client.oduzmi(broj);
        }
        public static float pomnozi(float broj, KalkulatorServiceClient client)
        {
            return client.pomnozi(broj);
        }
        public static float podeli(float broj, KalkulatorServiceClient client)
        {
            return client.podeli(broj);
        }
    }


    public class Callback : IKalkulatorServiceCallback
    {
        public Callback() { }

        public void CallbackPrikaziRacunanje(string rez) 
        {
            Console.WriteLine("=========Trenutno stanje:=========\n"+rez);
        }
    }



    
}
