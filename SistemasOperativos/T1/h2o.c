#include <nSystem.h>
#include "h2o.h"
#include "fifoqueues.h"

typedef struct{
  nCondition w;
  Hydrogen h;
  H2O h2o;
} ReqH;

typedef struct{
  nCondition w;
  Oxygen o;
  H2O h2o;
} ReqO;

FifoQueue hydrogenos;
FifoQueue oxigenos;
nMonitor m;

void initH2O(void) {
  hydrogenos = MakeFifoQueue();
  oxigenos = MakeFifoQueue();
  m = nMakeMonitor();
  return;
}

H2O combineOxy(Oxygen o) {
  
  nEnter(m);
  if(LengthFifoQueue(hydrogenos)>=2){
    
    ReqH *r1 = (ReqH *)GetObj(hydrogenos);
    ReqH *r2 = (ReqH *)GetObj(hydrogenos);
    nExit(m);

    Hydrogen h1 = (Hydrogen) r1->h;
    Hydrogen h2 = (Hydrogen) r2->h;

    H2O r = makeH2O(h1, h2, o);
    r1->h2o = r;
    r2->h2o = r;

    nEnter(m);
    nSignalCondition(r1->w);
    nSignalCondition(r2->w);
    nExit(m);

    return r;

  }
  else{
    
    ReqO ro = {nMakeCondition(m), o, NULL};
    PutObj(oxigenos, &ro);
    while(ro.h2o == NULL)
      nWaitCondition(ro.w);
    nDestroyCondition(ro.w);
    nExit(m);
    return ro.h2o;

  }

}

H2O combineHydro(Hydrogen h) {
  
  nEnter(m);
  if(EmptyFifoQueue(oxigenos) || EmptyFifoQueue(hydrogenos)){
    
    ReqH rh = {nMakeCondition(m), h, NULL};
    PutObj(hydrogenos, &rh);
    while(rh.h2o == NULL)
      nWaitCondition(rh.w);
    nDestroyCondition(rh.w);
    nExit(m);
    return rh.h2o;

  }
  else{

    ReqH* r1 = (ReqH *)GetObj(hydrogenos);
    ReqO* r2 = (ReqO *)GetObj(oxigenos);
    nExit(m);

    Hydrogen h2 = r1->h;
    Oxygen o = r2->o;

    H2O r = makeH2O(h, h2, o);
    r1->h2o=r;
    r2->h2o=r;

    nEnter(m);
    nSignalCondition(r1->w);
    nSignalCondition(r2->w);
    nExit(m);

    return r;

  }
}
