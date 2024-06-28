using SourceSDK;

namespace RosneHookV2
{
    class ServerCrasher
    {
        static void Crash()
        {
          while(true) {
            SourceSDK.SendFaultyPacket();
          }
        }
    }
}
