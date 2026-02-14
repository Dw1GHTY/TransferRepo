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
    public class Service1 : ICalculatorService
    {
        public float currentResult;
        public string currentState;
        public ICalcCallback callback;

        public Service1() 
        {
            this.currentResult = 0;
            this.currentState = string.Empty;
            this.callback = OperationContext.Current.GetCallbackChannel<ICalcCallback>();
        }

        public void clearState() 
        {
            this.currentState = string.Empty;
            this.currentResult = 0.0f;
        }


        public void add(float number) 
        {
            this.currentResult += number;
            this.currentState += "+" + number.ToString();
            this.callback.notifyUser(currentResult, currentState);
        }

        public void subtract(float number) 
        {
            this.currentResult -= number;
            this.currentState += "-" + number.ToString();
            this.callback.notifyUser(currentResult, currentState);
        }

        public void multiply(float number) 
        {
            this.currentResult *= number;
            this.currentState += "*" + number.ToString();
            this.callback.notifyUser(currentResult, currentState);
        }

        public void divide(float number) 
        {
            this.currentResult /= number;
            this.currentState += "/" + number.ToString();
            this.callback.notifyUser(currentResult, currentState);
        }
    }
}
