/** @file main.cpp */
#ifndef SETTDEBUG_H
#define SETTDEBUG_H

#define ENABLE_TASK_CRIT
//#define ENABLE_TASK_ALERT
#define ENABLE_TASK_GEN

#define DBG_MAIN_INIT //enable to make sure all task is created
    #define DEBUG_INIT_TASKCRITT 1
    #define DBG_MAIN_DELAY_SEC 2 
#define DEBUG_BOOT_GRAPHICAL_INTERFACE // enable ANSI interface to view all process 
#define DEBUG_DIRECTIVE_GRAPHICAL_INTERFACE // enable ANSI interface to view directive process 

//#define DBG_MAIN_FLAG //Show Flag trought each process

#define DEBUG_TASKCRITT 1
    #define DGB_FORCE_INIT // use to brute force all patche to avoid bad reset.
    
#define DEBUG_MOUVEMENT_COMM_OFF    //disable comm with ssc-32

//#define DEBUG_LABYRINTHE_ADD_MAP //show process "addmap(char x, char y)"

#define DEGUG_LABIRINTH_GET_COORDONER
#define DEGUG_LABIRINTH_SET_COORDONER
#endif