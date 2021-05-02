//#include <boost/asio.hpp>
//#include <cassert>
//#include <cstdlib>
//#include <exception>
//#include <iostream>
//#include <sstream>
//#include <utility>
//
//using boost::asio::ip::tcp;
//
//int main(int argc, char *argv[]) {
//    {
//        argc = 2;
//        argv[1] = "23";
//    }
//    assert(argc == 2);
//
//    boost::asio::io_context io_context;
//
//    // описание сокета на котором нужно начать слушать
//    tcp::acceptor acceptor(io_context,
//                           tcp::endpoint(tcp::v4(), std::atoi(argv[1])));
//    // можно узнать на каком порту слушает
//    std::cout << "Listening at " << acceptor.local_endpoint() << "\n";
//
//    tcp::iostream client([&]() {
//        // блокируется пока не подключится новый клиент
//        tcp::socket s = acceptor.accept();
//        // откуда куда
//        std::cout << "Connected " << s.remote_endpoint() << " --> "
//                  << s.local_endpoint() << "\n";
//        return s;
//    }());
//
//    // пока активен
//    while (client) {
//        std::string s;
//        client >> s;
//        client << "string: " << s << "\n";
//    }
//    std::cout << "Completed\n";
//    return 0;
//}