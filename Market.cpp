//
// Created by Cephas Svosve on 10/6/2022.
//

#include "Market.h"
#include "price_setter.h"
#include "market_watch.h"
#include <fstream>


int main(){

    int passive_share;
    std::cout<<" Share of passive investment(in units of 0.5%): ";
    std::cin >> passive_share;

    double market_wealth = 1.68e10;
    double shares_outstanding = 0.5*market_wealth/9;
    double market_cash = 0.5*market_wealth;
    double passive_investment= passive_share * 0.005;


    market_watch watch(market_watch::one_second);


//Define the price setter
    price_setter market_;
    market_.set_clock(&watch);



//create assets and register stocks to the market
    market_.register_assets(3);
    market_.generate_fundamentals();


//generate initial quotes
    market_.set_initial_quotes();

//set price setter's wealth
    market_.initial_wealth(0.5*market_cash, 0.5*shares_outstanding);



//initialize traders
    funds
            aggressive_value
            ,aggressive_noisy
            ,aggressive_momentum
            ,aggressive_growth
            ,aggressive_index
    ;


    vector<funds*> participants = {
            &aggressive_value
            ,&aggressive_noisy
            ,&aggressive_momentum
            ,&aggressive_growth
            ,&aggressive_index

    };



//number of participants
    double investor_population = participants.size();
//inform traders about assets on the market
    for(auto &p : participants){
        p->set_clock(&watch);
        p->get_inform(market_.tradeable_assets());
    }


    aggressive_value.trade_strategy(funds::aggressive_fundamental_value);
    aggressive_value.set_reb_period(63);
    aggressive_value.initial_wealth((1/(investor_population))*0.5*market_cash *(1-passive_investment)
            ,(1/(investor_population))*0.5*shares_outstanding*(1-passive_investment));


    aggressive_growth.trade_strategy(funds::aggressive_growth);
    aggressive_growth.set_reb_period(63);
    aggressive_growth.initial_wealth((1./(investor_population))*0.5*market_cash*(1-passive_investment)
            ,(1./(investor_population))*0.5*shares_outstanding*(1-passive_investment));

    aggressive_noisy.trade_strategy(funds::aggressive_noise);
    aggressive_noisy.set_reb_period(1);
    aggressive_noisy.initial_wealth((1/(investor_population))*0.5*market_cash*(1-passive_investment)
            ,(1/(investor_population))*0.5*shares_outstanding*(1-passive_investment));


    aggressive_momentum.trade_strategy(funds::aggressive_momentum_investment);
    aggressive_momentum.set_reb_period(21);
    aggressive_momentum.initial_wealth((1./(investor_population))*0.5*market_cash*(1-passive_investment)
            ,(1./(investor_population))*0.5*shares_outstanding*(1-passive_investment));

    aggressive_momentum.trade_strategy(funds::aggressive_index);
    aggressive_momentum.set_reb_period(63);
    aggressive_momentum.initial_wealth((1./(investor_population))*0.5*market_cash*(passive_investment)
            ,(1./(investor_population))*0.5*shares_outstanding*(passive_investment));
//


//register traders on the market
    market_.register_traders(participants);


//market simulation run point
    std::ofstream myfile;
    std::string file_name = "Experiment_" + std::to_string(passive_share);
    file_name += ".csv";
    myfile.open (file_name);

    watch.start();
    int day_count = 0;
    while(day_count < 5) {

        //adjust traders' balances for interest and dividends


        if (day_count < int((&watch)->current_time())) {
            for (auto &p : participants) {
                p->balance_cf(int((&watch)->current_time()));
            }
        }



//receive orders from traders

        market_.receive_orders();

//clear market



        if (day_count < int((&watch)->current_time())) {
            for (auto &[k, v] : market_.tradeable_assets()) {
//                if (result.find(k)!= result.end()){
//                    result.find(k)->second.push_back(v.get_midprice());
//                }else{
//                    result.emplace(k,(v.get_midprice()));
//                }


                myfile << k << "," << (v.get_midprice()) << ",";
                myfile << v.get_value((&watch)->current_time()) << ",";


}
            std::cout << std::endl;
            myfile << std::endl;
            day_count++;
        }
        market_.clear(watch);
        std::cout << "market's watch time " << (&watch)->current_time() << std::endl;
    }


    myfile.close();
    return 0;
}
