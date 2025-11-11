using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Lab1Namespace;

namespace Server.Properties
{
    public class Lab1Service : Lab1Namespace.Lab1Service.Lab1ServiceBase
    {

        public int acc;

        public Task<Empty> proslediBroj(Broj broj, ServerCallContext context) 
        {
            int srednjaVrednostManjih = 0;
            int brojac = 0;
            for (int i = 1; i <= broj.Vrednost; i++) 
            {
                brojac++;
                srednjaVrednostManjih += i;
            }
            srednjaVrednostManjih /= brojac;
            this.acc += srednjaVrednostManjih;

            return Task.FromResult(new Empty());
            
        }


        public async Task proslediTok(IAsyncStreamReader<Broj> inputStream, IServerStreamWriter<Broj> outputStream,
            ServerCallContext context) 
        {
            int counter = 0;
            await foreach (Broj broj in inputStream.ReadAllAsync()) 
            {
                counter++;

                if (counter % 3 == 0)
                {
                    broj.Vrednost *= acc;
                    await outputStream.WriteAsync(new Broj() { Vrednost = broj.Vrednost});
                }
                else 
                {
                    broj.Vrednost -= acc;
                    await outputStream.WriteAsync(new Broj() { Vrednost = broj.Vrednost});
                }
            }

        }

    }
}
