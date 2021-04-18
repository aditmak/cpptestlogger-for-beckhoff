// cpptestlogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Include General Libraries
#include <iostream>
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

//Include ADS Libraries
#include "Windows.h"
#include "TcAdsDef.h"
#include "TcAdsAPI.h"

//Include Logger Libraries
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"



int main()
{   
    //Initializations
    AmsAddr Addr;
    PAmsAddr pAddr = &Addr;
    long nErr, nPort;
    long float SetPos, ActPos;
    int SetVelo;
    double ActVelo;
    int n = 0;
    
    //Operation
    try
    {
        //Logger Settings
        //Setting for Console Logger
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::warn);
        console_sink->set_pattern("[Phantom_Realtime] [%^%l%$] %v");//[Phantom_Realtime] [%^%l%$] %v

        //Setting for file logger
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
        file_sink->set_level(spdlog::level::trace);

        spdlog::sinks_init_list sink_list = { file_sink, console_sink };

        spdlog::logger logger("Phantom_Realtime", sink_list.begin(), sink_list.end());
        logger.set_level(spdlog::level::debug);

        //Open communication for ADS router
        nPort = AdsPortOpen();
        nErr = AdsGetLocalAddress(pAddr);
        
        if (nErr) {logger.error("AdsGetLocalAddress failed: {} -- Error Code", nErr);}
        
        //Port Number
        pAddr->port = 0x8888;
        
        logger.error("Welcome to C++ TwinCAT Logger");
        logger.info("***************************************************************");
        logger.error("Login started");
        
        while (nErr == 0){
            //Project specific changes go here!
            //This code is for Phantom Robot (RWTH Aachen)
            nErr = AdsSyncReadWriteReq(pAddr, 1, 1, sizeof(SetPos), &SetPos, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq SetPos failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 1, 3, sizeof(SetVelo), &SetVelo, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq SetVelo failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 1, 2, sizeof(ActPos), &ActPos, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq ActPos failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 1, 4, sizeof(ActVelo), &ActVelo, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq ActVelo failed: {} -- Error Code", nErr);
            
            logger.warn("TimeDiff: {},   Index: {}", SetPos, SetVelo);
            
            logger.warn("M1:  TimeinData: {} ActPos: {}",  ActVelo, ActPos);
            
            nErr = AdsSyncReadWriteReq(pAddr, 2, 1, sizeof(SetPos), &SetPos, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq SetPos failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 2, 3, sizeof(SetVelo), &SetVelo, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq SetVelo failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 2, 2, sizeof(ActPos), &ActPos, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq ActPos failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 2, 4, sizeof(ActVelo), &ActVelo, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq ActVelo failed: {} -- Error Code", nErr);
            
            logger.warn("M2: TimeinData: {} ActPos: {}", ActVelo, ActPos);

            nErr = AdsSyncReadWriteReq(pAddr, 3, 1, sizeof(SetPos), &SetPos, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq SetPos failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 3, 3, sizeof(SetVelo), &SetVelo, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq SetVelo failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 3, 2, sizeof(ActPos), &ActPos, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq ActPos failed: {} -- Error Code", nErr);
            nErr = AdsSyncReadWriteReq(pAddr, 3, 4, sizeof(ActVelo), &ActVelo, 0, NULL);
            if (nErr) logger.error("AdsSyncReadReq ActVelo failed: {} -- Error Code", nErr);
            
            logger.warn("M3: TimeinData: {} ActPos: {}", ActVelo, ActPos);
            Sleep(2);
        }
    
        //Logging
        logger.warn("Finished!");
        logger.info("***************************************************************");
        
        // or you can even set multi_sink logger as default logger
        //spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({ console_sink, file_sink })));

    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }

 }

