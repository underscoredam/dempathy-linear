//
// Created by geek on 4/5/16.
//

#include <queue>
#include "empathy_linear.h"
#include <irrKlang.h>

using namespace std;

namespace empathy_linear{
    static GLfloat time;

    static GLFWwindow * window;

    Empathy_Linear* _instance;
    Empathy_Linear * getInstance();
    Linear_MoonLight * moonLight;
    irrklang::ISoundEngine* engine;

    class Empathy_Linear:public empathy::Empathy{

    protected:
        virtual GLfloat getTime() override {
            return time;
        }


    public:
        virtual void flush() override {
            empathy::Empathy::flush();

            if(window!= nullptr)
                glfwSetWindowShouldClose(window,true);

            glfwTerminate();
        }

    public:
        virtual void loop() override {
            empathy::Empathy::loop();
        }

        virtual bool shouldClose() override {
            return empathy::Empathy::shouldClose() || glfwWindowShouldClose(window);
        }


        virtual void init() override {
            initGlfw();

            setScreenSize(700,700);

            empathy_linear::moonLight=new Linear_MoonLight();
            setMoonLight(empathy_linear::moonLight);

            empathy::Empathy::init();
        }

    public:
        virtual void run() override {

        }
    };

    bool shouldClose(){
        return getInstance()->shouldClose();
    }
    std::stack<PlayableItem> getAudioEvents(){
        return moonLight->getEvents();
    }
    void addDummyTouchBrain() {
        (new empathy::brain::DummyTouchBrain())->addTo(getInstance());
    }

    void init(){
        getInstance()->init();
    }
    void run() {
        init();

        engine = irrklang::createIrrKlangDevice();

        if (!engine)
        {
            printf("Could not startup engine\n");
        }

        engine->setSoundVolume(0.4f);

        while(! getInstance()->shouldClose()){

            std::stack<PlayableItem> audioEvents=moonLight->getEvents();
            while(! audioEvents.empty()){
                PlayableItem playableItem=audioEvents.top();

                try{

                    cout<<"Playing audio"<<playableItem.fileName<<endl;

                    engine->play2D(playableItem.fileName.c_str());

                }catch (int i){
                    cout<<"Could not play "<<playableItem.fileName<<endl;
                    continue;
                }

                audioEvents.pop();
            }

            glfwPollEvents();

            getInstance()->loop();

            time=glfwGetTime();

            glfwSwapBuffers(window);
        }

        getInstance()->flush();
    }

    void addJsonBrain(std::string name) {
        empathy::brain::JSONBrain * brain=new empathy::brain::JSONBrain(name);
        brain->addTo(getInstance());
    }


    Empathy_Linear * getInstance(){
        if(_instance== nullptr)
            _instance=new Empathy_Linear();

        return _instance;
    }

    static GLfloat mouseX,mouseY;

    void mouse_input_callback(GLFWwindow *window, int button, int action, int mods) {
        if(action==GLFW_PRESS){
            empathy::radio::Event event(EMPATHY_EVENT_ACTION_NONE);

            if(button==GLFW_MOUSE_BUTTON_LEFT ){
                event=empathy::radio::Event(EMPATHY_EVENT_INPUT_MOUSE_LEFT_KEY_PRESS);
            }else if(button==GLFW_MOUSE_BUTTON_RIGHT){
                event=empathy::radio::Event(EMPATHY_EVENT_INPUT_MOUSE_RIGHT_KEY_PRESS);
            }

            event.putDouble(EMPATHY_MOUSE_XPOS,mouseX);
            event.putDouble(EMPATHY_MOUSE_YPOS,700-mouseY);


            empathy::radio::BroadcastStation::emit(event);
        }
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//    std::cout<<"key call back received"<<action<<std::endl;

        // When a user presses the escape key, we set the WindowShouldClose property to true,
        // closing the application

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
//            glfwSetWindowShouldClose(instance->window, GL_TRUE);
            getInstance()->makeReadyToClose();

            return;
        }

        cout<<"KEY callback"<<endl;
        std::string myAction="";
        if(action==GLFW_PRESS){
            myAction=EMPATHY_EVENT_INPUT_KEY_PRESS;
        }else if(action==GLFW_RELEASE){
            myAction=EMPATHY_EVENT_INPUT_KEY_RELEASE;
        }else if(action==GLFW_REPEAT){
            myAction=EMPATHY_EVENT_INPUT_KEY_REPEAT;
        }
        if(myAction != ""){
            empathy::radio::Event event=empathy::radio::Event(myAction);
            event.putInt(EMPATHY_EVENT_INPUT_KEY,key);

            empathy::radio::BroadcastStation::emit(event);
        }

    }


    void mouse_position_callback(GLFWwindow *window, double xpos, double ypos) {
        mouseX=xpos;
        mouseY=ypos;
    }


    void initGlfw() {
        //	cout<<"glfwInit"<<endl;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        int count;
        GLFWmonitor** monitors=glfwGetMonitors(&count);

        //Create a GLFW window
        window = glfwCreateWindow((GLuint)700, (GLuint)700, "Linux Empathy", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        //set event receiver call backs.
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window,mouse_input_callback);
        glfwSetCursorPosCallback(window,mouse_position_callback);
    }
}