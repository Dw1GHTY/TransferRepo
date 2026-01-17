using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.

    [ServiceBehavior(
        InstanceContextMode = InstanceContextMode.PerSession,
        ConcurrencyMode = ConcurrencyMode.Single
        )]
    public class KalkulatorService : IKalkulatorService 
    {
        private Rezultat trenutniRezultat;
        private ICallback cb;
        public void obrisiRacunanje() 
        {
            this.cb = OperationContext.Current.GetCallbackChannel<ICallback>();
            this.trenutniRezultat = new Rezultat();
            this.trenutniRezultat.RezultatOperacije = 0;
            this.trenutniRezultat.Operacija = string.Empty; 
        }

        public void dodajBroj(int broj) 
        {
            this.trenutniRezultat.RezultatOperacije += broj;
            this.trenutniRezultat.Operacija += " + " + broj;
            cb.obavestiKlijenta(trenutniRezultat);
        }

        public void oduzmiBroj(int broj) 
        {
            this.trenutniRezultat.RezultatOperacije -= broj;
            this.trenutniRezultat.Operacija += " - " + broj;
            cb.obavestiKlijenta(trenutniRezultat);
        }

        public void pomnoziBrojem(int broj)
        {
            this.trenutniRezultat.RezultatOperacije *= broj;
            this.trenutniRezultat.Operacija += " * " + broj;
            cb.obavestiKlijenta(trenutniRezultat);
        }


        public void podeliBrojem(int broj) 
        {
            this.trenutniRezultat.RezultatOperacije /= broj;
            this.trenutniRezultat.Operacija += " / " + broj;
            cb.obavestiKlijenta(trenutniRezultat);
        }

    }
}
