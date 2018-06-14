#include <iostream>
#include <memory>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>

#include <SerialPort.h>

using std::cout;
using std::endl;

const unsigned char READ_CMD = 0x72;
const unsigned char WRITE_CMD = 0x77;
const unsigned char EOL = 0x0D;

const unsigned char CONTROLLER_ADDR = 0x20; // write

std::shared_ptr<LibSerial::SerialPort> serial_port_;

std::vector<unsigned char> receive_from_payload() {
    std::vector<unsigned char> rx_buf;
    bool done = false;
    do {
        char byte;
        //unsigned char byte = serial_port_->ReadByte(1000);
        serial_port_->ReadByte(byte, 1000);
        rx_buf.push_back(byte);
        done = (byte == '\r');
    } while (!done);
    return rx_buf;
}

void ack_signal_payload() {
    cout << "Acking signal" << endl;
    std::vector<unsigned char> output_buffer =
        {WRITE_CMD, CONTROLLER_ADDR, 0x00, 0x00, 0x32, 0x10, EOL};
    serial_port_->Write(output_buffer);
}

void print_buffer(std::vector<unsigned char> rx_buf,
                  bool hex = true) {
    for (unsigned char c : rx_buf) {
        if (hex) {
            printf("0x%02x ", c);
        } else {
            printf("%c", c);
        }
    }
    printf("\n");
}


int main(int argc, char *argv[]) {
    //serial_port_ = std::make_shared<LibSerial::SerialPort>("/dev/ttyUSB0");
    //serial_port_->Open(LibSerial::SerialPort::BaudRate::BAUD_115200,
    //                   LibSerial::SerialPort::CharacterSize::CHAR_SIZE_8,
    //                   LibSerial::SerialPort::Parity::PARITY_NONE,
    //                   LibSerial::SerialPort::StopBits::STOP_BITS_1,
    //                   LibSerial::SerialPort::FlowControl::FLOW_CONTROL_NONE);
    serial_port_ = std::make_shared<LibSerial::SerialPort>("/dev/ttyUSB0",
                                                           LibSerial::BaudRate::BAUD_115200,
                                                           LibSerial::CharacterSize::CHAR_SIZE_8,
                                                           LibSerial::FlowControl::FLOW_CONTROL_NONE,
                                                           LibSerial::Parity::PARITY_NONE,
                                                           LibSerial::StopBits::STOP_BITS_1
        );

    if (!serial_port_->IsOpen()) {
        cout << "Couldn't open serial port: " << endl;
        return -1;
    }

    {
        cout << "Build date: " << endl;
        std::vector<unsigned char> output_buffer = {READ_CMD, 0x00, 0x00, EOL};
        serial_port_->Write(output_buffer);
        std::vector<unsigned char> rx_buf = receive_from_payload();
        print_buffer(rx_buf);

        cout << "STATUS: " << endl;
        output_buffer = {READ_CMD, CONTROLLER_ADDR, 0x00, EOL};
        serial_port_->Write(output_buffer);
        rx_buf = receive_from_payload();
        print_buffer(rx_buf);
    }

    while (true) {
        std::cout << ">> ";
        std::string input;
        std::cin >> input;
        cout << "Arming payload" << endl;

        std::vector<unsigned char> output_buffer = {WRITE_CMD, CONTROLLER_ADDR, 0x00, 0x00, 0x32, 0x11, EOL};
        serial_port_->Write(output_buffer);
        std::vector<unsigned char> rx_buf = receive_from_payload();

        cout << "Ready" << endl;

        while(true) {
            std::vector<unsigned char> output_buffer = {READ_CMD, CONTROLLER_ADDR, 0x00, EOL};
            serial_port_->Write(output_buffer);
            std::vector<unsigned char> rx_buf = receive_from_payload();

            if (rx_buf.size() == 3 && (rx_buf[1] & 0x04) ) {
                print_buffer(rx_buf);
                cout << "Received: " << (rx_buf[0] & 0x0F) << endl;

                ///cout << "SLEEP" << endl;
                std::this_thread::sleep_for (std::chrono::seconds(1));
                //cout << "DONE" << endl;

                ack_signal_payload();

                serial_port_->FlushIOBuffers();

                break;
            }
            //std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        //std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    serial_port_->Close();
}
