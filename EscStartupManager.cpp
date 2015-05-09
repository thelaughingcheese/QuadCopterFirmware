#define CONFIG_ITEM_DELAY delay(5000);
#define CONFIG_OPTION_DELAY delay(3000);

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

	DEBUGSPRINTLN("esc programming start!");

	//set brake
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("select brake");
	throttleAllMin();
	do{
		CONFIG_OPTION_DELAY
		if(config.brake == config.BRAKE_OFF){
			DEBUGSPRINTLN("break off");
			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
		if(config.brake == config.BRAKE_ON){
			DEBUGSPRINTLN("break on");
  			throttleAllMax();
			break;
		}
		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);

	//set battery type
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("select battery type");
	throttleAllMin();
	do{
		CONFIG_OPTION_DELAY
		if(config.batteryType == config.LIPO){
			DEBUGSPRINTLN("lipo");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
		if(config.batteryType == config.NICD){
			DEBUGSPRINTLN("nicd");
			break;
		}
		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);

	//set cutoff mode
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("select cutoff mode");
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
		if(config.cutoffMode == config.SOFT_CUTOFF){
			DEBUGSPRINTLN("soft cutoff");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
		if(config.cutoffMode == config.HARD_CUTOFF){
			DEBUGSPRINTLN("hard cutoff");
  			throttleAllMax();
			break;
		}
		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);

	//set cutoff threshold
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("select cutoff threshold");
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
  		if(config.cutoffThreshold == config.LOW_THRESHOLD){
			DEBUGSPRINTLN("low thresh");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
  		if(config.cutoffThreshold == config.MEDIUM_THRESHOLD){
			DEBUGSPRINTLN("med thresh");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
  		if(config.cutoffThreshold == config.HIGH_THRESHOLD){
			DEBUGSPRINTLN("high thresh");
  			throttleAllMax();
			break;
		}
  		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);

	//set startup mode
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("select startup mode");
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
    	if(config.startMode == config.NORMAL_START){
			DEBUGSPRINTLN("normal start");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    	if(config.startMode == config.SOFT_START){
				DEBUGSPRINTLN("soft start");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    	if(config.startMode == config.SUPERSOFT_START){
			DEBUGSPRINTLN("supersoft start");
  			throttleAllMax();
			break;
		}
  		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);

	//set timing
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("select timing");
	throttleAllMin();
	do{
  		CONFIG_OPTION_DELAY
    	if(config.timing == config.LOW_TIMING){
			DEBUGSPRINTLN("low timing");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    	if(config.timing == config.MEDIUM_TIMING){
			DEBUGSPRINTLN("med timing");
  			throttleAllMax();
			break;
		}
		CONFIG_OPTION_DELAY
    	if(config.timing == config.HIGH_TIMING){
			DEBUGSPRINTLN("high timing");
  			throttleAllMax();
			break;
		}
  		DEBUGSPRINTLN("esc config didn't make selection!");
	}while(0);

	//skip default
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("skip factory reset");

	//exit
	CONFIG_ITEM_DELAY
	DEBUGSPRINTLN("done esc config");
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
