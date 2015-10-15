/** @file main.cpp */
#ifndef SETTDEBUG_H
#define SETTDEBUG_H

#define DEBUG_DIRECTIVE_TEST_CAPTEUR

#define ENABLE_TASK_CRIT
//#define ENABLE_TASK_ALERT
#define ENABLE_TASK_GEN

#define DBG_MAIN_INIT //enable to make sure all task is created
    #define DEBUG_INIT_TASKCRITT 1
    //#define DBG_MAIN_DELAY_SEC .2 
#define DEBUG_BOOT_GRAPHICAL_INTERFACE // enable ANSI interface to view all process 
//#define DEBUG_DIRECTIVE_GRAPHICAL_INTERFACE // enable ANSI interface to view directive process 
    #define DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE 0 /*enable debug for maze*/
//#define DEBUG_LABYRINTHE_GRAPHICAL_INTERFACE

//#define DBG_MAIN_FLAG //Show Flag trought each process

#define DEBUG_TASKCRITT 0
    //#define DGB_FORCE_INIT // use to brute force all patche to avoid bad reset.
    
//#define DEBUG_MOUVEMENT_COMM_OFF    //disable comm with ssc-32

//#define DEBUG_DIRECTIVE_LEG_DISABLE //skip all linked whit the control of leg
//#define DEBUG_DIRECTIVE_LABYRINTH_USER_CTRL // chose manualy what robot see
//#define DEBUG_LABYRINTHE_ADD_MAP //show process "addmap(char x, char y)"
#define DEBUG_DIRECTIVE_TEST 0
#define DEBUG_DIRECTIVE_TRAITEMENT 1
#define DEBUG_DIRECTIVE_LABYRINTH 1
#define DEBUG_DIRECTIVE_SHOW_MAP_LABYRINTH
#define DIRECTIVE_IR_BUFFER_LENGHT  3/*1*/
#define DIRECTIVE_ULTRASONIC_BUFFER_LENGHT /*3*/1
#define DIRECTIVE_IR_LIMIT_SHORT    15
#define DIRECTIVE_IR_LIMIT_MIDDLE   33
#define DIRECTIVE_IR_LIMIT_LONG     50

#define DIRECTIVE_ULTRASONIC_LIMIT_SHORT    13
#define DIRECTIVE_ULTRASONIC_LIMIT_MIDDLE   33
#define DIRECTIVE_ULTRASONIC_LIMIT_LONG     50
#define DEBUG_DIRECTIVE_UPDATE_MODULE
//#define DEGUG_LABIRINTH_GET_CASE
//#define DEGUG_LABIRINTH_GET_COORDONER
//#define DEGUG_LABIRINTH_SET_COORDONER
//#define DEBUG_LABYRINTHE_ADD_MAP
//#define DEBUG_LABYRINTHE_SHOW_MAP

#define DEBUG_HOMEMADESEQ_PERCENT_DELAIS 100
#define DEBUG_HOMEMADESEQ_PERCENT_DELAIS_PAUSE 50
#define DEBUG_HOMEMADE_GETFRAME 0
#define DEBUG_HOMEMADE_GETTIME 0
#define DEBUG_HOMEMADE_NEXTFRAME 0
#define DEBUG_HOMEMADE_PREVFRAME 0
#define DELAITESTE 1000
#endif