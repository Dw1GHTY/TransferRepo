using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Server
{
    class RegistracijaService : IRegistracijaService
    {

        private List<Registracija> registracije;
        private Dictionary<Vlasnik, Vozilo> vozilaVlasnika;

        private int brojRegistracije;


        public RegistracijaService() 
        {
            registracije = new List<Registracija>();
            vozilaVlasnika = new Dictionary<Vlasnik, Vozilo>();
            brojRegistracije = 0;
        }

        void RegistrujVozilo(Vlasnik vl, Vozilo voz, DateTime datumKrajaReg) 
        {
            vozilaVlasnika.Add(vl, voz);
            var reg = new Registracija();
            
            reg.DatumKrajaRegistracije = datumKrajaReg;
            reg.Vlasnik = vl;
            reg.Vozilo = voz;
            reg.DatumKrajaRegistracije = datumKrajaReg;
            reg.DatumPocetkaRegistracije = DateTime.Now;

            brojRegistracije++;
            reg.BrojRegistracije = brojRegistracije; 

            registracije.Add(reg)
        }


        List<Vozilo> vratiVozilaVlasnika(Vlasnik v) 
        {
            return new List<Vozilo>();
        }


        List<Registracija> vratiRegistracijeVozila(Vozilo v) 
        {
            return new List<Registracija>();
        }


        List<Registracija> vratiVozilaIRegistracije() 
        {
            return new List<Registracija>();
        }
    }
}
