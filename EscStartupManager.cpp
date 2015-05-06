#define CONFIG_ITEM_DELAY delay(2);
#define CONFIG_OPTION_DELAY delay(2);

#include "Globals.h"
#include "EscStartupManager.h"

EscStartupManager::EscStartupManager(Esc* escs,long n){
	esc = escs;
	size = n;
}

void EscStartupManager::startupAllNormal(){
	throttleAllMin();

	delay(5500);
}

void EscStartupManager::applyRange(){
	throttleAllMax();//max throttle
	delay(2000);//wait 2s
	throttleAllMin();//min throttle
	delay(4000);//wait 4s
}

void EscStartupManager::setConfigurationAll(EscConfiguration cfg){
	config = cfg;
}

void EscStartupManager::applyConfigurationAll(){
	//enter programming mode
	throttleAllMax();
	delay(7000);

	//set brake
	throttleAllMin();
	do{
		if(config.brake == config.BRAKE_OFF){
			throttleAllMax();
			break;
		}
		if(config.brake == config.BRAKE_ON){
  			throttleAllMax();
			break;
		}
		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);
	CONFIG_ITEM_DELAY

	//set battery type
	throttleAllMin();
	do{
		CONFIG_OPTION_DELAY
		if(config.batteryType == config.LIPO){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
		if(config.batteryType == config.NICD){
  			throttleAllMax();
			break;
		}
		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);
	CONFIG_ITEM_DELAY

	//set cutoff mode
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
		if(config.cutoffMode == config.SOFT_CUTOFF){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
		if(config.cutoffMode == config.HARD_CUTOFF){
  			throttleAllMax();
			break;
		}
		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);
	CONFIG_ITEM_DELAY

	//set cutoff threshold
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
  		if(config.cutoffThreshold == config.LOW_THRESHOLD){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
  		if(config.cutoffThreshold == config.MEDIUM_THRESHOLD){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
  		if(config.cutoffThreshold == config.HIGH_THRESHOLD){
  			throttleAllMax();
			break;
		}
  		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);
	CONFIG_ITEM_DELAY

	//set startup mode
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
    		if(config.startMode == config.NORMAL_START){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    		if(config.startMode == config.SOFT_START){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    		if(config.startMode == config.SUPERSOFT_START){
  			throttleAllMax();
			break;
		}
  		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);
	CONFIG_ITEM_DELAY

	//set timing
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
    		if(config.timing == config.LOW_TIMING){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    		if(config.timing == config.MEDIUM_TIMING){
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    		if(config.timing == config.HIGH_TIMING){
  			throttleAllMax();
			break;
		}
  		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);
	CONFIG_ITEM_DELAY

	//skip default
	delay(0);

        //exit
        delay(0);
	throttleAllMin();
}

void EscStartupManager::throttleAllMin(){
	for(int i=0; i<size;i++){
		esc[i].set(esc[i].getMinPulse());
	}
}

void EscStartupManager::throttleAllMax(){
	for(int i=0; i<size;i++){
		esc[i].set(esc[i].getMaxPulse());
	}
}
