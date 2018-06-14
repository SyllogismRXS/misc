#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

    // 1048576

    double time = 0.01048576;
    const double clock_period = 10e-9;
    unsigned int counts = static_cast<unsigned int>(std::round(time / clock_period));
    uint16_t rx_blank_time_ = static_cast<uint16_t>(counts >> 12);
    cout << "rx_blank_time: " << rx_blank_time_ << endl;
    printf("0x%04x\n", rx_blank_time_);


    uint8_t tx_sel_a_ = 0x01;
    uint8_t tx_sel_b_ = 0x02;
    uint8_t tx_sel_c_ = 0x03;
    bool armed_bit_ = true;

    printf("0 - 0x%02x\n", rx_blank_time_ >> 8);
    printf("1 - 0x%02x\n", rx_blank_time_ & 0x00FF);
    printf("2 - 0x%02x\n", ((tx_sel_c_ << 4) & 0xF0) | (tx_sel_b_ & 0x0F));
    printf("3 - 0x%02x\n", ((tx_sel_a_ << 4) & 0xF0) | (armed_bit_ & 0x01));



    //uint8_t tx_sel_a_ = 0x01;
    //uint8_t tx_sel_b_ = 0x02;
    //uint8_t tx_sel_c_ = 0x03;

    //cout <<

    return 0;
}
