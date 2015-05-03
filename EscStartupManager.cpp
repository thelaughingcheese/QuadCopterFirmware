#include "EscStartupManager.h"

EscStartupManager::EscStartupManager(Esc* escs,long n){
	esc = escs;
	size = n;
}

void EscStartupManager::startupAllNormal(){
	for(int i=0; i<size;i++){
		esc[i].set(esc[i].getMinPulse());
	}

	delay(5500);
}

void EscStartupManager::setConfigurationAll(EscConfiguration config){

}

void EscStartupManager::applyConfigurationAll(){

}