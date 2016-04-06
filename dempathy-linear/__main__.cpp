#include <Empathy/Empathy/Empathy.h>
#include "empathy_linear.h"

using namespace std;

int  main(){
//    empathy_linear::init();
    empathy_linear::addJsonBrain("brains/CanonInD.json");
    empathy_linear::addDummyTouchBrain();
    empathy_linear::run();

//    DEmpathy * empathy=new DEmpathy();
//
////    CWave_Test * brain=new CWave_Test();
//    empathy::brain::JSONBrain * brain=new empathy::brain::JSONBrain("brains/CanonInD.json");
//    brain->addTo(empathy);
//
//    (new empathy::brain::DummyTouchBrain())->addTo(empathy);
//
//    empathy->run();

}