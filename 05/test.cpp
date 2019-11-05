#include <iostream>
#include <string>
#include <regex>

int main(){
    std::string buf;
    std::regex book_reg("^\"(.*)\" by (.*)$");
    while(std::getline(std::cin,buf)){
        std::smatch res;
        if(std::regex_search(buf,res,book_reg)){
            for(auto x : res){
                std::cout << x << "\n";
            }
        }
    }
    return 0;
}