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
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession)]
    public class Service1 : IKalkulatorService
    {

        private string racunanje;
        private float rezulat;

        public Service1() 
        {
            this.racunanje = string.Empty;
            this.rezulat = 0.0f;
        }
        public void obrisiRacunanje() 
        {
            this.racunanje = string.Empty;
            this.rezulat = 0.0f;
        }


        public float saberi(float broj) 
        {
            this.racunanje += "+" + broj.ToString();
            this.rezulat += broj;

            ICallback cb = OperationContext.Current.GetCallbackChannel<ICallback>();
            cb.prikaziRacunanje(this.racunanje);
            return this.rezulat;
        }

        public float oduzmi(float broj) 
        {
            this.racunanje += "-" + broj.ToString();
            this.rezulat -= broj;

            ICallback cb = OperationContext.Current.GetCallbackChannel<ICallback>();
            cb.prikaziRacunanje(this.racunanje);

            return this.rezulat;
        }

        public float pomnozi(float broj) 
        {
            this.racunanje += "*" + broj.ToString();
            this.rezulat *= broj;

            ICallback cb = OperationContext.Current.GetCallbackChannel<ICallback>();
            cb.prikaziRacunanje(this.racunanje);

            return this.rezulat;
        }

        public float podeli(float broj) 
        {
            this.racunanje += "/" + broj.ToString();
            this.rezulat /= broj;

            ICallback cb = OperationContext.Current.GetCallbackChannel<ICallback>();
            cb.prikaziRacunanje(this.racunanje);

            return this.rezulat;
        }
    }
}
