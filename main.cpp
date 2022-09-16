#include <grpcpp/grpcpp.h>

#include <iostream>

namespace {

bool WaitForConnected(grpc::Channel* channel, uint64_t deadline_msec)
{
    bool timeout = channel->WaitForConnected(gpr_time_add(
        gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_millis(deadline_msec, GPR_TIMESPAN)));
    if (!timeout)
    {
        return false;
    }

    return (channel->GetState(false) == GRPC_CHANNEL_READY);
}

bool WaitForChannelConnected(grpc::Channel* channel, size_t connect_max_retry = 10)
{
    static const uint32_t kTimeoutForConnectionEstablishmentMsec = 1000;

    bool connected = false;
    for (size_t retry = 0; retry < connect_max_retry; ++retry)
    {
        if (!WaitForConnected(channel, kTimeoutForConnectionEstablishmentMsec))
        {
            continue;
        }

        connected = true;
        break;
    }

    return connected;
}

}    // namespace

int main(int, char**)
{
    std::cout << "Hello, world!\n";

    grpc::ChannelArguments args;
    auto channel = grpc::CreateCustomChannel(":50051", grpc::InsecureChannelCredentials(), args);

    if (channel)
    {
        WaitForChannelConnected(channel.get(), 3);
    }
}
