using Client.ServiceReference1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Channels;
using System.Runtime.Serialization;
using System.Security.Cryptography.X509Certificates;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;


namespace Client
{
    internal class Program
    {

        private 
        static void Main(string[] args)
        {
            var callback = new Callback();
            InstanceContext context = new InstanceContext(new Program());
            DuplexChannelFactory<IKalkulatorService> factory =
                new DuplexChannelFactory<IKalkulatorService>(context, "KalkulatorServiceEndpoint");

            IKalkulatorService proxy = factory.CreateChannel();

            proxy.dodajBroj(2);
            proxy.dodajBroj(5);
            proxy.oduzmiBroj(3);
            proxy.podeliBrojem(2);
            proxy.pomnoziBrojem(8);


        }
         
    }

    internal class Callback : IKalkulatorServiceCallback 
    {
        public void obavestiKlijenta(Rezultat rez)
        {
            Console.WriteLine("Trenutni Rezultat: " + rez.RezultatOperacije);
            Console.WriteLine("Operacija: " + rez.Operacija);
        }

    }
}
