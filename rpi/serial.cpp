#include "serial.h"

#include <string>
#include <boost/asio.hpp>
#include <thread>

void lineReadHandler(const boost::system::error_code& e, std::size_t size);
Serial* Serial::lastInstance = 0;
/**
 * Constructor.
 * \param port device name, example "/dev/ttyUSB0" or "COM4"
 * \param baud_rate communication speed, example 9600 or 115200
 * \throws boost::system::system_error if cannot open the
 * serial device
 */
Serial::Serial(std::string port, unsigned int baud_rate)
    : io(), serial(io,port)
{
    serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    boost::asio::async_read_until(serial, readBuffer, '\n', lineReadHandler);
    lastInstance = this;
}

/**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
void Serial::writeString(std::string s)
{
    boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
}

/**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
std::string Serial::readLine()
{
    //Reading data char by char, code is optimized for simplicity, not speed
    using namespace boost;
    char c;
    std::string result;
    for(;;)
    {
        asio::read(serial,asio::buffer(&c,1));
        switch(c)
        {
        case '\r':
            break;
        case '\n':
            return result;
        default:
            result+=c;
        }
    }
}

void lineReadHandler(const boost::system::error_code& e, std::size_t size) {
  if (!e) {
    std::istream is(&Serial::lastInstance->readBuffer);
    std::string line;
    std::getline(is, line);
    //handle this line
  }
  if (Serial::lastInstance) {
    boost::asio::async_read_until(Serial::lastInstance->serial, Serial::lastInstance->readBuffer, '\n', lineReadHandler);
  }
}
