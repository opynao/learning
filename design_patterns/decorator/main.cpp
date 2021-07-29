#include <iostream>

#include "packet.h"
#include "tcp_ip_decorator.h"
#include "base_data_packet.h"
#include "application_layer.h"
#include "ip_layer.h"
#include "packet_crypt_decorator.h"

int main()
{
    std::shared_ptr<IPacket> packet = std::make_shared<BaseDataPacket>("Hello world!");
    packet = std::make_shared<PacketCryptoDecorator>(packet);
    packet = std::make_shared<ApplicationLayer>(packet);
    packet = std::make_shared<IpLayer>(packet);
    std::cout << packet->GetData();
    return 0;
}