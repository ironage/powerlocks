#ifndef SERIAL_H
#define SERIAL_H

#include <boost/asio.hpp>

class Serial
{
public:
    Serial(std::string port, unsigned int baud_rate);
    void writeString(std::string s);
    std::string readLine();

private:
    void lineReadHandler(const boost::system::error_code& e, std::size_t size);
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    boost::asio::streambuf readBuffer;
};


#endif // SERIAL_H
