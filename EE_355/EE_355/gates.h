#ifndef GATE_H
#define GATE_H

#include <vector>
#include <string>
#include "net.h"

using namespace std;

/* forward declaration */
class Net;

/**
 * Enumeration to indicate gate type
 *  AND=0, OR=1, etc.
 */
enum {AND, OR, NAND, NOR, XOR, NOT};

/**
 * This class models a Gate object
 */
class Gate {
 public:
  /**
   * Constructor
   *
   * @param[in] n Name of the gate
   */
  Gate(string n); 

  /**
   * Constructor
   *
   * @param[in] n Name of the gate
   * @param[in] d Delay of this gate instance
   */
  Gate(string n, int d);

  /**
   * Destructor
   */
  virtual ~Gate();

  /**
   * Returns the name of this Gate
   *
   * @return String representing the name of the gate
   */
  string name() const;

  /**
   * Returns the delay of this gate
   *
   * @return Delay of this gate
   */
  int getDelay() const;

  /**
   * Pure virtual function that should be 
   * overridden for specific gate types
   *
   * Evaluates the value the gate will attempt
   *  to prdoduce based on the input net values
   *
   * @return Value the gate attempts to produce:
   *         '0','1','X'
   */
  virtual char eval() = 0;

  /**
   * Pure virtual function that should be 
   * overridden for specific gate types
   *
   * Evaluates the value the gate will attempt
   *  to prdoduce based on the input net values
   *
   * @param[in] os ostream to dump the Verilog 
   *                description of this gate
   */  
  virtual void dump(ostream &os) = 0;

  /**
   * Adds an input net to this gate
   *
   * @param[in] n Pointer to the input Net
   */
  void addInput(Net *n);

  /**
   * Returns the inputs of this gate
   *
   * @return Returns a new dynamically allocated
   *          list of the input nets
   */
  vector<Net *> *getInputs();

  /**
   * Sets the output net of this gate
   *
   * @param[in] n Pointer to the output Net
   */
  void addOutput(Net *n);

  /**
   * Returns the output Net of this gate
   *
   * @return Pointer to the output net of this Gate
   */
  Net* getOutput() const;

  /**
   * Returns the number of inputs
   *
   * @return Number of inputs for this gate
   */
  int getNumInputs() const;

 protected:
  vector<Net *> *inputs;
  Net *output;
  string inst_name;
  int delay;
};

class And : public Gate {
 public:
  And(string n, int d);
  ~And();
  char eval();
  void dump(ostream &os);
};

class Or : public Gate {
 public:
  Or(string n, int d);
  ~Or();
  char eval();
  void dump(ostream &os);
};

class Nor : public Gate {
 public:
  Nor(string n, int d);
  ~Nor();
  char eval();
  void dump(ostream &os);
};

class Nand : public Gate {
 public:
  Nand(string n, int d);
  ~Nand();
  char eval();
  void dump(ostream &os);
};

class Xor : public Gate {
 public:
  Xor(string n, int d);
  ~Xor();
  char eval();
  void dump(ostream &os);
};

class Not : public Gate {
 public:
  Not(string n, int d);
  ~Not();
  char eval();
  void dump(ostream &os);
};

#endif
