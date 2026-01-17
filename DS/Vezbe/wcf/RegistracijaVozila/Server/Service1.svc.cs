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
    public class Service1 : IRegistracijaServis
    {
        private Dictionary<Vozilo, Registracija> registarRegistracija;
        private int redniBrojRegistracije;      //da broj ne bi ostao isti, server mora da perzistira => jedna instanca

        public Service1() 
        {
            registarRegistracija = new Dictionary<Vozilo, Registracija>();
            redniBrojRegistracije = 1;
        }

        public void RegistrujVozilo(Vlasnik vlasnik, Vozilo vozilo, DateTime datumKrajaRegistracije) 
        {
            var novaRegistracija = new Registracija()
            {
                Vlasnik = vlasnik,
                Vozilo = vozilo,
                DatumKrajaRegistracije = datumKrajaRegistracije,
                DatumPocetkaRegistracije = DateTime.Now,
                BrojRegistracije = redniBrojRegistracije
            };
            this.registarRegistracija.Add(vozilo, novaRegistracija);
            this.redniBrojRegistracije++;
        }


        public List<Vozilo> vratiVozilaVlasnika(Vlasnik vlasnik) 
        {
            var filter = registarRegistracija.Where(item => item.Value.Vlasnik.Jmbg == vlasnik.Jmbg);
            var vozila = filter.Select(p => p.Key);
            return vozila.ToList();
        }



        public List<Registracija> sveRegistracije() 
        {
            return this.registarRegistracija.Values.ToList();
        }
    }
}
