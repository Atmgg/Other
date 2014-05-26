#include <iostream>
#include <string>
#include "Data.pb.h"

int main()
{
        Data::Commodity honey;
        honey.set_name("JingTaiHoney1");
        honey.set_id(1);
        honey.set_price(66.5);
        honey.set_description("Healthy,Natural,Beauty");
        honey.set_discount(0.95);

        std::string str;
        honey.SerializeToString(&str);

        Data::Commodity unkown_commodity;
        unkown_commodity.ParseFromString(str);

        std::cout<<"Name:"<<unkown_commodity.name()<<std::endl;
        std::cout<<"Id:"<<unkown_commodity.id()<<std::endl;
        std::cout<<"Price:"<<unkown_commodity.price()<<std::endl;
        std::cout<<"Descripion:"<<unkown_commodity.description()<<std::endl;

        return 0;
        

}
