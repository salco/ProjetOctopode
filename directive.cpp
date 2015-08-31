
#include "directive.h"
Serial pc(SERIAL_TX, SERIAL_RX);
int tabIR[12][2]= {
    {80, 400},{50, 600},{40, 700},{30, 900},{25,1100},
    {20,1300},{15,1600},{10,2400},{ 8,2700},{ 7,3000},
    { 6,3200},{ 5,3100}
};






Directive::Directive():TTask(0)//on veux que cette tache sois exec toute les fois que TTaskGen sexecute.
{
    /* initialize random seed: */
    srand (time(NULL));
    myMaze = new Labyrinthe();
    
    myMaze->setDirection(UP);
    //c=0;
    ssc32 = new /*Serial*//*Raw*/Serial/*(USBTX, USBRX);*/(PB_6, PB_7);//(PA_9, PA_10);
    ctrDesPattes = new Faculter_motrice(ssc32/*pc*/);
    m_valueCapteurUltrasonic = 0;
    m_valueCapteurIR = 0;
    m_valueCapteurProximiter = 0;
    for(int i =0; i<10; i++)tableauDeCommange[i]= 0;
    size_tableauDeCommange=0;
    myMaze->setC(EXPLORER,C5);
    //m_CtrlBridge = m_CtrlBridge->getInstance();
    //a enlever de commentaire//m_ListDesModules = m_CtrlBridge->findModule(0,1,0,0);

    //Serial pc(USBTX, USBRX);

    //ssc32->set_flow_control(0);

    myMaze = new Labyrinthe();
    debug("\n\r directive Init");//printf("Hello World\n");
    m_ListDesModules = m_CtrlBridge->findModule(0,CAPTEUR,DISTANCE,0);
    m_ListDesModules.append(m_CtrlBridge->findModule(0,CAPTEUR,PROXIMITEE,0));

    m_capteurUltrasonic= m_CtrlBridge->findModule(0,CAPTEUR,ULTRASONIQUE,0x27/*0b100111*/);
        if(!(m_capteurUltrasonic.empty()))debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurUltrasonic found");
        else debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurUltrasonic not found");
    m_capteurIR= m_CtrlBridge->findModule(0,CAPTEUR,DISTANCE,0x27/*0b100111*/);
        if(!(m_capteurIR.empty()))debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurIR found");
        else debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurIR not found");
    m_capteurProximiter= m_CtrlBridge->findModule(0,CAPTEUR,PROXIMITEE,0x0E/*0b001110*/);
        if(!(m_capteurProximiter.empty()))debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurProximiter found");
        else debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurProximiter not found");

    ctrDesPattes->moveUp();

    bool getUp=true;
    while((getUp)&& (! ctrDesPattes->isSeqComplet())) {
        ctrDesPattes->exec();

        if(ctrDesPattes->get_idFrame() >= 5)
            getUp = false;

    }
    
    ctrDesPattes->calibre();
    
    #ifdef DEBUG_BOOT_GRAPHICAL_INTERFACE
    wait(2);
    debug("\x1B[2J"); //clear screen
    debug("\x1B[25l");//hide cursor
    debug("\x1B[;H"); //cursor default position
    
    //createSLbox(0,0,5,15,"Mode");
    createDLbox(0,0,10,20,"Menu");//(1,12,10,20,"test2");
    setText(1,3,"1) BrainControle");
    setText(1,4,"2) Show Maze");
    //createDLbox(16,0,5,15,"Stage");
    
    #endif
}
Directive::~Directive()
{

    if(ctrDesPattes)
        delete ctrDesPattes;
    if(ssc32)
        delete ssc32;
    if(myMaze)
        delete myMaze;
}
void Directive::task(void)//ALL CODE HERE//
{
       
       #ifdef DEBUG_BOOT_GRAPHICAL_INTERFACE
    if(pc.readable()){
        
    debug("\x1B[2J"); //clear screen
    debug("\x1B[25l");//hide cursor
    debug("\x1B[;H"); //cursor default position
    
    
    int idCommand;
    
    idCommand = fgetc(pc) - '0';
    switch(idCommand)
    {
        case 1:
            createDLbox(0,0,10,25,"BrainControle");    
            setText(1,3,"1) Move Up");
            setText(1,4,"2) Move Down");
            setText(1,5,"2) Move Left");
            setText(1,6,"2) Move Right");
        break;
        
        case 2:
            createDLbox(0,0,10,20,"Show Maze");    
        break;
    }
    }
    #endif
    //debug(DEBUG_DIRECTIVE_TEST,"\n\rIn task directive");
    if(ctrDesPattes->isSeqComplet()) {
        if((tableauDeCommange[0] == 6) && (size_tableauDeCommange == 1)) {
            //addTableauDeCommande(0x81);
            //addTableauDeCommande(0x82);
            //mabey//addTableauDeCommande(0x83);
            addTableauDeCommande(0x84);

            //addTableauDeCommande(0x85);
            //mabey//addTableauDeCommande(0x86);
            addTableauDeCommande(0x87);
            addTableauDeCommande(0x88);
        }
        if(tableauDeCommange[0] == 0) {
            //pas sur que c'Est tout ce qui doit etre ici mais je vois pas quoi d'autre pour le moment.

            ////////////////
            // Inspection //
            ////////////////
            //flag.append(1,0);//0x02);
            /*for(int i=0; i<m_ListDesModules.length(); ++i) {
                wait_us(300);
                flag.clear();
                flag.append(1,7);
                data.clear();
                debug("\n\r result: %d",m_CtrlBridge->send(m_ListDesModules.at(i),flag,data));

                debug("\n\r flag: %d",flag[0]);
                debug("\n\r data: %x",data[0]);
            }*/
#ifndef BACKUP
            updateModuleValue();

            //////////////////////////////
            // Traitement du Labyrinthe //
            //////////////////////////////
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -IRToCm(%02f): %02f",ADCTomv(m_valueCapteurIR),IRToCm(ADCTomv(m_valueCapteurIR)));
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -ultrasonicToInch: %02f",ultrasonicToInch(m_valueCapteurUltrasonic));
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -m_valueCapteurProximiter: %02d",m_valueCapteurProximiter);

            analiseMaze();
            char nextCase=0;
            switch(myMaze->getDirection()) {
                case UP:
                    nextCase = myMaze->getC(myMaze->getX(),myMaze->getY()+1);
                    break;

                case DOWN:
                    nextCase = myMaze->getC(myMaze->getX(),myMaze->getY()-1);
                    break;

                case LEFT:
                    nextCase = myMaze->getC(myMaze->getX()-1,myMaze->getY());
                    break;

                case RIGHT:
                    nextCase = myMaze->getC(myMaze->getX()+1,myMaze->getY());
                    break;
            }

            switch(nextCase ) {
                case VIDE:
                    debug(DEBUG_DIRECTIVE_TEST," Javance");
                    addTableauDeCommande(6);
                    break;

                case EXPLORER:// ici pt amiliorer
                    debug(DEBUG_DIRECTIVE_TEST," Javance");
                    addTableauDeCommande(6);
                    break;

                case MUR:

                    switch(myMaze->getDirection()) {
                        case UP:
                            if(rand()%1) {
                                nextCase = myMaze->getC(myMaze->getX()-1,myMaze->getY());
                                if(nextCase != MUR) {
                                }
                                nextCase = myMaze->getC(myMaze->getX()+1,myMaze->getY());
                            } else {
                                nextCase = myMaze->getC(myMaze->getX()+1,myMaze->getY()+1);
                            }
                            break;

                        case DOWN:
                            nextCase = myMaze->getC(myMaze->getX(),myMaze->getY()-1);
                            break;

                        case LEFT:
                            nextCase = myMaze->getC(myMaze->getX()-1,myMaze->getY());
                            break;

                        case RIGHT:
                            nextCase = myMaze->getC(myMaze->getX()+1,myMaze->getY());
                            break;
                    }

                    break;

                case PAS_EXPLORER:
                    debug(DEBUG_DIRECTIVE_TEST," Javance");
                    addTableauDeCommande(6);
                    break;
            }

#endif
#if BACKUP
            /*if((ultrasonicToInch(m_valueCapteurUltrasonic)< 1) && (IRToCm(ADCTomv(m_valueCapteurIR)) <= 80)) //capteur ultrasson embrouiller/imprecis
            {
                debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Capteur Ultrasson brouiller");
                addTableauDeCommande(6);
                }
            else if(ultrasonicToInch(m_valueCapteurUltrasonic) < 10) { //plus proche que 10pouce
                debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche");
                if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 10) {
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
                    addTableauDeCommande(7);


                    //ici potentielle scaning
                } else {
                    addTableauDeCommande(4);
                    addTableauDeCommande(4);
                    addTableauDeCommande(4);
                }
            } else {
                debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Nothing:");
                addTableauDeCommande(6);


                int randomNbr = rand() % 4;
                switch(randomNbr)
                {
                    case 1:
                    debug(DEBUG_DIRECTIVE_TEST," Javance");
                    addTableauDeCommande(6);
                    break;
                    case 2:
                    debug(DEBUG_DIRECTIVE_TEST," Je tourne a gauche");
                    addTableauDeCommande(4);
                    break;
                    case 3:
                    debug(DEBUG_DIRECTIVE_TEST," Je tourne a droite");
                    addTableauDeCommande(5);
                    break;
                    default:
                    debug(DEBUG_DIRECTIVE_TEST," Jattend");
                    break;
                    }


                //addTableauDeCommande(6);
            }*/
#endif
            ///////////////
            // Mouvement //
            ///////////////
        } else {
            switch(tableauDeCommange[0]) {
                case 11:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_calibre");
                    ctrDesPattes->calibre();
                    break;
                case 2:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_moveUp");
                    ctrDesPattes->moveUp();
                    break;
                case 3:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_moveDown");
                    ctrDesPattes->moveDown();
                    break;
                case 4:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_turnLeft");
                    ctrDesPattes->turnLeft();
                    break;
                case 5:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_trunRight");
                    ctrDesPattes->trunRight();
                    break;
                case 6:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_moveFront");
                    ctrDesPattes->moveFront();
                    break;
                case 7:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_moveBack");
                    ctrDesPattes->moveBack();
                    break;
                    /*case 8:
                    ctrDesPattes->moveBack();
                    break;*/
                case 0x81:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 1");
                    ctrDesPattes->repositioner(1);
                    break;
                case 0x82:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 2");
                    ctrDesPattes->repositioner(2);
                    break;
                case 0x83:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 3");
                    ctrDesPattes->repositioner(3);
                    break;
                case 0x84:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 4");
                    ctrDesPattes->repositioner(4);
                    break;
                case 0x85:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 5");
                    ctrDesPattes->repositioner(5);
                    break;
                case 0x86:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 6");
                    ctrDesPattes->repositioner(6);
                    break;
                case 0x87:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 7");
                    ctrDesPattes->repositioner(7);
                    break;
                case 0x88:
                    debug(DEBUG_DIRECTIVE_TEST,"\n\r        -set_Repositioner 8");
                    ctrDesPattes->repositioner(8);
                    break;
            }
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -TAB:");
            for(int i =0; i<10; i++) debug(DEBUG_DIRECTIVE_TEST,"[%02x]",tableauDeCommange[i]);
            for(int i =0; i<9; i++)tableauDeCommange[i]= tableauDeCommange[i+1];
            tableauDeCommange[9]=0;
            if(size_tableauDeCommange != 0) size_tableauDeCommange--;
        }
    } else {
        ctrDesPattes->exec();
    }
    ////////////////////
    // Update memoire //
    ////////////////////

    ////////////
    // Autre? //
    ////////////


    //debug(DEBUG_DIRECTIVE_TEST,"\n\rOut task directive");
}
double Directive::IRToCm (double miliVolt)
{
    double result=0;

    if(miliVolt < tabIR[0][1])result = tabIR[0][0];
    else if(miliVolt > tabIR[11][1])result = tabIR[11][0];

    for(int i =1; (result==0)&&(i<12); i++) {
        if((tabIR[i-1][1]<=miliVolt) && (tabIR[i][1]>miliVolt)) {
            result=tabIR[i-1][0]+((tabIR[i][0]-tabIR[i-1][0])*((tabIR[i-1][1]-miliVolt)/(tabIR[i-1][1]-tabIR[i][1])));
        }
    }
    return result;
}
void Directive::addTableauDeCommande(unsigned char value)
{
    if(size_tableauDeCommange!=10) {
        tableauDeCommange[size_tableauDeCommange]=value;
        size_tableauDeCommange++;

    }
}

void Directive::updateModuleValue(void)
{
    string flag,data;
    flag.clear();
    data.clear();
    flag.append(1,7);
    if(m_CtrlBridge->send(m_capteurUltrasonic[0],flag,data))
        m_valueCapteurUltrasonic = data[0];


    flag.clear();
    data.clear();
    flag.append(1,7);
    if(m_CtrlBridge->send(m_capteurIR[0],flag,data)) {
        if(data.size() == 2) {
            m_valueCapteurIR = data[0];
            m_valueCapteurIR = (m_valueCapteurIR<<8) + data[1];
        } else
            m_valueCapteurIR = data[0];
    }

    flag.clear();
    data.clear();
    flag.append(1,7);
    if(m_CtrlBridge->send(m_capteurProximiter[0],flag,data))
        m_valueCapteurProximiter = data[0];
}

void Directive::analiseMaze(void)
{
    char areaLatt =0;
    char areaVert =0;
    string mymap = myMaze->showMap();
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r  Labyrinthe map: X:%02x Y:%02x \n\r",myMaze->getX(),myMaze->getY());
    for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%02X] ",mymap[i]);
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
    for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%02X] ",mymap[i+3]);
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
    for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%02X] ",mymap[i+6]);
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");



    if((ultrasonicToInch(m_valueCapteurUltrasonic)< 1) && (IRToCm(ADCTomv(m_valueCapteurIR)) <= 80)) { //capteur ultrasson embrouiller/imprecis
        debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Capteur Ultrasson brouiller");
        //addTableauDeCommande(6);
    } else if(ultrasonicToInch(m_valueCapteurUltrasonic) >=24) { //plus proche que 10pouce
        debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche 2pi");
        areaLatt =2;
        areaVert =2;
    } else if(ultrasonicToInch(m_valueCapteurUltrasonic) >=12) { //plus proche que 10pouce
        debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche 2pi");
        areaLatt =1;
        areaVert =1;
    }
    if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 60) {
        debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
        areaVert =2;
    } else if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 30) {
        debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
        areaVert =1;
    }


    switch(myMaze->getDirection()) {
        case UP:
            switch(areaVert) {
                case 0:
                    myMaze->setC_Up(MUR);
                    break;

                case 1:
                    if(areaLatt == 0) {
                        myMaze->setC_Up(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+1);

                        myMaze->setC(MUR,myMaze->getX(),myMaze->getY()+2);
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+1);

                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+2);
                        myMaze->setC(MUR,myMaze->getX(),myMaze->getY()+2);
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+2);
                    }
                    break;

                case 2:
                    if(areaLatt == 0) {
                        myMaze->setC_Up(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+1);//mur?
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()+1);
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+1);//mur?

                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+1);//mur?
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()+2);
                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+1);//mur?
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+1);

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+2);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()+2);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+2);
                    }
                    break;
            }

            break;

        case DOWN:
            switch(areaVert) {
                case 0:
                    myMaze->setC_Down(MUR);
                    break;

                case 1:
                    if(areaLatt == 0) {
                        myMaze->setC_Down(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-1);

                        myMaze->setC(MUR,myMaze->getX(),myMaze->getY()-2);
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-1);

                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()-2);
                        myMaze->setC(MUR,myMaze->getX(),myMaze->getY()-2);
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()-2);
                    }
                    break;

                case 2:
                    if(areaLatt == 0) {
                        myMaze->setC_Down(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()-1);//mur?
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()-1);
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()-1);//mur?

                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+1);//mur?
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()-2);
                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+1);//mur?
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-1);

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-2);
                        myMaze->setC(VIDE,myMaze->getX(),myMaze->getY()-2);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-2);
                    }
                    break;
            }
            break;

        case LEFT:
            switch(areaVert) {
                case 0:
                    myMaze->setC_Left(MUR);
                    break;

                case 1:
                    if(areaLatt == 0) {
                        myMaze->setC_Left(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+1);

                        myMaze->setC(MUR,myMaze->getX()-2,myMaze->getY());
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+1);

                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-2,myMaze->getY()-1);
                        myMaze->setC(MUR,myMaze->getX()-2,myMaze->getY());
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-2,myMaze->getY()+1);
                    }
                    break;

                case 2:
                    if(areaLatt == 0) {
                        myMaze->setC_Left(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()-1);//mur?
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY());
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+1);//mur?

                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+1);//mur?
                        myMaze->setC(VIDE,myMaze->getX()-2,myMaze->getY());
                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+1);//mur?
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()-1,myMaze->getY()+1);

                        myMaze->setC(VIDE,myMaze->getX()-2,myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX()-2,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()-2,myMaze->getY()+1);
                    }
                    break;
            }
            break;

        case RIGHT:
            switch(areaVert) {
                case 0:
                    myMaze->setC_Right(MUR);
                    break;

                case 1:
                    if(areaLatt == 0) {
                        myMaze->setC_Right(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+1);

                        myMaze->setC(MUR,myMaze->getX()+2,myMaze->getY());
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+1);

                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+2,myMaze->getY()-1);
                        myMaze->setC(MUR,myMaze->getX()+2,myMaze->getY());
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+2,myMaze->getY()+1);
                    }
                    break;

                case 2:
                    if(areaLatt == 0) {
                        myMaze->setC_Right(MUR);
                    } else if(areaLatt == 1) {
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()-1);//mur?
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY());
                        myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+1);//mur?

                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()-1,myMaze->getY()+1);//mur?
                        myMaze->setC(VIDE,myMaze->getX()+2,myMaze->getY());
                        //myMaze->setC(PAS_EXPLORER,myMaze->getX()+1,myMaze->getY()+1);//mur?
                    } else if(areaLatt == 2) {

                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()-1);
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()+1,myMaze->getY()+1);

                        myMaze->setC(VIDE,myMaze->getX()+2,myMaze->getY()+1);
                        myMaze->setC(VIDE,myMaze->getX()+2,myMaze->getY());
                        myMaze->setC(VIDE,myMaze->getX()+2,myMaze->getY()+1);
                    }
                    break;
            }
            break;
    }
}