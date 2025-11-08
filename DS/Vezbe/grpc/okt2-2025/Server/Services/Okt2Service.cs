using Grpc.Core;
using Okt2Proto;

namespace Server.Services
{
    public class Okt2Service : Okt2Proto.Okt2Service.Okt2ServiceBase
    {
        public override async Task IsSquare(
            IAsyncStreamReader<Numbers> inputStream,
            IServerStreamWriter<ResponseMessage> outputStream,
            ServerCallContext context)
        {
            await foreach (Numbers num in inputStream.ReadAllAsync()) 
            {
                if (IsSquareOfA(num.A, num.B)) 
                {
                    await outputStream.WriteAsync(new ResponseMessage { Message = "Da"});
                }

                await outputStream.WriteAsync(new ResponseMessage { Message = "N" });
            }
        }


        public bool IsSquareOfA(int a, int b) 
        {
            int square = a * a;
            if (b == square) return true;
            return false;
        }

    }
}
