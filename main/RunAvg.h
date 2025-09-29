// class for running average container

#ifndef RUNAVG_H
#define RUNAVG_H

class RunAvg {
  
  public: 
    // constructor 
    RunAvg(); 
    
    // get/set
    int get_avg();
    // update average from new data 
    void update_avg(int next); 

  private: 
    int rec_ten[10]; 
    int curr_avg; 
    int index; 
};

#endif
