#include <address_class.hpp>
#include <iostream>

int main(){
    //
    address_class t1(address_class::Platform_def::pc,address_class::Sensor_def::camera1,address_class::Process_def::undefined);
    address_class t2(address_class::Platform_def::pc,address_class::Sensor_def::camera1,address_class::Process_def::undefined);
    address_class t3(address_class::Platform_def::undefined_platform,address_class::Sensor_def::camera1,address_class::Process_def::cockpit);
    std::cout << "address 1 = " << t1 << std::endl;
    std::cout << "address 2 = " << t2 << std::endl;
    if (t1 == t2) std::cout << "addresses are equal" << std::endl;
    else std::cout << "addresses are different" << std::endl;
    std::cout << "\n\naddress 1 = " << t1 << std::endl;
    std::cout << "address 3 = " << t3 << std::endl;
    if (t1 == t3) std::cout << "addresses are equal" << std::endl;
    else std::cout << "addresses are different" << std::endl;
}
