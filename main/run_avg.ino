// class for running average container
class run_avg {
  
  public: 
    // constructor 
    run_avg() {
      for (int i=0; i<10; i++) {
          rec_ten[i] = 0; 
      }
      curr_avg = 0; 
      index = 0; 
    }; 
    
    // update average from new data 
    void update_avg(int next) {
      rec_ten[index] = next; 
      int t = 0; 
      for (int i=0; i<10; i++) t += rec_ten[i]; 
      curr_avg = t; 
      if (index == 9) index = 0; 
      else index++; 
    }
    

  private: 
    int rec_ten[10]; 
    int curr_avg; 
    int index; 
};
