
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
    ssc32 = new Serial(PB_6, PB_7);
    ctrDesPattes = new Faculter_motrice(ssc32/*pc*/);
    m_valueCapteurUltrasonic = 0;
    m_valueCapteurIR = 0;
    m_valueCapteurProximiter = 0;
    for(int i =0; i<10; i++)tableauDeCommange[i]= 0;
    size_tableauDeCommange=0;
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r set explorer \n\r");
    myMaze->setMyPos(Labyrinthe::explorer);
    //myMaze->setC(EXPLORER,C5);
    //m_CtrlBridge = m_CtrlBridge->getInstance();
    //a enlever de commentaire//m_ListDesModules = m_CtrlBridge->findModule(0,1,0,0);
    
    //Serial pc(USBTX, USBRX);
    
    //ssc32->set_flow_control(0);
    
    
    //debug("\n\r directive Init");
    m_ListDesModules = m_CtrlBridge->findModule(0,CAPTEUR,DISTANCE,0);
    m_ListDesModules.append(m_CtrlBridge->findModule(0,CAPTEUR,PROXIMITEE,0));
    for(int i=0; i < m_ListDesModules.size(); i++) debug(DEBUG_DIRECTIVE_TEST,"\n\r  m_ListDesModules[%i]:%i",i,m_ListDesModules[i]);
    
    m_capteurUltrasonic= m_CtrlBridge->findModule(0,CAPTEUR,ULTRASONIQUE,0x27/*0b100111*/);
    if(!(m_capteurUltrasonic.empty())) 
    {
        debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurUltrasonic found");
        for(int i=0; i < m_capteurUltrasonic.size(); i++) debug(DEBUG_DIRECTIVE_TEST,"\n\r  m_capteurUltrasonic[%i]:%i",i,m_capteurUltrasonic[i]);
    }
    else                               debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurUltrasonic not found");
    
    
    m_capteurIR= m_CtrlBridge->findModule(0,CAPTEUR,DISTANCE,0x27/*0b100111*/);
    if(!(m_capteurIR.empty()))
    {
        debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurIR found");
        for(int i=0; i < m_capteurIR.size(); i++) debug(DEBUG_DIRECTIVE_TEST,"\n\r  m_capteurIR[%i]:%i",i,m_capteurIR[i]);
    }
    else debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurIR not found");
    
    m_capteurProximiter= m_CtrlBridge->findModule(0,CAPTEUR,PROXIMITEE,0x0E/*0b001110*/);
    if(!(m_capteurProximiter.empty()))
    {
        debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurProximiter found");
        for(int i=0; i < m_capteurProximiter.size(); i++) debug(DEBUG_DIRECTIVE_TEST,"\n\r  m_capteurProximiter[%i]:%i",i,m_capteurProximiter[i]);
    }
    else debug(DEBUG_DIRECTIVE_TEST,"\n\r m_capteurProximiter not found");
    
    ctrDesPattes->moveUp();
    
    bool getUp=true;
    while((getUp)&& (! ctrDesPattes->isSeqComplet())) 
    {
        ctrDesPattes->exec();
        
        if(ctrDesPattes->get_idFrame() >= 5)
        getUp = false;
        
    }
    
    followThePath = false;
    ctrDesPattes->calibre();
    
    
    #ifdef DEBUG_DIRECTIVE_GRAPHICAL_INTERFACE
        //analiseMaze();
        ///wait(2);
        //debug("\x1B[2J"); //clear screen
        /*debug("\x1B[25l");//hide cursor
        debug("\x1B[;H");*/ //cursor default position
        
        //createSLbox(0,0,5,15,"Mode");
        /*createDLbox(0,0,10,20,"Menu");//(1,12,10,20,"test2");
            setText(1,3,"1) BrainControle");
        setText(1,4,"2) Show Maze");*/
        //createDLbox(16,0,5,15,"Stage");
        
        myMaze->setC(Labyrinthe::mur,0,0,Labyrinthe::C1);
        myMaze->setC(Labyrinthe::vide,0,0,Labyrinthe::C2);
        myMaze->setC(Labyrinthe::mur,0,0,Labyrinthe::C3);
        myMaze->setC(Labyrinthe::mur,0,0,Labyrinthe::C4);
        myMaze->setC(Labyrinthe::vide,0,0,Labyrinthe::C5);
        myMaze->setC(Labyrinthe::vide,0,0,Labyrinthe::C6);
        myMaze->setC(Labyrinthe::mur,0,0,Labyrinthe::C7);
        myMaze->setC(Labyrinthe::mur,0,0,Labyrinthe::C8);
        myMaze->setC(Labyrinthe::mur,0,0,Labyrinthe::C9);
        
        myMaze->setC(Labyrinthe::vide,3,0,Labyrinthe::C1);
        myMaze->setC(Labyrinthe::vide,3,0,Labyrinthe::C2);
        myMaze->setC(Labyrinthe::mur ,3,0,Labyrinthe::C3);
        myMaze->setC(Labyrinthe::vide,3,0,Labyrinthe::C4);
        myMaze->setC(Labyrinthe::vide,3,0,Labyrinthe::C5);
        myMaze->setC(Labyrinthe::vide,3,0,Labyrinthe::C6);
        myMaze->setC(Labyrinthe::mur ,3,0,Labyrinthe::C7);
        myMaze->setC(Labyrinthe::mur ,3,0,Labyrinthe::C8);
        myMaze->setC(Labyrinthe::mur ,3,0,Labyrinthe::C9);
        
        myMaze->setC(Labyrinthe::vide,6,0,Labyrinthe::C1);
        myMaze->setC(Labyrinthe::mur ,6,0,Labyrinthe::C2);
        myMaze->setC(Labyrinthe::mur ,6,0,Labyrinthe::C3);
        myMaze->setC(Labyrinthe::vide,6,0,Labyrinthe::C4);
        myMaze->setC(Labyrinthe::vide,6,0,Labyrinthe::C5);
        myMaze->setC(Labyrinthe::mur ,6,0,Labyrinthe::C6);
        myMaze->setC(Labyrinthe::mur ,6,0,Labyrinthe::C7);
        myMaze->setC(Labyrinthe::mur ,6,0,Labyrinthe::C8);
        myMaze->setC(Labyrinthe::mur ,6,0,Labyrinthe::C9);
        
        myMaze->setC(Labyrinthe::mur ,0,-3,Labyrinthe::C1);
        myMaze->setC(Labyrinthe::mur ,0,-3,Labyrinthe::C2);
        myMaze->setC(Labyrinthe::mur ,0,-3,Labyrinthe::C3);
        myMaze->setC(Labyrinthe::mur ,0,-3,Labyrinthe::C4);
        myMaze->setC(Labyrinthe::vide,0,-3,Labyrinthe::C5);
        myMaze->setC(Labyrinthe::mur ,0,-3,Labyrinthe::C6);
        myMaze->setC(Labyrinthe::mur ,0,-3,Labyrinthe::C7);
        myMaze->setC(Labyrinthe::vide,0,-3,Labyrinthe::C8);
        myMaze->setC(Labyrinthe::vide,0,-3,Labyrinthe::C9);
        
        myMaze->setC(Labyrinthe::mur ,3,-3,Labyrinthe::C1);
        myMaze->setC(Labyrinthe::mur ,3,-3,Labyrinthe::C2);
        myMaze->setC(Labyrinthe::mur ,3,-3,Labyrinthe::C3);
        myMaze->setC(Labyrinthe::vide,3,-3,Labyrinthe::C4);
        myMaze->setC(Labyrinthe::vide,3,-3,Labyrinthe::C5);
        myMaze->setC(Labyrinthe::vide,3,-3,Labyrinthe::C6);
        myMaze->setC(Labyrinthe::vide,3,-3,Labyrinthe::C7);
        myMaze->setC(Labyrinthe::mur ,3,-3,Labyrinthe::C8);
        myMaze->setC(Labyrinthe::vide,3,-3,Labyrinthe::C9);
        
        myMaze->setC(Labyrinthe::mur ,6,-3,Labyrinthe::C1);
        myMaze->setC(Labyrinthe::mur ,6,-3,Labyrinthe::C2);
        myMaze->setC(Labyrinthe::mur ,6,-3,Labyrinthe::C3);
        myMaze->setC(Labyrinthe::vide,6,-3,Labyrinthe::C4);
        myMaze->setC(Labyrinthe::mur ,6,-3,Labyrinthe::C5);
        myMaze->setC(Labyrinthe::mur ,6,-3,Labyrinthe::C6);
        myMaze->setC(Labyrinthe::vide,6,-3,Labyrinthe::C7);
        myMaze->setC(Labyrinthe::vide,6,-3,Labyrinthe::C8);
        myMaze->setC(Labyrinthe::mur ,6,-3,Labyrinthe::C9);
    #endif
    myMaze->setMyPos(Labyrinthe::explorer);
    
    #ifdef DEBUG_DIRECTIVE_TEST_CAPTEUR
    debug("\x1B[2J"); //clear screen
    char areaLatt =0;
    char areaVert =0;
    int idCommand = 0;
    while(idCommand != 9)
    {
        
         debug("\x1B[;H"); //cursor default position
             debug("\n\r press any key");
            idCommand = fgetc(pc) - '0';
        debug("\x1B[2J"); //clear screen
        
        updateModuleValue();
                
        //////////////////////////////
        // Traitement du Labyrinthe //
        //////////////////////////////
        debug("\n\r        -invert ultrasonicToCm: %02f         ",inchToCm(ultrasonicToInch(m_valueCapteurIR)));
        debug("\n\r        -invert IRToCm(%02f): %02f         ",ADCTomv(m_valueCapteurUltrasonic),IRToCm(ADCTomv(m_valueCapteurUltrasonic)));
        //debug("\n\r        -IR(value):%i         ",m_valueCapteurIR);
        debug("\n\r        -IRToCm(%02f): %02f         ",ADCTomv(m_valueCapteurIR),IRToCm(ADCTomv(m_valueCapteurIR)));
        
        debug("\n\r        -ultrasonic(value):%f         ",m_valueCapteurUltrasonic);
        debug("\n\r        -ultrasonicToInch: %02f         ",ultrasonicToInch(m_valueCapteurUltrasonic));
        debug("\n\r        -ultrasonicToCm: %02f         ",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)));
        
        debug("\n\r        -m_valueCapteurProximiter: %02d         ",m_valueCapteurProximiter);
        //wait(.5);
                
                
        if((inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic))<= 1) /*&& (IRToCm(ADCTomv(m_valueCapteurIR)) <= 80)*/)//enlever parce que il est lock avec des limites 
        { //capteur ultrasson embrouiller/imprecis
            debug("\n\r        -Capteur Ultrasson brouiller");
            //addTableauDeCommande(6);
        } 
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) <= DIRECTIVE_ULTRASONIC_LIMIT_SHORT)
        { //plus proche que 1 case
            debug("\n\r        -Objet proche %g <= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_SHORT);
            
            areaLatt =0;
            
            if(IRToCm(ADCTomv(m_valueCapteurIR)) <= DIRECTIVE_IR_LIMIT_SHORT)
            {
                /*
                    /---\
                    |?M?| //vert 0
                    |.X.| //latt 0
                    |...|
                    \---/
                */
                areaVert = 0;
            }
            else
            {
                /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
                areaVert = 1;
            }
            
            
        }
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) <= DIRECTIVE_ULTRASONIC_LIMIT_MIDDLE)
        { //plus proche que 2 case
             debug("\n\r        -Objet proche %g <= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_MIDDLE);
            //modifier vue que il ne detecte pas asser loin
                    /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
            areaLatt =0;
            areaVert =1;
        } 
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) <= DIRECTIVE_ULTRASONIC_LIMIT_LONG)
        { //plus proche que 2 case
            debug("\n\r        -Objet proche %g <= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_LONG);
            //modifier vue que il ne detecte pas asser loin
            /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
            areaLatt =0;
            areaVert =1;
        } 
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) > DIRECTIVE_ULTRASONIC_LIMIT_LONG)
        { //plus proche que 2 case
        debug("\n\r        -Objet proche %g >= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_LONG);
        //modifier vue que il ne detecte pas asser loin
        /*
                            /?V?\
                            |?V?| //vert 2
                            |.X.| //latt 0
                            |...| // objet possiblement a proximiter
                            \---/
                        */
            
            areaLatt =0;
            areaVert =2;
        }
        
        
        
        /*if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 60) 
        {
            debug("\n\r          -Confirmation IR");
            areaVert =2;
        } 
        else if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 30) 
        {
            debug("\n\r          -Confirmation IR");
            areaVert =1;
        }*/
        
        
        if(areaVert >= areaLatt) 
        {
            switch(areaVert) 
            {
                case 0:
                    /*
                        /---\
                        |?M?| //vert 0
                        |.X.| //latt 0
                        |...|
                        \---/
                    */
                    
                    debug("\n\r +---+ ");
                    debug("\n\r |?M?| //vert 0 ");
                    debug("\n\r |.X.| //latt 0 ");
                    debug("\n\r |...| ");
                    debug("\n\r +---+ ");
                    break;
                case 1://impossible pour le moment IR trop instable//
                    
                 
                    
                    if(areaLatt == 1) 
                    {
                        /*
                            /?M?\
                            |VVV| //vert 1
                            |.X.| //latt 1
                            |...| // objet possiblement a proximiter
                            \---/
                        */
                        debug("\n\r +-M-+ ");
                        debug("\n\r |VVV| //vert 1 ");
                        debug("\n\r |.X.| //latt 1 ");
                        debug("\n\r |...| // objet possiblement a proximiter ");
                        debug("\n\r +---+ ");
                    }
                    else
                    {
                        /*
                        /-M-\
                        |?V?| //vert 1
                        |.X.| //latt 0
                        |...|
                        \---/
                         */
                    
                        debug("\n\r +-M-+ ");
                        debug("\n\r |?V?| //vert 1 ");
                        debug("\n\r |.X.| //latt 0 ");
                        debug("\n\r |...| ");
                        debug("\n\r +---+ ");
                    }
                    break;
                case 2:
                   
                    switch(areaLatt) 
                    {
                        case 0://impossible pour le moment IR trop instable//
                            /*
                                /?V?\
                                |?V?| //vert 2
                                |.X.| //latt 0
                                |...| // objet possiblement a proximiter
                                \---/
                            */
                            debug("\n\r +?V?+ ");
                            debug("\n\r |?V?| //vert 2 ");
                            debug("\n\r |.X.| //latt 0 ");
                            debug("\n\r |...| // objet possiblement a proximiter ");
                            debug("\n\r +---+ ");
                            break;
                        case 1://impossible pour le moment IR trop instable//
                            /*
                                /?V?\
                                |VVV| //vert 2
                                |.X.| //latt 1
                                |...| // objet possiblement a proximiter
                                \---/
                            */
                            debug("\n\r +-M-+ ");
                            debug("\n\r |VVV| //vert 2 ");
                            debug("\n\r |.X.| //latt 1 ");
                            debug("\n\r |...| // objet possiblement a proximiter ");
                            debug("\n\r +---+ ");
                            break;
                        case 2:
                            /*
                                /VVV\
                                |VVV| //vert 2
                                |.X.| //latt 2
                                |...|
                                \---/
                            */
                            debug("\n\r +VVV+ ");
                            debug("\n\r |VVV| //vert 2 ");
                            debug("\n\r |.X.| //latt 2 ");
                            debug("\n\r |...| ");
                            debug("\n\r +---+ ");
                            break;
                    }
                    break;
            }
        }
        /*if((ultrasonicToInch(m_valueCapteurUltrasonic)< 1) && (IRToCm(ADCTomv(m_valueCapteurIR)) <= 80)) 
        { //capteur ultrasson embrouiller/imprecis
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Capteur Ultrasson brouiller");
            //addTableauDeCommande(6);
        } 
        else if(ultrasonicToInch(m_valueCapteurUltrasonic) >=24) 
        { //plus proche que 10pouce
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche 2pi");
            areaLatt =2;
            areaVert =2;
        } 
        else if(ultrasonicToInch(m_valueCapteurUltrasonic) >=12) 
        { //plus proche que 10pouce
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche 2pi");
            areaLatt =1;
            areaVert =1;
        }
        debug(DEBUG_DIRECTIVE_TEST,": %i",ultrasonicToInch(m_valueCapteurUltrasonic));
        
        if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 60) 
        {
            debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
            areaVert =2;
        } 
        else if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 30) 
        {
            debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
            areaVert =1;
        }
        debug(DEBUG_DIRECTIVE_TEST,": %i",IRToCm(ADCTomv(m_valueCapteurIR)));*/
    }
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
        debug("\x1B[2J"); //clear screen
        debug("\x1B[25l");//hide cursor
        debug("\x1B[;H"); //cursor default position
        debug("\n\r--------In task directive--------");
        
        /*
            createDLbox(0,0,10,25,"BrainControle");
            setText(1,3,"1) Move Up");
            setText(1,4,"2) Move Down");
            setText(1,5,"3) Move Left");
            setText(1,6,"4) Move Right");
            
            int idCommand;
            do{
            if(pc.readable()){
            idCommand = fgetc(pc) - '0';
            switch(idCommand)
            {
            case 1:
            myMaze->goUp();
            break;
            case 2:
            myMaze->goDown();
            break;
            case 3:
            myMaze->goLeft();
            break;
            case 4:
            myMaze->goRight();
            break;
            }
            myMaze->setMyPos(Labyrinthe::explorer);
            
            string mymap = myMaze->showMap();
            debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r  Labyrinthe map: X:%02x Y:%02x \n\r",myMaze->getX(),myMaze->getY());
            for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%02X] ",mymap[i+6]);
            debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
            for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%02X] ",mymap[i+3]);
            debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
            for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%02X] ",mymap[i]);
            debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
            
            #ifdef DBG_MAIN_DELAY_SEC
            debug("\n\r\n wait \n\r\n");
            wait(DBG_MAIN_DELAY_SEC);
            #endif
            
            debug("\x1B[2J"); //clear screen
            debug("\x1B[;H"); //cursor default position
            createDLbox(0,0,10,25,"BrainControle");
            setText(1,3,"1) Move Up");
            setText(1,4,"2) Move Down");
            setText(1,5,"3) Move Left");
            setText(1,6,"4) Move Right");
            }
        }while(1);   */
    #endif
    
    //debug(DEBUG_DIRECTIVE_TEST,"\n\rIn task directive");
    #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
        if(ctrDesPattes->isSeqComplet()) 
        {
            ////////////////
            // Inspection //
            ////////////////
            updateModuleValue();
            
            if((tableauDeCommange[0] == TBL_CMD_MARCHE) && (size_tableauDeCommange == 1)) 
            {
                //addTableauDeCommande(0x81);
                //addTableauDeCommande(0x82);
                //mabey//addTableauDeCommande(0x83);
                addTableauDeCommande(0x84);
                
                //addTableauDeCommande(0x85);
                //mabey//addTableauDeCommande(0x86);
                addTableauDeCommande(0x87);
                addTableauDeCommande(0x88);
            }
            
            
            if(tableauDeCommange[0] == 0) 
            {
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
                
                updateModuleValue();
                
                //////////////////////////////
                // Traitement du Labyrinthe //
                //////////////////////////////
                debug(DEBUG_DIRECTIVE_TRAITEMENT,"\n\r        -IRToCm(%02f): %02f",ADCTomv(m_valueCapteurIR),IRToCm(ADCTomv(m_valueCapteurIR)));
                debug(DEBUG_DIRECTIVE_TRAITEMENT,"\n\r        -ultrasonicToInch: %02f",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)));
                debug(DEBUG_DIRECTIVE_TRAITEMENT,"\n\r        -m_valueCapteurProximiter: %02d",m_valueCapteurProximiter);
    #endif //DEBUG_DIRECTIVE_LEG_DISABLE
                if(followThePath == true)
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r EN MODE FOLLOW THE PATH");
                else
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r HORS MODE FOLLOW THE PATH");
                
                analiseMaze();
                char nextCase=0;
                /*switch(myMaze->getDirection()) {
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
                }*/
                if( myMaze->getC_Foward() == Labyrinthe::vide )
                    followThePath = false;
                
                
            
                if(followThePath == false) 
                {
                    nextCase = myMaze->getC_Foward();
                    
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r nextCase: [%02x]",nextCase);
                    switch(nextCase ) 
                    {
                        case Labyrinthe::vide :
                            #ifdef DEBUG_DIRECTIVE_LEG_DISABLE
                                debug("nextCase Vide\n\r");
                            #endif
                            debug(DEBUG_DIRECTIVE_TEST," Javance");
                            #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
                                addTableauDeCommande(TBL_CMD_MARCHE);
                            #endif
                            //if(followThePath == true)
                            //followThePath = false;
                            myMaze->moveFoward();
                            myMaze->setMyPos(Labyrinthe::explorer);
                            break;
                        
                        case Labyrinthe::explorer :// ici pt amiliorer
                            debug(DEBUG_DIRECTIVE_TEST," \n\rnext case deja explorer");
                            if(rand()%2) 
                            {
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r jeverifie si alternative");
                                
                                #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
                                addTableauDeCommande(TBL_CMD_MARCHE);
                                #endif
                                nextCase = checkOtherWay(myMaze->getDirection(),1);
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rnextcase: %i",nextCase);
                                switch(nextCase) 
                                { // on verifie si on a une direction possible
                                    case UP:
                                        debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne UP");
                                        turnRightDirection(myMaze->getDirection(),UP);
                                        myMaze->setDirection(UP);
                                        
                                        
                                        break;
                                    case DOWN:
                                        debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne DOWN");
                                        turnRightDirection(myMaze->getDirection(),DOWN);
                                        myMaze->setDirection(DOWN);
                                        
                                        break;
                                    case LEFT:
                                        debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne LEFT");
                                        turnRightDirection(myMaze->getDirection(),LEFT);
                                        myMaze->setDirection(LEFT);
                                        
                                        break;
                                    case RIGHT:
                                        debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne RIGHT");
                                        turnRightDirection(myMaze->getDirection(),RIGHT);
                                        myMaze->setDirection(RIGHT);
                                        
                                        break;
                                    default: //aucun autre chemin
                                        debug(DEBUG_DIRECTIVE_TEST,"\n\r aucune autre place alors J'avance");
                                        myMaze->moveFoward();
                                        myMaze->setMyPos(Labyrinthe::explorer);
                                        #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
                                        addTableauDeCommande(TBL_CMD_MARCHE);
                                        #endif
                                        break;
                                }
                            } 
                            else 
                            {
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r jeverifie pas si alternative");
                                myMaze->moveFoward();
                                #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
                                addTableauDeCommande(TBL_CMD_MARCHE);
                                #endif
                            }
                            //myMaze->moveFoward();
                            //myMaze->setMyPos(Labyrinthe::explorer);
                            break;
                        
                        case Labyrinthe::mur:
                            debug(DEBUG_DIRECTIVE_TEST,"\n\r UN MURRRRRRRR\n\r");
                            if(searchNewWay()) 
                            {
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r New Path found ");
                                followThePath = true;
                            } 
                            else 
                            {
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r New Path not found ");
                            }
                            /* switch(checkOtherWay(myMaze->getDirection()))// on verifie si on a une direction possible
                                {
                                case UP:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne UP ");
                                myMaze->setDirection(UP);
                                //myMaze->moveFoward();
                                break;
                                case DOWN:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne DOWN ");
                                myMaze->setDirection(DOWN);
                                //myMaze->moveFoward();
                                break;
                                case LEFT:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne LEFT");
                                myMaze->setDirection(LEFT);
                                //myMaze->moveFoward();
                                break;
                                case RIGHT:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne RIGHT");
                                myMaze->setDirection(RIGHT);
                                //myMaze->moveFoward();
                                break;
                                default://aucun autre chemin
                                /debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne completement ");
                                if(myMaze->getDirection() %2)
                                myMaze->setDirection(myMaze->getDirection()+1);
                                else
                                myMaze->setDirection(myMaze->getDirection()-1);
                                
                                //myMaze->moveFoward();
                                
                                break;
                                }
                            myMaze->setMyPos(Labyrinthe::explorer);*/
                            break;
                        
                        case Labyrinthe::pasExplorer ://pas sur
                            debug(DEBUG_DIRECTIVE_TEST," pasExplorer");
                            #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
                                addTableauDeCommande(TBL_CMD_MARCHE);
                            #endif
                            break;
                    }
                } 
                else 
                { // on suis un chemin
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rmode follow the path\n\n\r");
                    positionXY tempPosition;
                    //std::list<positionXY>::iterator it=bufferNewWay.begin();
                    for (std::list<positionXY>::iterator it=bufferNewWay.begin(); it != bufferNewWay.end(); ++it) 
                    {
                        //tempPosition = *(it);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posX: %i",(*it).posX);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posY: %i",(*it).posY);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.direction: %i",(*it).direction);
                    } //std::cout << ' ' << *it;
                    
                    if((bufferNewWay.front()).direction != myMaze->getDirection()) //turn time
                    {
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     le chemin a pas la meme direction");
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     current dir : %i",myMaze->getDirection());
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     next dir : %i",(bufferNewWay.front()).direction);
                        
                        turnRightDirection(myMaze->getDirection(),(bufferNewWay.front()).direction);
                        switch((bufferNewWay.front()).direction) 
                        {
                            case UP:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne UP");
                                myMaze->setDirection(UP);
                                
                                /*if(((bufferNewWay.front()).direction + myMaze->getDirection()) == (UP + DOWN))
                                {
                                    if(rand()%2)
                                    {
                                    addTableauDeCommande(TBL_CMD_TURN_LEFT);
                                    addTableauDeCommande(TBL_CMD_TURN_LEFT);
                                    }
                                    else
                                    {
                                    addTableauDeCommande(TBL_CMD_TURN_RIGHT);
                                    addTableauDeCommande(TBL_CMD_TURN_RIGHT);
                                    }
                                }*/
                                break;
                            case DOWN:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne DOWN");
                                myMaze->setDirection(DOWN);
                                
                                break;
                            case LEFT:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne LEFT");
                                myMaze->setDirection(LEFT);
                                
                                break;
                            case RIGHT:
                                debug(DEBUG_DIRECTIVE_TEST,"\n\r Je tourne RIGHT");
                                myMaze->setDirection(RIGHT);
                                break;
                        }
                        //bufferNewWay.pop_front();
                    } 
                    else 
                    {
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     le chemin a la meme direction");
                        //myMaze->getXY_Foward(tempPosition.posX,tempPosition.posY);
                        tempPosition.posX = myMaze->getX();
                        tempPosition.posY = myMaze->getY();
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     current X: %i",tempPosition.posX);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     current Y: %i",tempPosition.posY);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     buffer X: %i",(bufferNewWay.front()).posX);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     buffer Y: %i",(bufferNewWay.front()).posY);
                        if((tempPosition.posX == (bufferNewWay.front()).posX) && (tempPosition.posY == (bufferNewWay.front()).posY)) 
                        {
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     aucun problem");
                            #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
                                addTableauDeCommande(TBL_CMD_MARCHE);
                            #endif
                            myMaze->moveFoward();
                            myMaze->setMyPos(Labyrinthe::explorer);
                            bufferNewWay.pop_front();
                            
                        } 
                        else
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     problem");
                        
                    }
                    
                    
                    
                    if(bufferNewWay.empty())
                        followThePath = false;
                    /*do{
                        //tempPosition.posX = (bufferNewWay.front()).posX;
                        //tempPosition.posY = (bufferNewWay.front()).posY;
                        
                        tempPosition = bufferNewWay.front();
                        bufferNewWay.pop_front();
                        debug("\n\r bufferNewWay: %i",bufferNewWay.size());
                        debug("\n\rtempPosition.posX: %i",tempPosition.posX);
                        debug("\n\rtempPosition.posY: %i",tempPosition.posY);
                    }while(bufferNewWay.size() != 0);*/
                }
                #ifdef DEBUG_DIRECTIVE_SHOW_MAP_LABYRINTH
                    string mymap = myMaze->showMap();
                    debug("\n\r  Labyrinthe map: X:%02i Y:%02i \n\r",(signed char)(myMaze->getX()),(signed char)(myMaze->getY()));
                    //char caseCaract = 0;
                    debug("\n\r");
                    for(int i=0; i<3; i++) debug(" [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+6]));
                    debug("\n\r");
                    for(int i=0; i<3; i++) debug(" [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+3]));
                    debug("\n\r");
                    for(int i=0; i<3; i++) debug(" [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i]));
                    debug("\n\r");
                #endif
    #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
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
                    
                    ///////////////
                    // Mouvement //
                    ///////////////
            } 
            else 
            {
                
                switch(tableauDeCommange[0]) 
                {
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
            
        } 
        else
        {
            ctrDesPattes->exec();
        }
    #endif //DEBUG_DIRECTIVE_LEG_DISABLE
    ////////////////////
    // Update memoire //
    ////////////////////
    
    ////////////
    // Autre? //
    ////////////
    
    
    //debug(DEBUG_DIRECTIVE_TEST,"\n\rOut task directive");
    #ifdef DEBUG_BOOT_GRAPHICAL_INTERFACE
        #ifdef DBG_MAIN_DELAY_SEC
            debug("\n\r\n wait \n\r\n");
            wait(DBG_MAIN_DELAY_SEC);
        #endif
        debug("\n\r---------------------");
    #endif
}
double Directive::IRToCm (double miliVolt)
{
    double result=0;
    //debug("\n\r double value: %02f",miliVolt);
    if(miliVolt < tabIR[0][1])result = tabIR[0][0];
    else if(miliVolt > tabIR[11][1])result = tabIR[11][0];
    
    for(int i =1; (result==0)&&(i<12); i++) 
    {
        if((tabIR[i-1][1]<=miliVolt) && (tabIR[i][1]>miliVolt)) 
        {
            result=tabIR[i-1][0]+((tabIR[i][0]-tabIR[i-1][0])*((tabIR[i-1][1]-miliVolt)/(tabIR[i-1][1]-tabIR[i][1])));
        }
    }
    return result;
}
void Directive::addTableauDeCommande(unsigned char value)
{
    if(size_tableauDeCommange!=10) 
    {
        tableauDeCommange[size_tableauDeCommange]=value;
        size_tableauDeCommange++;
        
    }
}

void Directive::updateModuleValue(void)
{
    string flag,data;
    double tempValue=0;
    flag.clear();
    data.clear();
    flag.append(1,7);
    //debug("\n\n\r  flag size:%i \n\r",flag.size());
    if(m_CtrlBridge->send(m_capteurUltrasonic[0],flag,data))
    {
        /*if(data[0] != 1)//patch?
            tempValue = data[0];*/
        
        if(data.size() == 2) 
        {
            tempValue = data[0];
            //tempValue = (tempValue<<8) + data[1];
            tempValue = (data[0]<<8) + data[1];
        } 
        else
        tempValue = data[0];
        
        m_valueCapteurUltrasonic = m_valueCapteurUltrasonic+((tempValue -m_valueCapteurUltrasonic)/DIRECTIVE_ULTRASONIC_BUFFER_LENGHT);
    }
    #ifdef DEBUG_DIRECTIVE_UPDATE_MODULE
    debug("\n\n\r  data size:%i \n\r",data.size());
    debug("\n\r        -data(value):%i         ",data[0]);
    debug("\n\r        -tempValue(value):%02f         ",tempValue);
    #endif
    tempValue=0;
    flag.clear();
    data.clear();
    flag.append(1,7);
   
    //debug("\n\n\r  flag size:%i \n\r",flag.size());
    if(m_CtrlBridge->send(m_capteurIR[0],flag,data)) 
    {
        
        if(data.size() == 2) 
        {
            //tempValue = data[0]<<8;
            //debug("\n\n\r monI: %02f",tempValue);
            //debug("\n\n\r mondata: %i",data[0]<<8);
            //tempValue = (tempValue<<8) + data[1];
            tempValue = (data[0]<<8) + data[1];
        } 
        else
        tempValue = data[0];
        
        m_valueCapteurIR=m_valueCapteurIR+((tempValue-m_valueCapteurIR)/DIRECTIVE_IR_BUFFER_LENGHT);
    }
    #ifdef DEBUG_DIRECTIVE_UPDATE_MODULE
    debug("\n\n\r  data size:%i \n\r",data.size());
    debug("\n\r        -data(value):%i         ",data[0]);
    debug("\n\r        -tempValue(value):%02f         ",tempValue);
    #endif
    //debug("\n\n\r  data size:%i \n\r",data.size());
   // debug("\n\r        -IR(value):%f         ",m_valueCapteurIR);
    //for(int i=0; i<data.size();i++)debug("\n\r        -data[%i]:%i",i,data[i]);
    
    flag.clear();
    data.clear();
    flag.append(1,7);
    //debug("\n\n\r  flag size:%i \n\r",flag.size());
    if(m_CtrlBridge->send(m_capteurProximiter[0],flag,data))
        m_valueCapteurProximiter = data[0];
        
       // debug("\n\n\r  data size:%i \n\r",data.size());
       // debug("\n\r        -m_valueCapteurProximiter(value):%i         ",m_valueCapteurProximiter);
}

void Directive::analiseMaze(void)
{
    char areaLatt =0;
    char areaVert =0;
    string mymap = myMaze->showMap();
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r  Labyrinthe map: X:%02i Y:%02i \n\r",(signed char)(myMaze->getX()),(signed char)(myMaze->getY()));
    
    debug(DEBUG_DIRECTIVE_LABYRINTH,"Direction: ");
    switch(myMaze->getDirection()) 
    {
        case UP:
            debug(DEBUG_DIRECTIVE_LABYRINTH,"Up \n\r");
            break;
        case DOWN:
            debug(DEBUG_DIRECTIVE_LABYRINTH,"Down \n\r");
            break;
        case LEFT:
            debug(DEBUG_DIRECTIVE_LABYRINTH,"Left \n\r");
            break;
        case RIGHT:
            debug(DEBUG_DIRECTIVE_LABYRINTH,"Right \n\r");
            break;
    }
    
    for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+6]));
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
    for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+3]));
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
    for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i]));
    debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
    
    
    #ifndef DEBUG_DIRECTIVE_LABYRINTH_USER_CTRL
        /*if((ultrasonicToInch(m_valueCapteurUltrasonic)< 1) && (IRToCm(ADCTomv(m_valueCapteurIR)) <= 80)) 
        { //capteur ultrasson embrouiller/imprecis
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Capteur Ultrasson brouiller");
            //addTableauDeCommande(6);
        } 
        else if(ultrasonicToInch(m_valueCapteurUltrasonic) >=24) 
        { //plus proche que 10pouce
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche 2pi");
            areaLatt =2;
            areaVert =2;
        } 
        else if(ultrasonicToInch(m_valueCapteurUltrasonic) >=12) 
        { //plus proche que 10pouce
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Objet proche 2pi");
            areaLatt =1;
            areaVert =1;
        }
        debug(DEBUG_DIRECTIVE_TEST,": %i",ultrasonicToInch(m_valueCapteurUltrasonic));
        
        if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 60) 
        {
            debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
            areaVert =2;
        } 
        else if(IRToCm(ADCTomv(m_valueCapteurIR)) <= 30) 
        {
            debug(DEBUG_DIRECTIVE_TEST,"\n\r          -Confirmation IR");
            areaVert =1;
        }
        debug(DEBUG_DIRECTIVE_TEST,": %i",IRToCm(ADCTomv(m_valueCapteurIR)));*///old one
        if((inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic))<= 1) /*&& (IRToCm(ADCTomv(m_valueCapteurIR)) <= 80)*/)//enlever parce que il est lock avec des limites 
        { //capteur ultrasson embrouiller/imprecis
        
            debug(DEBUG_DIRECTIVE_TEST,"\n\r        -Capteur Ultrasson brouiller");
            //addTableauDeCommande(6);
        } 
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) <= DIRECTIVE_ULTRASONIC_LIMIT_SHORT)
        { //plus proche que 1 case
        #ifdef DEBUG_DIRECTIVE_UPDATE_MODULE
            debug("\n\r        -Objet proche %g <= %i cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_SHORT);
            #endif
            areaLatt =0;
            
            if(IRToCm(ADCTomv(m_valueCapteurIR)) <= DIRECTIVE_IR_LIMIT_SHORT)
            {
                /*
                    /---\
                    |?M?| //vert 0
                    |.X.| //latt 0
                    |...|
                    \---/
                */
                areaVert = 0;
            }
            else
            {
                /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
                areaVert = 1;
            }            
        }
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) <= DIRECTIVE_ULTRASONIC_LIMIT_MIDDLE)
        { //plus proche que 2 case
        #ifdef DEBUG_DIRECTIVE_UPDATE_MODULE
             debug("\n\r        -Objet proche %g <= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_MIDDLE);
             #endif
            //modifier vue que il ne detecte pas asser loin
                    /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
            areaLatt =0;
            areaVert =1;
        } 
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) <= DIRECTIVE_ULTRASONIC_LIMIT_LONG)
        { //plus proche que 2 case
        #ifdef DEBUG_DIRECTIVE_UPDATE_MODULE
            debug("\n\r        -Objet proche %g <= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_LONG);
            #endif
            //modifier vue que il ne detecte pas asser loin
            /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
            areaLatt =0;
            areaVert =1;
        } 
        else if(inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)) > DIRECTIVE_ULTRASONIC_LIMIT_LONG)
        { //plus proche que 2 case
        #ifdef DEBUG_DIRECTIVE_UPDATE_MODULE
            debug("\n\r        -Objet proche %g >= %g cm",inchToCm(ultrasonicToInch(m_valueCapteurUltrasonic)),DIRECTIVE_ULTRASONIC_LIMIT_LONG);
            #endif
            //modifier vue que il ne detecte pas asser loin
            /*
                /?V?\
                |?V?| //vert 2
                |.X.| //latt 0
                |...| // objet possiblement a proximiter
                \---/
            */
            
            areaLatt =0;
            areaVert =2;
        }
        
        //debug("\n\r    areaLatt: %i,    areaVert: %i",areaLatt,areaVert);
    #endif
    
    #ifdef DEBUG_DIRECTIVE_LABYRINTH_USER_CTRL
        debug("\n\r---analise maze(manualy CTRL)---\n\r");
        int idCommand = -1;
        areaVert = 9;
        areaLatt = 9;
        /*do {
            debug("\n\r Enter areaVert [0,1,2]: ");
            idCommand = fgetc(pc) - '0';
            debug(" %i",idCommand);
        } while((idCommand < 0) && (idCommand > 2));
        areaVert = idCommand;
        
        do {
            debug("\n\r Enter areaLatt [0,1,2]: ");
            idCommand = fgetc(pc) - '0';
            debug(" %i",idCommand);
        } while((idCommand < 0) && (idCommand > 2));
        areaLatt = idCommand;*/
        
        debug("\n\r");
    #endif
    //changer lalgoritme ici
    
    /*
        /---\
        |?M?| //vert 0
        |.X.| //latt 0
        |...|
        \---/
        
        /-M-\
        |?V?| //vert 1
        |.X.| //latt 0
        |...|
        \---/
        
        /?M?\
        |VVV| //vert 1
        |.X.| //latt 1
        |...| // objet possiblement a proximiter
        \---/
        
        /?M?\
        |VVV| //vert 1
        |.X.| //latt 2
        |...| // cas impossible
        \---/
        
        /?V?\
        |?V?| //vert 2
        |.X.| //latt 0
        |...| // objet possiblement a proximiter
        \---/
        
        /?V?\
        |VVV| //vert 2
        |.X.| //latt 1
        |...| // objet possiblement a proximiter
        \---/
        
        /VVV\
        |VVV| //vert 2
        |.X.| //latt 2
        |...|
        \---/
    */
    //vertical==0 latt==0 //mur devant
    //vertical==1 latt==1
    ////////////////////////////////////
    //345  
    //012  | numerotation des case
    ///////////////////////////////////
    signed char fieldX[6]= {0,0,0,0,0,0};
    signed char fieldY[6]= {0,0,0,0,0,0};
    bool fieldSet = false;
    
    switch(myMaze->getDirection()) 
    {
        case UP:
            fieldX[0] = myMaze->getX()-1;
            fieldY[0] = myMaze->getY()+1;
            fieldX[1] = myMaze->getX();
            fieldY[1] = myMaze->getY()+1;
            fieldX[2] = myMaze->getX()+1;
            fieldY[2] = myMaze->getY()+1;
            fieldX[3] = myMaze->getX()-1;
            fieldY[3] = myMaze->getY()+2;
            fieldX[4] = myMaze->getX();
            fieldY[4] = myMaze->getY()+2;
            fieldX[5] = myMaze->getX()+1;
            fieldY[5] = myMaze->getY()+2;
            break;
        
        case DOWN:
            fieldX[0] = myMaze->getX()-1;
            fieldY[0] = myMaze->getY()-1;
            fieldX[1] = myMaze->getX();
            fieldY[1] = myMaze->getY()-1;
            fieldX[2] = myMaze->getX()+1;
            fieldY[2] = myMaze->getY()-1;
            fieldX[3] = myMaze->getX()-1;
            fieldY[3] = myMaze->getY()-2;
            fieldX[4] = myMaze->getX();
            fieldY[4] = myMaze->getY()-2;
            fieldX[5] = myMaze->getX()+1;
            fieldY[5] = myMaze->getY()-2;
            break;
        
        case LEFT:
            fieldX[0] = myMaze->getX()-1;
            fieldY[0] = myMaze->getY()-1;
            fieldX[1] = myMaze->getX()-1;
            fieldY[1] = myMaze->getY();
            fieldX[2] = myMaze->getX()-1;
            fieldY[2] = myMaze->getY()+1;
            fieldX[3] = myMaze->getX()-2;
            fieldY[3] = myMaze->getY()-1;
            fieldX[4] = myMaze->getX()-2;
            fieldY[4] = myMaze->getY();
            fieldX[5] = myMaze->getX()-2;
            fieldY[5] = myMaze->getY()+1;
            break;
        
        case RIGHT:
            fieldX[0] = myMaze->getX()+1;
            fieldY[0] = myMaze->getY()-1;
            fieldX[1] = myMaze->getX()+1;
            fieldY[1] = myMaze->getY();
            fieldX[2] = myMaze->getX()+1;
            fieldY[2] = myMaze->getY()+1;
            fieldX[3] = myMaze->getX()+2;
            fieldY[3] = myMaze->getY()-1;
            fieldX[4] = myMaze->getX()+2;
            fieldY[4] = myMaze->getY();
            fieldX[5] = myMaze->getX()+2;
            fieldY[5] = myMaze->getY()+1;
            break;
    }
    if(areaVert >= areaLatt) 
    {
        switch(areaVert) 
        {
            case 0:
                /*
                    /---\
                    |?M?| //vert 0
                    |.X.| //latt 0
                    |...|
                    \---/
                */
                myMaze->setC(Labyrinthe::mur,fieldX[1],fieldY[1]);
                fieldSet = true;
                break;
            case 1:
                /*
                    /-M-\
                    |?V?| //vert 1
                    |.X.| //latt 0
                    |...|
                    \---/
                */
                myMaze->setC(Labyrinthe::vide,fieldX[1],fieldY[1]);
                myMaze->setC(Labyrinthe::mur,fieldX[4],fieldY[4]);
                fieldSet = true;
                
                if(areaLatt == 1) 
                {
                    /*
                        /?M?\
                        |VVV| //vert 1
                        |.X.| //latt 1
                        |...| // objet possiblement a proximiter
                        \---/
                    */
                    myMaze->setC(Labyrinthe::vide,fieldX[0],fieldY[0]);
                    myMaze->setC(Labyrinthe::vide,fieldX[2],fieldY[2]);
                }
                break;
            case 2:
                fieldSet = true;
                switch(areaLatt) 
                {
                    case 0:
                        /*
                            /?V?\
                            |?V?| //vert 2
                            |.X.| //latt 0
                            |...| // objet possiblement a proximiter
                            \---/
                        */
                        myMaze->setC(Labyrinthe::vide,fieldX[1],fieldY[1]);
                        myMaze->setC(Labyrinthe::vide,fieldX[4],fieldY[4]);
                        break;
                    case 1:
                        /*
                            /?V?\
                            |VVV| //vert 2
                            |.X.| //latt 1
                            |...| // objet possiblement a proximiter
                            \---/
                        */
                        for(int i = 0; i<3; i++)myMaze->setC(Labyrinthe::vide,fieldX[i],fieldY[i]);
                        myMaze->setC(Labyrinthe::vide,fieldX[4],fieldY[4]);
                        break;
                    case 2:
                        /*
                            /VVV\
                            |VVV| //vert 2
                            |.X.| //latt 2
                            |...|
                            \---/
                        */
                        for(int i = 0; i<6; i++)myMaze->setC( Labyrinthe::vide,fieldX[i],fieldY[i]);
                        break;
                }
                break;
        }
    }
    
    if(fieldSet == false) 
    { // on a un cas impossible
        //myMaze->setC(Labyrinthe::error,fieldX[1],fieldY[1]);
    }
    
    ////////////////////////////////////
    
    
    #ifdef DEBUG_DIRECTIVE_LABYRINTH_USER_CTRL
        mymap = myMaze->showMap();
        //char caseCaract = 0;
        for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+6]));
        debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
        for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+3]));
        debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
        for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i]));
        debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
        
        debug("\n\r-------------------\n\r");
    #endif
}

char Directive::checkOtherWay(char dir, bool checkExplorer)
{
    char result = 0;
    char order[3];
    
    
    
    bool fini = false;
    
    switch(rand() % 6) 
    {
        case 0://[0],[1],[2]
            order[0] = 0;
            order[1] = 1;
            order[2] = 2;
            break;
        case 1://[0],[2],[1]
            order[0] = 0;
            order[1] = 2;
            order[2] = 1;
            break;
        case 2://[1],[0],[2]
            order[0] = 1;
            order[1] = 0;
            order[2] = 2;
            break;
        case 3://[2],[0],[1]
            order[0] = 2;
            order[1] = 0;
            order[2] = 1;
            break;
        case 4://[1],[2],[0]
            order[0] = 1;
            order[1] = 2;
            order[2] = 0;
            break;
        case 5://[2],[1],[0]
            order[0] = 2;
            order[1] = 1;
            order[2] = 0;
            break;
    }
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rresult: ");
    for(int i=0; (i<3)&&(!fini); i++) 
    {
        switch(order[i]) 
        { // inclure un état memoir affin que si il a le choix entre une case vide et une explorer il priorise la vide// pt faire de meme avec pas explorer
            case 0:
                result = myMaze->getC_ToLeft();
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r getC_ToLeft: %i %i ****",result,myMaze->getC_ToLeft());
                //if(((Labyrinthe::case_t)result != Labyrinthe::error)&&((Labyrinthe::case_t)result != Labyrinthe::mur) &&((checkExplorer)?((Labyrinthe::case_t)result != Labyrinthe::explorer):1) )
                if(((Labyrinthe::case_t)result == Labyrinthe::vide)&&((Labyrinthe::case_t)result != Labyrinthe::mur) &&((checkExplorer)?((Labyrinthe::case_t)result != Labyrinthe::explorer):1) ) 
                {
                    fini = true;
                    result = LEFT;
                }
                break;
            case 1:
                result = myMaze->getC_Backward();
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r getC_Backward: %i %i ****",result,myMaze->getC_Backward());
                if(/*((Labyrinthe::case_t)result != Labyrinthe::error)&&*/((Labyrinthe::case_t)result != Labyrinthe::mur)&&((checkExplorer)?((Labyrinthe::case_t)result != Labyrinthe::explorer):1)) 
                {
                    fini = true;
                    result = DOWN;
                }
                break;
            case 2:
                result = myMaze->getC_ToRight();
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r getC_ToRight: %i %i ****",result,myMaze->getC_ToRight());
                if(/*((Labyrinthe::case_t)result != Labyrinthe::error)&&*/((Labyrinthe::case_t)result != Labyrinthe::mur)&&((checkExplorer)?((Labyrinthe::case_t)result != Labyrinthe::explorer):1)) 
                {
                    fini = true;
                    result = RIGHT;
                }
                break;
        }
    }
    
    if(fini) 
    {
        switch(dir) 
        {
            /*case UP:
            break;*/
            case DOWN:
                switch(result) 
                {
                    case LEFT:
                        result = RIGHT;
                        break;
                    case DOWN:
                        result = UP;
                        break;
                    case RIGHT:
                        result = LEFT;
                        break;
                }
                break;
            case LEFT:
                switch(result) 
                {
                    case LEFT:
                        result = DOWN;
                        break;
                    case DOWN:
                        result = RIGHT;
                        break;
                    case RIGHT:
                        result = UP;
                        break;
                }
                break;
            case RIGHT:
                switch(result) 
                {
                    case LEFT:
                        result = UP;
                        break;
                    case DOWN:
                        result = LEFT;
                        break;
                    case RIGHT:
                        result = DOWN;
                        break;
                }
                break;
        }
    } 
    else
        result =0;
    return result;
}
void Directive::checkOtherWay(char &caseFront, char &caseBack, char &caseLeft, char &caseRight)
{
    caseFront = myMaze->getC_Foward();
    caseBack  = myMaze->getC_Backward();
    caseRight = myMaze->getC_ToRight();
    caseLeft = myMaze->getC_ToLeft();
}
bool Directive::searchNewWay(void)
{
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r ---- Search new way ----\n\r");
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r  Labyrinthe map: X:%02i Y:%02i \n\r",(signed char)(myMaze->getX()),(signed char)(myMaze->getY()));
    bool result=false;
    string backupMap = myMaze->getAllMap();
    signed char backupPosX = myMaze->getX();
    signed char backupPosY = myMaze->getY();
    string searchMap = backupMap;
    char tempdir,nextCase=0;
    positionXY tempPosition;
    char backupDir = myMaze->getDirection();
    
    
    bool noOtherWay = false;//si apres un moment tu est entourer de mur
    bool wrongWay = false; //si jamais vien un moment que tu est pris /doit rebrousser chemin
    //bool checkAutour = false;
    
    bufferNewWay.clear();
    tempPosition.posX = myMaze->getX();
    tempPosition.posY = myMaze->getY();
    //bufferNewWay.push_back(tempPosition); // pas sur de lutiliter
    
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Debut Boucle");
    //asdfasda// Ici voire pour pt amiliorer et cheker a gauche et a droite au cas ou tu verai une case vide parce que la tu cours direct dans un mur avant de tourner.
    while((!result)&&(!noOtherWay)) 
    {
        // nextCase = 0;
        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Cycle Boucle\n\r");
        nextCase = myMaze->getC_Foward();
        
        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r nextCase: [%02x]",nextCase);
        switch(nextCase ) 
        {
            
            case Labyrinthe::pasExplorer :
            case Labyrinthe::vide :
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r vide ou pas explorer: ");
                myMaze->moveFoward();
                result = true;
                break;
            
            case Labyrinthe::explorer :// ici pt amiliorer
                //add position a la liste
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Explorer");
                myMaze->moveFoward();
                //myMaze->setMyPos(Labyrinthe::error);
                break;
            
            case Labyrinthe::mur:
                tempdir = rand() % 2;
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Mur: %i",tempdir);
                if(tempdir == 1) 
                {
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r left right");
                    tempdir = myMaze->getC_ToLeft();
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r nextCase: [%02x]",tempdir);
                    if((Labyrinthe::case_t)tempdir != Labyrinthe::mur) 
                    {
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Left");
                        myMaze->turnLeft();
                        
                        //backupDir = myMaze->getDirection();
                    } 
                    else 
                    {
                        tempdir = myMaze->getC_ToRight();
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r nextCase: [%02x]",tempdir);
                        if((Labyrinthe::case_t)tempdir != Labyrinthe::mur) 
                        {
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Right");
                            myMaze->turnRight();
                            
                            //backupDir = myMaze->getDirection();
                        } 
                        else 
                        {
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r aucun coter");
                            wrongWay = true; // verifie dans la liste
                        }
                    }
                    
                } 
                else 
                {
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r right left");
                    tempdir = myMaze->getC_ToRight();
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r nextCase: [%02x]",tempdir);
                    if((Labyrinthe::case_t)tempdir != Labyrinthe::mur) 
                    {
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Right");
                        myMaze->turnRight();
                        
                        //backupDir = myMaze->getDirection();
                    } 
                    else 
                    {
                        tempdir = myMaze->getC_ToLeft();
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r nextCase: [%02x]",tempdir);
                        if((Labyrinthe::case_t)tempdir != Labyrinthe::mur) 
                        {
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Left");
                            myMaze->turnLeft();
                            
                            //backupDir = myMaze->getDirection();
                        } 
                        else 
                        {
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r aucun coter");
                            wrongWay = true; // verifie dans la liste
                        }
                    }
                    /* if(wrongWay == false)
                    myMaze->moveFoward();*/
                }
                
                //myMaze->setMyPos(Labyrinthe::error);
                break;
        }
        
        tempPosition.posX = myMaze->getX();
        tempPosition.posY = myMaze->getY();
        tempPosition.direction = myMaze->getDirection();
        
        /*debug("\n\rtempPosition.posX: %i",tempPosition.posX);
            debug("\n\rtempPosition.posY: %i",tempPosition.posY);
            debug("\n\rbufferNewWay.posX: %i",(bufferNewWay.back().posX));
        debug("\n\rbufferNewWay.posY: %i",(bufferNewWay.back().posY));*/
        
        if((bufferNewWay.empty())||(((bufferNewWay.back().posX) != tempPosition.posX) || ((bufferNewWay.back().posY) != tempPosition.posY))) 
        {
            bufferNewWay.push_back(tempPosition);
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r bufferNewWay: %i",bufferNewWay.size());
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posX: %i",tempPosition.posX);
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posY: %i",tempPosition.posY);
        } 
        else if((bufferNewWay.empty())&& ((backupPosX != myMaze->getX()) || (backupPosY != myMaze->getY())) ) 
        {
            bufferNewWay.push_back(tempPosition);
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r bufferNewWay: %i",bufferNewWay.size());
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posX: %i",tempPosition.posX);
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posY: %i",tempPosition.posY);
        } 
        else if(((bufferNewWay.back()).posX == tempPosition.posX) && ((bufferNewWay.back()).posY == tempPosition.posY) && ((bufferNewWay.back()).direction != tempPosition.direction))//ra fait un tours
        {
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r pop back a cause dun tournie");
            bufferNewWay.pop_back();
            bufferNewWay.push_back(tempPosition);
        }
        
        else
        {
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r buffer non adder");
            
        }
        
        
        if(wrongWay) 
        {
            char caseFront,caseBack,caseLeft,caseRight;
            char wallCount;
            char directive;
            bool haveValuesChange = false;
            bool caseVideTrouver = false;
            bool caseExplorerTrouver = false;
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\n\r wrong way patching");
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r bufferNewWay size: %i",bufferNewWay.size());
            std::list<positionXY>::iterator it;
            do 
            {
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r --wrong way boucle");
                
                //bufferNewWay.pop_back();
                if(!bufferNewWay.empty()) 
                {
                    directive = 0;//defenir fait rien
                    it=bufferNewWay.end();
                    haveValuesChange = false;
                    caseVideTrouver = false;
                    caseExplorerTrouver = false;
                    tempPosition.posX = (bufferNewWay.back()).posX;
                    tempPosition.posY = bufferNewWay.back().posY;
                    
                    
                    myMaze->setX(bufferNewWay.back().posX);
                    myMaze->setY(bufferNewWay.back().posY);
                    wallCount = 0;
                    checkOtherWay(caseFront,caseBack,caseLeft,caseRight);
                    
                    if((Labyrinthe::case_t)caseFront == Labyrinthe::mur)wallCount++;
                    if((Labyrinthe::case_t)caseBack  == Labyrinthe::mur)wallCount++;
                    if((Labyrinthe::case_t)caseLeft  == Labyrinthe::mur)wallCount++;
                    if((Labyrinthe::case_t)caseRight == Labyrinthe::mur)wallCount++;
                    
                    if(wallCount == 3)
                    {
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r PATH trouver ");
                        myMaze->setC(Labyrinthe::mur,tempPosition.posX,tempPosition.posY);
                    }
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r checkOtherWay front: %i, back: %i, LEFT: %i, RIGHT: %i",caseFront,caseBack,caseLeft,caseRight);
                    //tempPosition.posX = (bufferNewWay.back()).posX;
                    //tempPosition.posY = bufferNewWay.back().posY;
                    /*if(((Labyrinthe::case_t)caseFront == Labyrinthe::vide) || ((Labyrinthe::case_t)caseBack == Labyrinthe::vide) || ((Labyrinthe::case_t)caseLeft == Labyrinthe::vide) || ((Labyrinthe::case_t)caseRight == Labyrinthe::vide))
                    {
                        debug("\n\r Path vide trouver!!!");
                        caseVideTrouver = true;
                        wrongWay = false;
                    }*/
                    
                    //else
                    //{
                        it--;
                        if(/*((Labyrinthe::case_t)caseFront != Labyrinthe::error) &&*/ ((Labyrinthe::case_t)caseFront != Labyrinthe::mur)) 
                        { // une anciene case est potentiele,emt bonne
                            myMaze->getXY_Foward(tempPosition.posX,tempPosition.posY);
                            
                            if((Labyrinthe::case_t)caseFront == Labyrinthe::vide)
                            {
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Path vide trouver!!!");
                                caseVideTrouver = true;
                                haveValuesChange = true;
                                directive = 1;
                                wrongWay = false;
                                //debug("\n\r moveFoward");
                            }
                            if((!caseVideTrouver) && (!caseExplorerTrouver))
                            {
                                caseExplorerTrouver = true;
                            /*if(((*it).posX != tempPosition.posX) && ((*it).posY != tempPosition.posY)) {
                                wrongWay = false;
                                myMaze->moveFoward();//setDirection(UP);
                                debug("\n\r moveFoward");
                                debug("\n\r chemin trouver");
                                haveValuesChange = true;
                            } else if(bufferNewWay.size() == 1) {*/
                              //  debug("\n\r Last thing in buffer");
                                //myMaze->moveFoward();//setDirection(UP);
                                directive = 1;// move foward
                                haveValuesChange = true;
                               // debug("\n\r moveFoward");
                            }
                        }
                        
                        if(/*((Labyrinthe::case_t)caseBack != Labyrinthe::error) &&*/ ((Labyrinthe::case_t)caseBack != Labyrinthe::mur)) 
                        { // une anciene case est potentiele,emt bonne
                            myMaze->getXY_Backward(tempPosition.posX,tempPosition.posY);
                            
                            if((Labyrinthe::case_t)caseBack == Labyrinthe::vide)
                            {
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Path vide trouver!!!");
                                caseVideTrouver = true;
                                haveValuesChange = true;
                                directive = 2;
                                wrongWay = false;
                                //debug("\n\r moveFoward");
                            }
                            if((!caseVideTrouver) && (!caseExplorerTrouver))
                            {
                                caseExplorerTrouver = true;
                            /*if(((*it).posX != tempPosition.posX) && ((*it).posY != tempPosition.posY)) {
                                wrongWay = false;
                                myMaze->turnBack();//setDirection(DOWN);
                                debug("\n\r turn Back");
                                debug("\n\r chemin trouver");
                                haveValuesChange = true;
                            } else if(bufferNewWay.size() == 1) {*/
                                //debug("\n\r Last thing in buffer");
                                //myMaze->turnBack();//setDirection(DOWN);
                                directive = 2;
                                //debug("\n\r turn Back");
                                haveValuesChange = true;
                            }
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r direction: %i",myMaze->getDirection());
                        }
                        
                        if(/*((Labyrinthe::case_t)caseLeft != Labyrinthe::error) &&*/ ((Labyrinthe::case_t)caseLeft != Labyrinthe::mur)) 
                        { // une anciene case est potentiele,emt bonne
                            myMaze->getXY_Left(tempPosition.posX,tempPosition.posY);
                            
                            if((Labyrinthe::case_t)caseLeft == Labyrinthe::vide)
                            {
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Path vide trouver!!!");
                                caseVideTrouver = true;
                                haveValuesChange = true;
                                directive = 3;
                                wrongWay = false;
                                //debug("\n\r moveFoward");
                            }
                            if((!!caseVideTrouver) && (!caseExplorerTrouver))
                            {
                                caseExplorerTrouver = true;
                            /*if(((*it).posX != tempPosition.posX) && ((*it).posY != tempPosition.posY)) {
                                wrongWay = false;
                                myMaze->turnLeft();//setDirection(LEFT);
                                debug("\n\r turn Left");
                                debug("\n\r chemin trouver");
                                haveValuesChange = true;
                            } else if(bufferNewWay.size() == 1) {*/
                                //debug("\n\r Last thing in buffer");
                                //myMaze->turnLeft();//setDirection(LEFT);
                                directive = 3;
                                //debug("\n\r turn Left");
                                haveValuesChange = true;
                            }
                        }
                        
                        if(/*((Labyrinthe::case_t)caseRight != Labyrinthe::error) &&*/ ((Labyrinthe::case_t)caseRight != Labyrinthe::mur)) 
                        { // une anciene case est potentiele,emt bonne
                            myMaze->getXY_Right(tempPosition.posX,tempPosition.posY);
                            
                            if((Labyrinthe::case_t)caseRight == Labyrinthe::vide)
                            {
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Path vide trouver!!!");
                                caseVideTrouver = true;
                                haveValuesChange = true;
                                directive = 4;
                                wrongWay = false;
                                //debug("\n\r moveFoward");
                            }
                            if((!caseVideTrouver)&& (!caseExplorerTrouver))
                            {
                                caseExplorerTrouver = true;
                            /*if(((bufferNewWay.back()).posX != tempPosition.posX) && ((bufferNewWay.back()).posY != tempPosition.posY)) {
                                wrongWay = false;
                                myMaze->turnRight();//setDirection(RIGHT);
                                debug("\n\r turn Right");
                                debug("\n\r chemin trouver");
                                haveValuesChange = true;
                            } else if(bufferNewWay.size() == 1) {*/
                                //debug("\n\r Last thing in buffer");
                                //myMaze->turnRight();//setDirection(RIGHT);
                                directive = 4;
                               // debug("\n\r turn Right");
                                haveValuesChange = true;
                            }
                        }
                        
                    //} 
                    
                    
                }   
                else
                    noOtherWay = true;
                
                
                if(haveValuesChange)
                {
                    switch(directive)
                    {
                        case 0:
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r doNothing");
                            break;
                        case 1:
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r moveFoward");
                            myMaze->moveFoward();
                            break;
                        case 2:
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Back");
                            myMaze->turnBack();
                            break;
                        case 3:
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Left");
                            myMaze->turnLeft();
                            break;
                        case 4:
                            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r turn Right");
                            myMaze->turnRight();
                            break;
                    }
                    tempPosition.posX = myMaze->getX();
                    tempPosition.posY = myMaze->getY();
                    tempPosition.direction = myMaze->getDirection();
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r bufferNewWay: %i",bufferNewWay.size());
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posX: %i",tempPosition.posX);
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posY: %i",tempPosition.posY);
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.direction: %i",tempPosition.direction);
                    for (std::list<positionXY>::iterator it=bufferNewWay.begin(),itEnd;( it != bufferNewWay.end()) && (!bufferNewWay.empty()); ++it) 
                    {
                        //tempPosition = *(it);
                        itEnd = bufferNewWay.end();
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Bouble de meme position");
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posX: %i",(*it).posX);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posY: %i",(*it).posY);
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.direction: %i",(*it).direction);
                        if(((*it).posX == tempPosition.posX) && ((*it).posY == tempPosition.posY) && ((*it).direction == tempPosition.direction))
                        {
                            while(((*it).posX != (*itEnd).posX) &&
                                  ((*it).posY != (*itEnd).posY) &&
                                  ((*it).direction != (*itEnd).direction) && (!bufferNewWay.empty()))
                            {
                                itEnd = bufferNewWay.end();
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r pop back et enmurer");
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     tempPosition.posX: %i",(bufferNewWay.back()).posX);
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     tempPosition.posY: %i",(bufferNewWay.back()).posY);
                                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r     tempPosition.direction: %i",(bufferNewWay.back()).direction);
                                myMaze->setC(Labyrinthe::mur,(bufferNewWay.back()).posX,(bufferNewWay.back()).posY);
                                bufferNewWay.pop_back();
                            }
                            //it--;
                            noOtherWay = true;//placer ici pour patcher vue que je suis taner
                            //checkAutour = true;
                        }
                    }
                    if(((bufferNewWay.back()).posX == tempPosition.posX) && ((bufferNewWay.back()).posY == tempPosition.posY) && ((bufferNewWay.back()).direction != tempPosition.direction))//ra fait un tours
                    {
                        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r pop back a cause dun tournie");
                        bufferNewWay.pop_back();
                    }
                    bufferNewWay.push_back(tempPosition);
                    //bufferNewWay.pop_back();//on enleve pour pouvoir lire le dernier
                }
                else
                {
                    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r pop back");
                    bufferNewWay.pop_back();//on enleve pour pouvoir lire le dernier
                }
                string mymap = myMaze->showMap();
                debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r  Labyrinthe map: X:%02i Y:%02i \n\r",(signed char)(myMaze->getX()),(signed char)(myMaze->getY()));
                //char caseCaract = 0;
                debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r direction: %i",myMaze->getDirection());
                debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
                for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+6]));
                debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
                for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i+3]));
                debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r");
                for(int i=0; i<3; i++) debug(DEBUG_DIRECTIVE_LABYRINTH," [%c] ",myMaze->caseToChar((Labyrinthe::case_t)mymap[i]));
                debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r press any key...\n\r");
                
                fgetc(pc);
                
                
            } while((wrongWay) && (!noOtherWay));
            debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r Fin Boucle");
        }
        debug(DEBUG_DIRECTIVE_LABYRINTH,"\n\r press any key...\n\r"); fgetc(pc);
    }
    
    myMaze->setX(backupPosX);
    myMaze->setY(backupPosY);
    myMaze->setAllMap(backupMap);
    myMaze->setDirection(backupDir);
    if(noOtherWay)
    {
        result = false;
        myMaze->setAllMap("");
        myMaze->setX(0);
        myMaze->setY(0);
        myMaze->setDirection(backupDir);
    }
    
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\n\r dans le buffer");
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r bufferNewWay: %i",bufferNewWay.size());
    for (std::list<positionXY>::iterator it=bufferNewWay.begin(); it != bufferNewWay.end(); ++it) {
        //tempPosition = *(it);
        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posX: %i",(*it).posX);
        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.posY: %i",(*it).posY);
        debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\rtempPosition.direction: %i",(*it).direction);
    }
    debug(DEBUG_DIRECTIVE_MAZE_GRAPHICAL_INTERFACE_ENABLE,"\n\r ----------------");
    return result;
}

bool Directive::isAnotherWay(void)
{
    bool result=false;
    
    return result;
}
void Directive::turnRightDirection(char currentDir, char nextDir)
{
                                
                            
    #ifndef DEBUG_DIRECTIVE_LEG_DISABLE
    if(((nextDir + currentDir) == (UP + DOWN)) ||
        ((nextDir + currentDir) == (LEFT + RIGHT)))
    {
        if(rand()%2)
        {
            addTableauDeCommande(TBL_CMD_TURN_LEFT);
            addTableauDeCommande(TBL_CMD_TURN_LEFT);
        }
        else
        {
            addTableauDeCommande(TBL_CMD_TURN_RIGHT);
            addTableauDeCommande(TBL_CMD_TURN_RIGHT);
        }
    }
    else
    {
     switch(currentDir)
     {
        case UP:
            if(nextDir == LEFT) 
            {
                addTableauDeCommande(TBL_CMD_TURN_LEFT);
            }
            else if(nextDir == RIGHT)
            {
                addTableauDeCommande(TBL_CMD_TURN_RIGHT);
            }
            break;
        case DOWN:
            if(nextDir == LEFT) 
            {
                addTableauDeCommande(TBL_CMD_TURN_RIGHT);
            }
            else if(nextDir == LEFT)
            {
                addTableauDeCommande(TBL_CMD_TURN_LEFT);
            }
            break;
        case LEFT:
            if(nextDir == UP)   
            {
                addTableauDeCommande(TBL_CMD_TURN_RIGHT);
            }
            else if(nextDir == DOWN)
            {
                addTableauDeCommande(TBL_CMD_TURN_LEFT);
            }
            break;
        case RIGHT:
             if(nextDir == UP)  
            {
                addTableauDeCommande(TBL_CMD_TURN_LEFT);
            }
            else if(nextDir == DOWN)
            {
                addTableauDeCommande(TBL_CMD_TURN_RIGHT);
            }
            break;
     }
    }
    #endif
}