#include <Empathy/Empathy/Empathy.h>
#include <Empathy/empathy-linear/linear_empathy.h>
#include <irrKlang.h>
#include <GLFW/glfw3.h>

using namespace std;

static GLFWwindow * window;
static GLfloat mouseX,mouseY;
irrklang::ISoundEngine* engine;

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
        empathy_linear::makeReadyToClose();

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
    window = glfwCreateWindow((GLuint)700, (GLuint)700, "Empathy | <3", nullptr, nullptr);
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

void init(){

    initGlfw();
    empathy_linear::init();

    empathy_linear::addJsonBrain("brains/test.json");
    empathy_linear::addDummyTouchBrain();

    engine = irrklang::createIrrKlangDevice();

    if (!engine)
    {
        printf("Could not startup engine\n");
        exit(EXIT_FAILURE);
    }

    engine->setSoundVolume(0.4f);
}

void loop(){
    while(! empathy_linear::shouldClose() && !glfwWindowShouldClose(window)){


        std::stack<empathy::moonlight::BasicNote> audioEvents= empathy_linear::getMusicalKeyboardEvents();
        while(! audioEvents.empty()){
            empathy::moonlight::BasicNote playableItem=audioEvents.top();

            std::string fileName=playableItem.getNote()+std::to_string(playableItem.getOctave()-1);
            if(playableItem.isSharp()){
                fileName="#"+fileName;

            }

            std::string path=empathy::getAssetPath("audio/keyboard/music/"+fileName+".mp3");

            try{

                cout<<"Playing audio "<<fileName<<endl;

                engine->play2D(path.c_str());

            }catch (int i){
                cout<<"Could not play "<<path<<endl;
                continue;
            }

            audioEvents.pop();
        }


        glfwPollEvents();

        empathy_linear::loop();

        empathy_linear::setTime(glfwGetTime());


        glfwSwapBuffers(window);
    }
}
void flush(){
    engine->drop();

    empathy_linear::flush();

    if(window!= nullptr)
        glfwSetWindowShouldClose(window,true);

    glfwTerminate();
}

int  main() {
    init();
    loop();
    flush();
}
