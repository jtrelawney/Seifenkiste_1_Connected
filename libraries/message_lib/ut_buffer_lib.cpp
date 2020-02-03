#include <header_buffer.hpp>
#include <iostream>

void read_buffer(header_buffer_class &buffer){
    unsigned int id;
    buffer.get_buffer_data(id,0);
    float k;
    buffer.get_buffer_data(k,sizeof(unsigned int));
    std::cout << "reading id = " << id << "   k = " << k << std::endl;
}

void write_buffer(header_buffer_class &buffer){
    unsigned int id = 5;
    float k = 3.14;
    std::cout << "writing id = " << id << "   k = " << k << std::endl;
    buffer.set_buffer_data(id,0);
    buffer.set_buffer_data(k,sizeof(unsigned int));
}

int main(){
    std::string red_text = "\033[1;31m";
    std::string normal_text = "\033[0m";

    header_buffer_class buffer;
    write_buffer(buffer);
    read_buffer(buffer);

    std::cout << "\n\n" + red_text + "writing with improper buffer pos, this could fail with error" + normal_text << std::endl;
    unsigned int id = 5;
    unsigned int pos = buffer.get_buffer_length()-sizeof(id);
    std::cout <<"pos = " << pos << std::endl;
    buffer.set_buffer_data(id,pos-1);
    buffer.print_header_buffer_content();
    std::cout << "\n\n" + red_text + "nreading with improper buffer pos, this could fail with error" + normal_text << std::endl;
    buffer.get_buffer_data(id,pos);
}
