//
//  PSPatern.hpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#ifndef PSPatern_hpp
#define PSPatern_hpp

#include <stdio.h>
//this is to be the parent class of Human Agressive and Benevolent
class PlayerStrategyPattern {
public:
    PlayerStrategyPattern();
    virtual ~PlayerStrategyPattern();
};
//subclass of PlayerStrategyPattern
class Human : public PlayerStrategyPattern{
public:
    
};
//subclass of PlayerStrategyPattern
class Agressive;
//subclass of PlayerStrategyPattern
class Benevolent;


#endif /* PSPatern_hpp */
